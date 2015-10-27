#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

const char *path = "/dev/input/mouse1";//"/devices/pci0000:00/0000:00:1d.0/usb2/2-1/2-1.6/2-1.6:1.0/input/input20";//"/dev/input/mouse1"

int err, errm;
char *data;

int main(int argc, char const *argv[])
{
	
	int fd = open(path, O_RDONLY);//, O_SYNC);
	errm = errno;
	if (fd < 0)
	{
		fprintf(stderr, "Could not open mouse file %d\n", errm);
		return -1;
	}

	//READ
	err = ioctl(fd, TIOCGETD, data);
	errm = errno;
	if (err < 0)
	{
		fprintf(stderr, "ioctl failed %d\n", errm);
		return -1;
	}

	fprintf(stdout, "%s\n", data);


	err = close(fd);
	errm = errno;
	if (err < 0)
	{
		fprintf(stderr, "Could not close mouse file %d\n", errm);
		return -1;
	}
	return 0;
}