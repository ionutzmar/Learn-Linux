#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

const char *path = "/dev/input/mouse1";

int err, errm;
char bytesw[]= {8, 1, 2};
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
	
	int fd = open(path, O_RDWR);
	errm = errno;
	if (fd < 0)
	{
		fprintf(stderr, "Could not open mouse file: %s\n", strerror(errm));
		return -1;
	}


	//Write
	while(1)
	{
		err = write(fd, bytesw, 30);
		errm = errno;
		if (err <= 0)
		{
			fprintf(stderr, "Write failed: %s\n", strerror(errm));
			return -1;
		}

		err = read(fd, bytes, 3);
		errm = errno;
		if (err < 0)
		{
			fprintf(stderr, "Read failed: %s\n", strerror(errm));
			return -1;
		}

		if (err == 3)
			showBinary(bytes);
		else
		{
			fprintf(stderr, "Write or Read did not work, err is: %d\n", err);
			showBinary(bytes);
		}

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