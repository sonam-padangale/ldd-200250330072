#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>


int main(){
	int fd, ret;
	fd= open("/dev/sample0",O_RDWR);// sample0 c 42 0
	if(fd<0){
		perror("Error opening\n");
		return fd;
	}

	return 0;//closed will be called (on fd) implicitly by OS
}
