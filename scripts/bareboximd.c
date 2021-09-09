// SPDX-License-Identifier: GPL-2.0-or-later
// SPDX-FileCopyrightText: 2014 Sascha Hauer, Pengutronix

#include <stdio.h>
#include <sys/types.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>
#include <errno.h>
#include <stdarg.h>
#include <linux/err.h>
#include <linux/kernel.h>
#include <sys/mman.h>

#include "../include/image-metadata.h"

#define eprintf(args...) fprintf(stderr, ## args)

static void debug(const char *fmt, ...)
{
	va_list ap;

	if (!imd_command_verbose)
		return;

	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);
}

int imd_command_setenv(const char *variable_name, const char *value)
{
	fprintf(stderr, "-s option ignored\n");

	return -EINVAL;
}

static int write_file(const char *filename, const void *buf, size_t size)
{
	int fd, ret = 0;
	int now;

	fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd < 0)
		return fd;

	while (size) {
		now = write(fd, buf, size);
		if (now < 0) {
			ret = now;
			goto out;
		}
		size -= now;
		buf += now;
	}

out:
	close(fd);

	return ret;
}

static int read_file_2(const char *filename, size_t *size, void **outbuf, size_t max_size)
{
	off_t fsize;
	ssize_t rsize;
	int ret, fd;
	void *buf;

	*size = 0;
	*outbuf = NULL;

	fd = open(filename, O_RDONLY);
	if (fd < 0) {
		fprintf(stderr, "Cannot open %s: %s\n", filename, strerror(errno));
		return -errno;
	}

	fsize = lseek(fd, 0, SEEK_END);
	if (fsize == -1) {
		fprintf(stderr, "Cannot get size %s: %s\n", filename, strerror(errno));
		ret = -errno;
		goto close;
	}

	if (fsize < max_size)
		max_size = fsize;

	if (lseek(fd, 0, SEEK_SET) == -1) {
		fprintf(stderr, "Cannot seek to start %s: %s\n", filename, strerror(errno));
		ret = -errno;
		goto close;
	}

	buf = mmap(NULL, max_size, PROT_READ, MAP_SHARED, fd, 0);
	if (buf == MAP_FAILED ) {
		buf = malloc(max_size);
		if (!buf) {
			fprintf(stderr, "Cannot allocate memory\n");
			ret = -ENOMEM;
			goto close;
		}

		*outbuf = buf;

		while (*size < max_size) {
			rsize = read(fd, buf, max_size - *size);
			if (rsize == 0) {
				ret = -EIO;
				goto free;
			}

			if (rsize < 0) {
				ret = -errno;
				goto free;
			}

			buf += rsize;
			*size += rsize;
		}
	} else {
		*outbuf = buf;
		*size = max_size;
	}

	ret = 0;
	goto close;
free:
	*outbuf = NULL;
	free(buf);
close:
	close(fd);
	return ret;
}

static inline void read_file_2_free(void *buf)
{
	/*
	 * Can't free() here because buffer might be mmapped. No need
	 * to do anything as we are exitting in a moment anyway.
	 */
}

static unsigned long simple_strtoul(const char *cp, char **endp, unsigned int base)
{
	return strtoul(cp, endp, base);
}

#include "../include/xfuncs.h"
#include "../crypto/crc32.c"
#include "../common/imd.c"

static void usage(const char *prgname)
{
	printf(
"Extract metadata from a barebox image\n"
"\n"
"Usage: %s [OPTIONS] FILE\n"
"Options:\n"
"-t <type>    only show information of <type>\n"
"-n <no>      for tags with multiple strings only show string <no>\n"
"-v           Be verbose\n"
"-V           Verify checksum of FILE\n"
"-c           Create checksum for FILE and write it to the crc32 tag\n"
"\n"
"Without options all information available is printed. Valid types are:\n"
"release, build, model, of_compatible\n",
	prgname);
}

int main(int argc, char *argv[])
{
	int ret;

	ret = imd_command(argc, argv);
	if (ret == -ENOSYS) {
		usage(argv[0]);
		exit(1);
	}

	if (ret)
		fprintf(stderr, "%s\n", strerror(-ret));

	return ret ? 1 : 0;
}
