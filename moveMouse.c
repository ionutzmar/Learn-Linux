#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main() {
	int i;
    unsigned char a[5]={0, 0xff, 0, 0x28, 0xff};
    int fp = open ("/dev/input/mice", O_WRONLY);
    if(!fp)printf("open error:%s\n", strerror(errno));
    for(i = 0; i < 10; i++)
        printf("write:%d\t\t%s\n", write(fp, a, 5), strerror(errno));
    close(fp);
    return 0;
}