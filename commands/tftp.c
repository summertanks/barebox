// SPDX-License-Identifier: GPL-2.0-only
// SPDX-FileCopyrightText: © 2012 Sascha Hauer <s.hauer@pengutronix.de>, Pengutronix

/* tftp.c - (up)load tftp files */

#include <common.h>
#include <command.h>
#include <linux/stat.h>
#include <getopt.h>
#include <fcntl.h>
#include <libgen.h>
#include <fs.h>
#include <net.h>
#include <libbb.h>
#include <libfile.h>

#define TFTP_MOUNT_PATH	"/.tftp_tmp_path"

static int do_tftpb(int argc, char *argv[])
{
	char *source, *dest, *freep;
	int opt;
	int tftp_push = 0;
	int ret;
	IPaddr_t ip;
	char ip4_str[sizeof("255.255.255.255")];

	while ((opt = getopt(argc, argv, "p")) > 0) {
		switch(opt) {
		case 'p':
			tftp_push = 1;
			break;
		default:
			return COMMAND_ERROR_USAGE;
		}
	}

	if (argc <= optind)
		return COMMAND_ERROR_USAGE;

	source = argv[optind++];

	if (argc == optind)
		dest = basename(source);
	else
		dest = argv[optind];

	if (tftp_push)
		dest = freep = basprintf("%s/%s", TFTP_MOUNT_PATH, dest);
	else
		source = freep = basprintf("%s/%s", TFTP_MOUNT_PATH, source);

	if (!freep)
		return -ENOMEM;

	ret = make_directory(TFTP_MOUNT_PATH);
	if (ret)
		goto err_free;

	ip = net_get_serverip();
	sprintf(ip4_str, "%pI4", &ip);
	ret = mount(ip4_str, "tftp", TFTP_MOUNT_PATH, NULL);
	if (ret)
		goto err_rmdir;

	debug("%s: %s -> %s\n", __func__, source, dest);

	ret = copy_file(source, dest, 1);

	umount(TFTP_MOUNT_PATH);

err_rmdir:
	rmdir(TFTP_MOUNT_PATH);

err_free:
	free(freep);

	return ret;
}

BAREBOX_CMD_HELP_START(tftp)
BAREBOX_CMD_HELP_TEXT("Load (or save) a file via TFTP. SOURCE is a path on server,")
BAREBOX_CMD_HELP_TEXT("server address is taken from the environment (ethX.serverip).")
BAREBOX_CMD_HELP_TEXT("")
BAREBOX_CMD_HELP_TEXT("Options:")
BAREBOX_CMD_HELP_OPT ("-p", "push to TFTP server")
BAREBOX_CMD_HELP_END

BAREBOX_CMD_START(tftp)
	.cmd		= do_tftpb,
	BAREBOX_CMD_DESC("load (or save) a file using TFTP")
	BAREBOX_CMD_OPTS("[-p] SOURCE [DEST]")
	BAREBOX_CMD_GROUP(CMD_GRP_NET)
	BAREBOX_CMD_HELP(cmd_tftp_help)
BAREBOX_CMD_END
