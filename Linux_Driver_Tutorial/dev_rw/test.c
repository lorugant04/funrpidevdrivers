#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
	int dev = open("/dev/mydevice", O_RDONLY);
	if(dev == -1){
		printf("opening was not possible!\n");
	}
	printf("Opening was successful!\n");
	close(dev);
	return 0;
}
