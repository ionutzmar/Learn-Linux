#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

const char *path = "/dev/input/mice";

int err, errm;
char bytes[3];
int i;
int minus = 0;

void showBinary(char *bts)
{
	for (i = 7; i >= 0; i--)
		fprintf(stdout, "%d ", (bytes[0] & 1 << i) != 0);
	fprintf(stdout, "\n");
	for (i = 7; i >= 0; i--)
		fprintf(stdout, "%d ", (bytes[1] & 1 << i) != 0);
	fprintf(stdout, "\n");
	for (i = 7; i >= 0; i--)
		fprintf(stdout, "%d ", (bytes[2] & 1 << i) != 0);
	fprintf(stdout, "\n");
	fprintf(stdout, "\n");
}

int main(int argc, char const *argv[])
{
	
	int fd = open(path, O_RDONLY);//, O_SYNC);
	errm = errno;
	if (fd < 0)
	{
		fprintf(stderr, "Could not open mouse file: %s\n", strerror(errm));
		return -1;
	}

	//READ
	while(1)
	{
		err = read(fd, bytes, 3);
		errm = errno;
		if (err < 0)
		{
			fprintf(stderr, "Read failed: %s\n", strerror(errm));
			return -1;
		}

		showBinary(bytes);
	}


	err = close(fd);
	errm = errno;
	if (err < 0)
	{
		fprintf(stderr, "Could not close mouse file: %s\n", strerror(errm));
		return -1;
	}
	return 0;
}