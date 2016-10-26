#import <stdio.h>
#import <stdlib.h>
#include <fcntl.h>

int rand_int(){
	int fd = open("/dev/random", O_RDONLY, 0444);
	unsigned int randint;
	read(fd, &randint, 4);
	close(fd);
	return randint;
}

int main(){
	int i;
	//unmask(0);
	int array[10];
	printf("generating random numbers:");
	for (i = 0; i < 10; i++){
		array[i] = rand_int();
	}
	int fd = open("out.txt", O_RDWR | O_CREAT, 0666);
	for (i = 0; i < 10; i++){
		write(fd, &array[i], sizeof(int));
	}
	return 0;
}