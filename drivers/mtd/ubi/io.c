/*
 * Copyright (c) International Business Machines Corp., 2006
 * Copyright (c) Nokia Corporation, 2006, 2007
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See
 * the GNU General Public License for more details.
 *
 * Author: Artem Bityutskiy (Битюцкий Артём)
 */

/*
 * UBI input/output sub-system.
 *
 * This sub-system provides a uniform way to work with all kinds of the
 * underlying MTD devices. It also implements handy functions for reading and
 * writing UBI headers.
 *
 * We are trying to have a paranoid mindset and not to trust to what we read
 * from the flash media in order to be more secure and robust. So this
 * sub-system validates every single header it reads from the flash media.
 *
 * Some words about how the eraseblock headers are stored.
 *
 * The erase counter header is always stored at offset zero. By default, the
 * VID header is stored after the EC header at the closest aligned offset
 * (i.e. aligned to the minimum I/O unit size). Data starts next to the VID
 * header at the closest aligned offset. But this default layout may be
 * changed. For example, for different reasons (e.g., optimization) UBI may be
 * asked to put the VID header at further offset, and even at an unaligned
 * offset. Of course, if the offset of the VID header is unaligned, UBI adds
 * proper padding in front of it. Data offset may also be changed but it has to
 * be aligned.
 *
 * About minimal I/O units. In general, UBI assumes flash device model where
 * there is only one minimal I/O unit size. E.g., in case of NOR flash it is 1,
 * in case of NAND flash it is a NAND page, etc. This is reported by MTD in the
 * @ubi->mtd->writesize field. But as an exception, UBI admits use of another
 * (smaller) minimal I/O unit size for EC and VID headers to make it possible
 * to do different optimizations.
 *
 * This is extremely useful in case of NAND flashes which admit of several
 * write operations to one NAND page. In this case UBI can fit EC and VID
 * headers at one NAND page. Thus, UBI may use "sub-page" size as the minimal
 * I/O unit for the headers (the @ubi->hdrs_min_io_size field). But it still
 * reports NAND page size (@ubi->min_io_size) as a minimal I/O unit for the UBI
 * users.
 *
 * Example: some Samsung NANDs with 2KiB pages allow 4x 512-byte writes, so
 * although the minimal I/O unit is 2K, UBI uses 512 bytes for EC and VID
 * headers.
 *
 * Q: why not just to treat sub-page as a minimal I/O unit of this flash
 * device, e.g., make @ubi->min_io_size = 512 in the example above?
 *
 * A: because when writing a sub-page, MTD still writes a full 2K page but the
 * bytes which are not relevant to the sub-page are 0xFF. So, basically,
 * writing 4x512 sub-pages is 4 times slower than writing one 2KiB NAND page.
 * Thus, we prefer to use sub-pages only for EC and VID headers.
 *
 * As it was noted above, the VID header may start at a non-aligned offset.
 * For example, in case of a 2KiB page NAND flash with a 512 bytes sub-page,
 * the VID header may reside at offset 1984 which is the last 64 bytes of the
 * last sub-page (EC header is always at offset zero). This causes some
 * difficulties when reading and writing VID headers.
 *
 * Suppose we have a 64-byte buffer and we read a VID header at it. We change
 * the data and want to write this VID header out. As we can only write in
 * 512-byte chunks, we have to allocate one more buffer and copy our VID header
 * to offset 448 of this buffer.
 *
 * The I/O sub-system does the following trick in order to avoid this extra
 * copy. It always allocates a @ubi->vid_hdr_alsize bytes buffer for the VID
 * header and returns a pointer to offset @ubi->vid_hdr_shift of this buffer.
 * When the VID header is being written out, it shifts the VID header pointer
 * back and writes the whole sub-page.
 */

#include <linux/err.h>
#include <mtd/mtd-peb.h>
#include "ubi.h"

static int self_check_not_bad(const struct ubi_device *ubi, int pnum);
static int self_check_peb_ec_hdr(const struct ubi_device *ubi, int pnum);
static int self_check_ec_hdr(const struct ubi_device *ubi, int pnum,
			     const struct ubi_ec_hdr *ec_hdr);
static int self_check_peb_vid_hdr(const struct ubi_device *ubi, int pnum);
static int self_check_vid_hdr(const struct ubi_device *ubi, int pnum,
			      const struct ubi_vid_hdr *vid_hdr);

/**
 * ubi_io_read - read data from a physical eraseblock.
 * @ubi: UBI device description object
 * @buf: buffer where to store the read data
 * @pnum: physical eraseblock number to read from
 * @offset: offset within the physical eraseblock from where to read
 * @len: how many bytes to read
 *
 * This function reads data from offset @offset of physical eraseblock @pnum
 * and stores the read data in the @buf buffer. The following return codes are
 * possible:
 *
 * o %0 if all the requested data were successfully read;
 * o %UBI_IO_BITFLIPS if all the requested data were successfully read, but
 *   correctable bit-flips were detected; this is harmless but may indicate
 *   that this eraseblock may become bad soon (but do not have to);
 * o %-EBADMSG if the MTD subsystem reported about data integrity problems, for
 *   example it can be an ECC error in case of NAND; this most probably means
 *   that the data is corrupted;
 * o %-EIO if some I/O error occurred;
 * o other negative error codes in case of other errors.
 */
int ubi_io_read(const struct ubi_device *ubi, void *buf, int pnum, int offset,
		int len)
{
	int ret;

	ret = mtd_peb_read(ubi->mtd, buf, pnum, offset, len);
	if (mtd_is_bitflip(ret))
		return UBI_IO_BITFLIPS;
	return ret;
}

/**
 * ubi_io_write - write data to a physical eraseblock.
 * @ubi: UBI device description object
 * @buf: buffer with the data to write
 * @pnum: physical eraseblock number to write to
 * @offset: offset within the physical eraseblock where to write
 * @len: how many bytes to write
 *
 * This function writes @len bytes of data from buffer @buf to offset @offset
 * of physical eraseblock @pnum. If all the data were successfully written,
 * zero is returned. If an error occurred, this function returns a negative
 * error code. If %-EIO is returned, the physical eraseblock most probably went
 * bad.
 *
 * Note, in case of an error, it is possible that something was still written
 * to the flash media, but may be some garbage.
 */
int ubi_io_write(struct ubi_device *ubi, const void *buf, int pnum, int offset,
		 int len)
{
	int err;

	dbg_io("write %d bytes to PEB %d:%d", len, pnum, offset);

	ubi_assert(pnum >= 0 && pnum < ubi->peb_count);
	ubi_assert(offset >= 0 && offset + len <= ubi->peb_size);
	ubi_assert(offset % ubi->hdrs_min_io_size == 0);
	ubi_assert(len > 0 && len % ubi->hdrs_min_io_size == 0);

	if (ubi->ro_mode) {
		ubi_err(ubi, "read-only mode");
		return -EROFS;
	}

	if (offset >= ubi->leb_start) {
		/*
		 * We write to the data area of the physical eraseblock. Make
		 * sure it has valid EC and VID headers.
		 */
		err = self_check_peb_ec_hdr(ubi, pnum);
		if (err)
			return err;
		err = self_check_peb_vid_hdr(ubi, pnum);
		if (err)
			return err;
	}

	return mtd_peb_write(ubi->mtd, buf, pnum, offset, len);
}

/**
 * do_sync_erase - synchronously erase a physical eraseblock.
 * @ubi: UBI device description object
 * @pnum: the physical eraseblock number to erase
 *
 * This function synchronously erases physical eraseblock @pnum and returns
 * zero in case of success and a negative error code in case of failure. If
 * %-EIO is returned, the physical eraseblock most probably went bad.
 */
static int do_sync_erase(struct ubi_device *ubi, int pnum)
{
	dbg_io("erase PEB %d", pnum);
	ubi_assert(pnum >= 0 && pnum < ubi->peb_count);

	if (ubi->ro_mode) {
		ubi_err(ubi, "read-only mode");
		return -EROFS;
	}

	return mtd_peb_erase(ubi->mtd, pnum);
}

/**
 * nor_erase_prepare - prepare a NOR flash PEB for erasure.
 * @ubi: UBI device description object
 * @pnum: physical eraseblock number to prepare
 *
 * NOR flash, or at least some of them, have peculiar embedded PEB erasure
 * algorithm: the PEB is first filled with zeroes, then it is erased. And
 * filling with zeroes starts from the end of the PEB. This was observed with
 * Spansion S29GL512N NOR flash.
 *
 * This means that in case of a power cut we may end up with intact data at the
 * beginning of the PEB, and all zeroes at the end of PEB. In other words, the
 * EC and VID headers are OK, but a large chunk of data at the end of PEB is
 * zeroed. This makes UBI mistakenly treat this PEB as used and associate it
 * with an LEB, which leads to subsequent failures (e.g., UBIFS fails).
 *
 * This function is called before erasing NOR PEBs and it zeroes out EC and VID
 * magic numbers in order to invalidate them and prevent the failures. Returns
 * zero in case of success and a negative error code in case of failure.
 */
static int nor_erase_prepare(struct ubi_device *ubi, int pnum)
{
	int err;
	size_t written;
	loff_t addr;
	uint32_t data = 0;
	struct ubi_ec_hdr ec_hdr;
	struct ubi_vid_io_buf vidb;

	/*
	 * Note, we cannot generally define VID header buffers on stack,
	 * because of the way we deal with these buffers (see the header
	 * comment in this file). But we know this is a NOR-specific piece of
	 * code, so we can do this. But yes, this is error-prone and we should
	 * (pre-)allocate VID header buffer instead.
	 */
	struct ubi_vid_hdr vid_hdr;

	/*
	 * If VID or EC is valid, we have to corrupt them before erasing.
	 * It is important to first invalidate the EC header, and then the VID
	 * header. Otherwise a power cut may lead to valid EC header and
	 * invalid VID header, in which case UBI will treat this PEB as
	 * corrupted and will try to preserve it, and print scary warnings.
	 */
	addr = (loff_t)pnum * ubi->peb_size;
	err = ubi_io_read_ec_hdr(ubi, pnum, &ec_hdr, 0);
	if (err != UBI_IO_BAD_HDR_EBADMSG && err != UBI_IO_BAD_HDR &&
	    err != UBI_IO_FF){
		err = mtd_write(ubi->mtd, addr, 4, &written, (void *)&data);
		if(err)
			goto error;
	}

	ubi_init_vid_buf(ubi, &vidb, &vid_hdr);
	ubi_assert(&vid_hdr == ubi_get_vid_hdr(&vidb));

	err = ubi_io_read_vid_hdr(ubi, pnum, &vidb, 0);
	if (err != UBI_IO_BAD_HDR_EBADMSG && err != UBI_IO_BAD_HDR &&
	    err != UBI_IO_FF){
		addr += ubi->vid_hdr_aloffset;
		err = mtd_write(ubi->mtd, addr, 4, &written, (void *)&data);
		if (err)
			goto error;
	}
	return 0;

error:
	/*
	 * The PEB contains a valid VID or EC header, but we cannot invalidate
	 * it. Supposedly the flash media or the driver is screwed up, so
	 * return an error.
	 */
	ubi_err(ubi, "cannot invalidate PEB %d, write returned %d", pnum, err);
	ubi_dump_flash(ubi, pnum, 0, ubi->peb_size);
	return -EIO;
}

/**
 * ubi_io_sync_erase - synchronously erase a physical eraseblock.
 * @ubi: UBI device description object
 * @pnum: physical eraseblock number to erase
 * @torture: if this physical eraseblock has to be tortured
 *
 * This function synchronously erases physical eraseblock @pnum. If @torture
 * flag is not zero, the physical eraseblock is checked by means of writing
 * different patterns to it and reading them back. If the torturing is enabled,
 * the physical eraseblock is erased more than once.
 *
 * This function returns the number of erasures made in case of success, %-EIO
 * if the erasure failed or the torturing test failed, and other negative error
 * codes in case of other errors. Note, %-EIO means that the physical
 * eraseblock is bad.
 */
int ubi_io_sync_erase(struct ubi_device *ubi, int pnum, int torture)
{
	int err, ret = 0;

	ubi_assert(pnum >= 0 && pnum < ubi->peb_count);

	err = self_check_not_bad(ubi, pnum);
	if (err != 0)
		return err;

	if (ubi->ro_mode) {
		ubi_err(ubi, "read-only mode");
		return -EROFS;
	}

	if (ubi->nor_flash) {
		err = nor_erase_prepare(ubi, pnum);
		if (err)
			return err;
	}

	if (torture) {
		ret = mtd_peb_torture(ubi->mtd, pnum);
		if (ret < 0)
			return ret;
	} else {
		err = do_sync_erase(ubi, pnum);
		if (err)
			return err;
	}

	return ret + 1;
}

/**
 * ubi_io_is_bad - check if a physical eraseblock is bad.
 * @ubi: UBI device description object
 * @pnum: the physical eraseblock number to check
 *
 * This function returns a positive number if the physical eraseblock is bad,
 * zero if not, and a negative error code if an error occurred.
 */
int ubi_io_is_bad(const struct ubi_device *ubi, int pnum)
{
	struct mtd_info *mtd = ubi->mtd;

	ubi_assert(pnum >= 0 && pnum < ubi->peb_count);

	if (ubi->bad_allowed) {
		int ret;

		ret = mtd_block_isbad(mtd, (loff_t)pnum * ubi->peb_size);
		if (ret < 0)
			ubi_err(ubi, "error %d while checking if PEB %d is bad",
				ret, pnum);
		else if (ret)
			dbg_io("PEB %d is bad", pnum);
		return ret;
	}

	return 0;
}

/**
 * ubi_io_mark_bad - mark a physical eraseblock as bad.
 * @ubi: UBI device description object
 * @pnum: the physical eraseblock number to mark
 *
 * This function returns zero in case of success and a negative error code in
 * case of failure.
 */
int ubi_io_mark_bad(const struct ubi_device *ubi, int pnum)
{
	int err;
	struct mtd_info *mtd = ubi->mtd;

	ubi_assert(pnum >= 0 && pnum < ubi->peb_count);

	if (ubi->ro_mode) {
		ubi_err(ubi, "read-only mode");
		return -EROFS;
	}

	if (!ubi->bad_allowed)
		return 0;

	err = mtd_block_markbad(mtd, (loff_t)pnum * ubi->peb_size);
	if (err)
		ubi_err(ubi, "cannot mark PEB %d bad, error %d", pnum, err);
	return err;
}

/**
 * validate_ec_hdr - validate an erase counter header.
 * @ubi: UBI device description object
 * @ec_hdr: the erase counter header to check
 *
 * This function returns zero if the erase counter header is OK, and %1 if
 * not.
 */
static int validate_ec_hdr(const struct ubi_device *ubi,
			   const struct ubi_ec_hdr *ec_hdr)
{
	long long ec;
	int vid_hdr_offset, leb_start;

	ec = be64_to_cpu(ec_hdr->ec);
	vid_hdr_offset = be32_to_cpu(ec_hdr->vid_hdr_offset);
	leb_start = be32_to_cpu(ec_hdr->data_offset);

	if (ec_hdr->version != UBI_VERSION) {
		ubi_err(ubi, "node with incompatible UBI version found: this UBI version is %d, image version is %d",
			UBI_VERSION, (int)ec_hdr->version);
		goto bad;
	}

	if (vid_hdr_offset != ubi->vid_hdr_offset) {
		ubi_err(ubi, "bad VID header offset %d, expected %d",
			vid_hdr_offset, ubi->vid_hdr_offset);
		goto bad;
	}

	if (leb_start != ubi->leb_start) {
		ubi_err(ubi, "bad data offset %d, expected %d",
			leb_start, ubi->leb_start);
		goto bad;
	}

	if (ec < 0 || ec > UBI_MAX_ERASECOUNTER) {
		ubi_err(ubi, "bad erase counter %lld", ec);
		goto bad;
	}

	return 0;

bad:
	ubi_err(ubi, "bad EC header");
	ubi_dump_ec_hdr(ec_hdr);
	dump_stack();
	return 1;
}

/**
 * ubi_io_read_ec_hdr - read and check an erase counter header.
 * @ubi: UBI device description object
 * @pnum: physical eraseblock to read from
 * @ec_hdr: a &struct ubi_ec_hdr object where to store the read erase counter
 * header
 * @verbose: be verbose if the header is corrupted or was not found
 *
 * This function reads erase counter header from physical eraseblock @pnum and
 * stores it in @ec_hdr. This function also checks CRC checksum of the read
 * erase counter header. The following codes may be returned:
 *
 * o %0 if the CRC checksum is correct and the header was successfully read;
 * o %UBI_IO_BITFLIPS if the CRC is correct, but bit-flips were detected
 *   and corrected by the flash driver; this is harmless but may indicate that
 *   this eraseblock may become bad soon (but may be not);
 * o %UBI_IO_BAD_HDR if the erase counter header is corrupted (a CRC error);
 * o %UBI_IO_BAD_HDR_EBADMSG is the same as %UBI_IO_BAD_HDR, but there also was
 *   a data integrity error (uncorrectable ECC error in case of NAND);
 * o %UBI_IO_FF if only 0xFF bytes were read (the PEB is supposedly empty)
 * o a negative error code in case of failure.
 */
int ubi_io_read_ec_hdr(struct ubi_device *ubi, int pnum,
		       struct ubi_ec_hdr *ec_hdr, int verbose)
{
	int err, read_err;
	uint32_t crc, magic, hdr_crc;

	dbg_io("read EC header from PEB %d", pnum);
	ubi_assert(pnum >= 0 && pnum < ubi->peb_count);

	read_err = ubi_io_read(ubi, ec_hdr, pnum, 0, UBI_EC_HDR_SIZE);
	if (read_err) {
		if (read_err != UBI_IO_BITFLIPS && !mtd_is_eccerr(read_err))
			return read_err;

		/*
		 * We read all the data, but either a correctable bit-flip
		 * occurred, or MTD reported a data integrity error
		 * (uncorrectable ECC error in case of NAND). The former is
		 * harmless, the later may mean that the read data is
		 * corrupted. But we have a CRC check-sum and we will detect
		 * this. If the EC header is still OK, we just report this as
		 * there was a bit-flip, to force scrubbing.
		 */
	}

	magic = be32_to_cpu(ec_hdr->magic);
	if (magic != UBI_EC_HDR_MAGIC) {
		if (mtd_is_eccerr(read_err))
			return UBI_IO_BAD_HDR_EBADMSG;

		/*
		 * The magic field is wrong. Let's check if we have read all
		 * 0xFF. If yes, this physical eraseblock is assumed to be
		 * empty.
		 */
		if (mtd_buf_all_ff(ec_hdr, UBI_EC_HDR_SIZE)) {
			/* The physical eraseblock is supposedly empty */
			if (verbose)
				ubi_warn(ubi, "no EC header found at PEB %d, only 0xFF bytes",
					 pnum);
			dbg_bld("no EC header found at PEB %d, only 0xFF bytes",
				pnum);
			if (!read_err)
				return UBI_IO_FF;
			else
				return UBI_IO_FF_BITFLIPS;
		}

		/*
		 * This is not a valid erase counter header, and these are not
		 * 0xFF bytes. Report that the header is corrupted.
		 */
		if (verbose) {
			ubi_warn(ubi, "bad magic number at PEB %d: %08x instead of %08x",
				 pnum, magic, UBI_EC_HDR_MAGIC);
			ubi_dump_ec_hdr(ec_hdr);
		}
		dbg_bld("bad magic number at PEB %d: %08x instead of %08x",
			pnum, magic, UBI_EC_HDR_MAGIC);
		return UBI_IO_BAD_HDR;
	}

	crc = crc32(UBI_CRC32_INIT, ec_hdr, UBI_EC_HDR_SIZE_CRC);
	hdr_crc = be32_to_cpu(ec_hdr->hdr_crc);

	if (hdr_crc != crc) {
		if (verbose) {
			ubi_warn(ubi, "bad EC header CRC at PEB %d, calculated %#08x, read %#08x",
				 pnum, crc, hdr_crc);
			ubi_dump_ec_hdr(ec_hdr);
		}
		dbg_bld("bad EC header CRC at PEB %d, calculated %#08x, read %#08x",
			pnum, crc, hdr_crc);

		if (!read_err)
			return UBI_IO_BAD_HDR;
		else
			return UBI_IO_BAD_HDR_EBADMSG;
	}

	/* And of course validate what has just been read from the media */
	err = validate_ec_hdr(ubi, ec_hdr);
	if (err) {
		ubi_err(ubi, "validation failed for PEB %d", pnum);
		return -EINVAL;
	}

	/*
	 * If there was %-EBADMSG, but the header CRC is still OK, report about
	 * a bit-flip to force scrubbing on this PEB.
	 */
	return read_err ? UBI_IO_BITFLIPS : 0;
}

/**
 * ubi_io_write_ec_hdr - write an erase counter header.
 * @ubi: UBI device description object
 * @pnum: physical eraseblock to write to
 * @ec_hdr: the erase counter header to write
 *
 * This function writes erase counter header described by @ec_hdr to physical
 * eraseblock @pnum. It also fills most fields of @ec_hdr before writing, so
 * the caller do not have to fill them. Callers must only fill the @ec_hdr->ec
 * field.
 *
 * This function returns zero in case of success and a negative error code in
 * case of failure. If %-EIO is returned, the physical eraseblock most probably
 * went bad.
 */
int ubi_io_write_ec_hdr(struct ubi_device *ubi, int pnum,
			struct ubi_ec_hdr *ec_hdr)
{
	int err;
	uint32_t crc;

	dbg_io("write EC header to PEB %d", pnum);
	ubi_assert(pnum >= 0 &&  pnum < ubi->peb_count);

	ec_hdr->magic = cpu_to_be32(UBI_EC_HDR_MAGIC);
	ec_hdr->version = UBI_VERSION;
	ec_hdr->vid_hdr_offset = cpu_to_be32(ubi->vid_hdr_offset);
	ec_hdr->data_offset = cpu_to_be32(ubi->leb_start);
	ec_hdr->image_seq = cpu_to_be32(ubi->image_seq);
	crc = crc32(UBI_CRC32_INIT, ec_hdr, UBI_EC_HDR_SIZE_CRC);
	ec_hdr->hdr_crc = cpu_to_be32(crc);

	err = self_check_ec_hdr(ubi, pnum, ec_hdr);
	if (err)
		return err;

	err = ubi_io_write(ubi, ec_hdr, pnum, 0, ubi->ec_hdr_alsize);
	return err;
}

/**
 * validate_vid_hdr - validate a volume identifier header.
 * @ubi: UBI device description object
 * @vid_hdr: the volume identifier header to check
 *
 * This function checks that data stored in the volume identifier header
 * @vid_hdr. Returns zero if the VID header is OK and %1 if not.
 */
static int validate_vid_hdr(const struct ubi_device *ubi,
			    const struct ubi_vid_hdr *vid_hdr)
{
	int vol_type = vid_hdr->vol_type;
	int copy_flag = vid_hdr->copy_flag;
	int vol_id = be32_to_cpu(vid_hdr->vol_id);
	int lnum = be32_to_cpu(vid_hdr->lnum);
	int compat = vid_hdr->compat;
	int data_size = be32_to_cpu(vid_hdr->data_size);
	int used_ebs = be32_to_cpu(vid_hdr->used_ebs);
	int data_pad = be32_to_cpu(vid_hdr->data_pad);
	int data_crc = be32_to_cpu(vid_hdr->data_crc);
	int usable_leb_size = ubi->leb_size - data_pad;

	if (copy_flag != 0 && copy_flag != 1) {
		ubi_err(ubi, "bad copy_flag");
		goto bad;
	}

	if (vol_id < 0 || lnum < 0 || data_size < 0 || used_ebs < 0 ||
	    data_pad < 0) {
		ubi_err(ubi, "negative values");
		goto bad;
	}

	if (vol_id >= UBI_MAX_VOLUMES && vol_id < UBI_INTERNAL_VOL_START) {
		ubi_err(ubi, "bad vol_id");
		goto bad;
	}

	if (vol_id < UBI_INTERNAL_VOL_START && compat != 0) {
		ubi_err(ubi, "bad compat");
		goto bad;
	}

	if (vol_id >= UBI_INTERNAL_VOL_START && compat != UBI_COMPAT_DELETE &&
	    compat != UBI_COMPAT_RO && compat != UBI_COMPAT_PRESERVE &&
	    compat != UBI_COMPAT_REJECT) {
		ubi_err(ubi, "bad compat");
		goto bad;
	}

	if (vol_type != UBI_VID_DYNAMIC && vol_type != UBI_VID_STATIC) {
		ubi_err(ubi, "bad vol_type");
		goto bad;
	}

	if (data_pad >= ubi->leb_size / 2) {
		ubi_err(ubi, "bad data_pad");
		goto bad;
	}

	if (data_size > ubi->leb_size) {
		ubi_err(ubi, "bad data_size");
		goto bad;
	}

	if (vol_type == UBI_VID_STATIC) {
		/*
		 * Although from high-level point of view static volumes may
		 * contain zero bytes of data, but no VID headers can contain
		 * zero at these fields, because they empty volumes do not have
		 * mapped logical eraseblocks.
		 */
		if (used_ebs == 0) {
			ubi_err(ubi, "zero used_ebs");
			goto bad;
		}
		if (data_size == 0) {
			ubi_err(ubi, "zero data_size");
			goto bad;
		}
		if (lnum < used_ebs - 1) {
			if (data_size != usable_leb_size) {
				ubi_err(ubi, "bad data_size");
				goto bad;
			}
		} else if (lnum == used_ebs - 1) {
			if (data_size == 0) {
				ubi_err(ubi, "bad data_size at last LEB");
				goto bad;
			}
		} else {
			ubi_err(ubi, "too high lnum");
			goto bad;
		}
	} else {
		if (copy_flag == 0) {
			if (data_crc != 0) {
				ubi_err(ubi, "non-zero data CRC");
				goto bad;
			}
			if (data_size != 0) {
				ubi_err(ubi, "non-zero data_size");
				goto bad;
			}
		} else {
			if (data_size == 0) {
				ubi_err(ubi, "zero data_size of copy");
				goto bad;
			}
		}
		if (used_ebs != 0) {
			ubi_err(ubi, "bad used_ebs");
			goto bad;
		}
	}

	return 0;

bad:
	ubi_err(ubi, "bad VID header");
	ubi_dump_vid_hdr(vid_hdr);
	dump_stack();
	return 1;
}

/**
 * ubi_io_read_vid_hdr - read and check a volume identifier header.
 * @ubi: UBI device description object
 * @pnum: physical eraseblock number to read from
 * @vidb: the volume identifier buffer to store data in
 * @verbose: be verbose if the header is corrupted or wasn't found
 *
 * This function reads the volume identifier header from physical eraseblock
 * @pnum and stores it in @vidb. It also checks CRC checksum of the read
 * volume identifier header. The error codes are the same as in
 * 'ubi_io_read_ec_hdr()'.
 *
 * Note, the implementation of this function is also very similar to
 * 'ubi_io_read_ec_hdr()', so refer commentaries in 'ubi_io_read_ec_hdr()'.
 */
int ubi_io_read_vid_hdr(struct ubi_device *ubi, int pnum,
			struct ubi_vid_io_buf *vidb, int verbose)
{
	int err, read_err;
	uint32_t crc, magic, hdr_crc;
	struct ubi_vid_hdr *vid_hdr = ubi_get_vid_hdr(vidb);
	void *p = vidb->buffer;

	dbg_io("read VID header from PEB %d", pnum);
	ubi_assert(pnum >= 0 &&  pnum < ubi->peb_count);

	read_err = ubi_io_read(ubi, p, pnum, ubi->vid_hdr_aloffset,
			  ubi->vid_hdr_shift + UBI_VID_HDR_SIZE);
	if (read_err && read_err != UBI_IO_BITFLIPS && !mtd_is_eccerr(read_err))
		return read_err;

	magic = be32_to_cpu(vid_hdr->magic);
	if (magic != UBI_VID_HDR_MAGIC) {
		if (mtd_is_eccerr(read_err))
			return UBI_IO_BAD_HDR_EBADMSG;

		if (mtd_buf_all_ff(vid_hdr, UBI_VID_HDR_SIZE)) {
			if (verbose)
				ubi_warn(ubi, "no VID header found at PEB %d, only 0xFF bytes",
					 pnum);
			dbg_bld("no VID header found at PEB %d, only 0xFF bytes",
				pnum);
			if (!read_err)
				return UBI_IO_FF;
			else
				return UBI_IO_FF_BITFLIPS;
		}

		if (verbose) {
			ubi_warn(ubi, "bad magic number at PEB %d: %08x instead of %08x",
				 pnum, magic, UBI_VID_HDR_MAGIC);
			ubi_dump_vid_hdr(vid_hdr);
		}
		dbg_bld("bad magic number at PEB %d: %08x instead of %08x",
			pnum, magic, UBI_VID_HDR_MAGIC);
		return UBI_IO_BAD_HDR;
	}

	crc = crc32(UBI_CRC32_INIT, vid_hdr, UBI_VID_HDR_SIZE_CRC);
	hdr_crc = be32_to_cpu(vid_hdr->hdr_crc);

	if (hdr_crc != crc) {
		if (verbose) {
			ubi_warn(ubi, "bad CRC at PEB %d, calculated %#08x, read %#08x",
				 pnum, crc, hdr_crc);
			ubi_dump_vid_hdr(vid_hdr);
		}
		dbg_bld("bad CRC at PEB %d, calculated %#08x, read %#08x",
			pnum, crc, hdr_crc);
		if (!read_err)
			return UBI_IO_BAD_HDR;
		else
			return UBI_IO_BAD_HDR_EBADMSG;
	}

	err = validate_vid_hdr(ubi, vid_hdr);
	if (err) {
		ubi_err(ubi, "validation failed for PEB %d", pnum);
		return -EINVAL;
	}

	return read_err ? UBI_IO_BITFLIPS : 0;
}

/**
 * ubi_io_write_vid_hdr - write a volume identifier header.
 * @ubi: UBI device description object
 * @pnum: the physical eraseblock number to write to
 * @vidb: the volume identifier buffer to write
 *
 * This function writes the volume identifier header described by @vid_hdr to
 * physical eraseblock @pnum. This function automatically fills the
 * @vidb->hdr->magic and the @vidb->hdr->version fields, as well as calculates
 * header CRC checksum and stores it at vidb->hdr->hdr_crc.
 *
 * This function returns zero in case of success and a negative error code in
 * case of failure. If %-EIO is returned, the physical eraseblock probably went
 * bad.
 */
int ubi_io_write_vid_hdr(struct ubi_device *ubi, int pnum,
			 struct ubi_vid_io_buf *vidb)
{
	struct ubi_vid_hdr *vid_hdr = ubi_get_vid_hdr(vidb);
	int err;
	uint32_t crc;
	void *p = vidb->buffer;

	dbg_io("write VID header to PEB %d", pnum);
	ubi_assert(pnum >= 0 &&  pnum < ubi->peb_count);

	err = self_check_peb_ec_hdr(ubi, pnum);
	if (err)
		return err;

	vid_hdr->magic = cpu_to_be32(UBI_VID_HDR_MAGIC);
	vid_hdr->version = UBI_VERSION;
	crc = crc32(UBI_CRC32_INIT, vid_hdr, UBI_VID_HDR_SIZE_CRC);
	vid_hdr->hdr_crc = cpu_to_be32(crc);

	err = self_check_vid_hdr(ubi, pnum, vid_hdr);
	if (err)
		return err;

	err = ubi_io_write(ubi, p, pnum, ubi->vid_hdr_aloffset,
			   ubi->vid_hdr_alsize);
	return err;
}

/**
 * self_check_not_bad - ensure that a physical eraseblock is not bad.
 * @ubi: UBI device description object
 * @pnum: physical eraseblock number to check
 *
 * This function returns zero if the physical eraseblock is good, %-EINVAL if
 * it is bad and a negative error code if an error occurred.
 */
static int self_check_not_bad(const struct ubi_device *ubi, int pnum)
{
	int err;

	if (!ubi_dbg_chk_io(ubi))
		return 0;

	err = ubi_io_is_bad(ubi, pnum);
	if (!err)
		return err;

	ubi_err(ubi, "self-check failed for PEB %d", pnum);
	dump_stack();
	return err > 0 ? -EINVAL : err;
}

/**
 * self_check_ec_hdr - check if an erase counter header is all right.
 * @ubi: UBI device description object
 * @pnum: physical eraseblock number the erase counter header belongs to
 * @ec_hdr: the erase counter header to check
 *
 * This function returns zero if the erase counter header contains valid
 * values, and %-EINVAL if not.
 */
static int self_check_ec_hdr(const struct ubi_device *ubi, int pnum,
			     const struct ubi_ec_hdr *ec_hdr)
{
	int err;
	uint32_t magic;

	if (!ubi_dbg_chk_io(ubi))
		return 0;

	magic = be32_to_cpu(ec_hdr->magic);
	if (magic != UBI_EC_HDR_MAGIC) {
		ubi_err(ubi, "bad magic %#08x, must be %#08x",
			magic, UBI_EC_HDR_MAGIC);
		goto fail;
	}

	err = validate_ec_hdr(ubi, ec_hdr);
	if (err) {
		ubi_err(ubi, "self-check failed for PEB %d", pnum);
		goto fail;
	}

	return 0;

fail:
	ubi_dump_ec_hdr(ec_hdr);
	dump_stack();
	return -EINVAL;
}

/**
 * self_check_peb_ec_hdr - check erase counter header.
 * @ubi: UBI device description object
 * @pnum: the physical eraseblock number to check
 *
 * This function returns zero if the erase counter header is all right and and
 * a negative error code if not or if an error occurred.
 */
static int self_check_peb_ec_hdr(const struct ubi_device *ubi, int pnum)
{
	int err;
	uint32_t crc, hdr_crc;
	struct ubi_ec_hdr *ec_hdr;

	if (!ubi_dbg_chk_io(ubi))
		return 0;

	ec_hdr = kzalloc(ubi->ec_hdr_alsize, GFP_NOFS);
	if (!ec_hdr)
		return -ENOMEM;

	err = ubi_io_read(ubi, ec_hdr, pnum, 0, UBI_EC_HDR_SIZE);
	if (err && err != UBI_IO_BITFLIPS && !mtd_is_eccerr(err))
		goto exit;

	crc = crc32(UBI_CRC32_INIT, ec_hdr, UBI_EC_HDR_SIZE_CRC);
	hdr_crc = be32_to_cpu(ec_hdr->hdr_crc);
	if (hdr_crc != crc) {
		ubi_err(ubi, "bad CRC, calculated %#08x, read %#08x",
			crc, hdr_crc);
		ubi_err(ubi, "self-check failed for PEB %d", pnum);
		ubi_dump_ec_hdr(ec_hdr);
		dump_stack();
		err = -EINVAL;
		goto exit;
	}

	err = self_check_ec_hdr(ubi, pnum, ec_hdr);

exit:
	kfree(ec_hdr);
	return err;
}

/**
 * self_check_vid_hdr - check that a volume identifier header is all right.
 * @ubi: UBI device description object
 * @pnum: physical eraseblock number the volume identifier header belongs to
 * @vid_hdr: the volume identifier header to check
 *
 * This function returns zero if the volume identifier header is all right, and
 * %-EINVAL if not.
 */
static int self_check_vid_hdr(const struct ubi_device *ubi, int pnum,
			      const struct ubi_vid_hdr *vid_hdr)
{
	int err;
	uint32_t magic;

	if (!ubi_dbg_chk_io(ubi))
		return 0;

	magic = be32_to_cpu(vid_hdr->magic);
	if (magic != UBI_VID_HDR_MAGIC) {
		ubi_err(ubi, "bad VID header magic %#08x at PEB %d, must be %#08x",
			magic, pnum, UBI_VID_HDR_MAGIC);
		goto fail;
	}

	err = validate_vid_hdr(ubi, vid_hdr);
	if (err) {
		ubi_err(ubi, "self-check failed for PEB %d", pnum);
		goto fail;
	}

	return err;

fail:
	ubi_err(ubi, "self-check failed for PEB %d", pnum);
	ubi_dump_vid_hdr(vid_hdr);
	dump_stack();
	return -EINVAL;

}

/**
 * self_check_peb_vid_hdr - check volume identifier header.
 * @ubi: UBI device description object
 * @pnum: the physical eraseblock number to check
 *
 * This function returns zero if the volume identifier header is all right,
 * and a negative error code if not or if an error occurred.
 */
static int self_check_peb_vid_hdr(const struct ubi_device *ubi, int pnum)
{
	int err;
	uint32_t crc, hdr_crc;
	struct ubi_vid_io_buf *vidb;
	struct ubi_vid_hdr *vid_hdr;
	void *p;

	if (!ubi_dbg_chk_io(ubi))
		return 0;

	vidb = ubi_alloc_vid_buf(ubi, GFP_NOFS);
	if (!vidb)
		return -ENOMEM;

	vid_hdr = ubi_get_vid_hdr(vidb);
	p = vidb->buffer;
	err = ubi_io_read(ubi, p, pnum, ubi->vid_hdr_aloffset,
			  ubi->vid_hdr_alsize);
	if (err && err != UBI_IO_BITFLIPS && !mtd_is_eccerr(err))
		goto exit;

	crc = crc32(UBI_CRC32_INIT, vid_hdr, UBI_VID_HDR_SIZE_CRC);
	hdr_crc = be32_to_cpu(vid_hdr->hdr_crc);
	if (hdr_crc != crc) {
		ubi_err(ubi, "bad VID header CRC at PEB %d, calculated %#08x, read %#08x",
			pnum, crc, hdr_crc);
		ubi_err(ubi, "self-check failed for PEB %d", pnum);
		ubi_dump_vid_hdr(vid_hdr);
		dump_stack();
		err = -EINVAL;
		goto exit;
	}

	err = self_check_vid_hdr(ubi, pnum, vid_hdr);

exit:
	ubi_free_vid_buf(vidb);
	return err;
}

/**
 * ubi_self_check_all_ff - check that a region of flash is empty.
 * @ubi: UBI device description object
 * @pnum: the physical eraseblock number to check
 * @offset: the starting offset within the physical eraseblock to check
 * @len: the length of the region to check
 *
 * This function returns zero if only 0xFF bytes are present at offset
 * @offset of the physical eraseblock @pnum, and a negative error code if not
 * or if an error occurred.
 */
int ubi_self_check_all_ff(struct ubi_device *ubi, int pnum, int offset, int len)
{
	if (!ubi_dbg_chk_io(ubi))
		return 0;

	return mtd_peb_check_all_ff(ubi->mtd, pnum, offset, len, 1);
}
