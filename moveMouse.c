#include <stdio.h>
#include <unistd.h>
#include <linux/input.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <string.h>


int main() {

	int i, errm;
  	struct input_event event, event_end;

  	int fd = open("/dev/input/event4", O_RDWR);
	if (fd < 0)
	errm = errno;
	if (fd < 0)
	{
		fprintf(stderr, "Could not open mouse file: %s\n", strerror(errm));
		return -1;
	}


	gettimeofday(&event.time, NULL);
	event.type = EV_REL;
	event.code = REL_Y;
	event.value = 100;
	gettimeofday(&event_end.time, NULL);
	event_end.type = EV_SYN;
	event_end.code = SYN_REPORT;
	event_end.value = 0;
	for (i = 0; i < 5; i++) 
	{
    	write(fd, &event, sizeof(event));// Move the mouse
		write(fd, &event_end, sizeof(event_end));// Show move
    	sleep(1);// wait
    }
	close(fd);
	return 0;
}