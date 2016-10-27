#import <stdio.h>
#import <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>

//Gets one random int from /dev/random
int rand_int(){
	//Gets the int from /dev/random
	int fd = open("/dev/random", O_RDONLY, 0444);
	int randint;
	//Reads 3 bytes
	read(fd, &randint, 4);
	close(fd);
	return randint;
}

//Does most of the work for writings nums to a file
void writenums(int end) {
	int i;
	umask(0);
	//sets up the array that will store everything
	int * array = (int *) malloc(end * sizeof(int));
	printf("Generating random numbers:\n");
	//Generates and displays the random numbers, using the rand_int function to fetch numbers
	for (i = 0; i < end; i++){
		array[i] = rand_int();
		printf("%d: %d\n", i, array[i]);
	}

	//Writers numbers to a file
	printf("Writing numbers to file...\n");
	int fd = open("out", O_RDWR | O_CREAT, 0666);
	//Attempts to create a new file, but if there is already a file there it overrides it
	if (fd == -1) {
		fd = open("out", O_RDWR, 0666);
	}
	for (i = 0; i < end; i++){
		int *h = array[i];
		write(fd, &h, sizeof(int));
	}
	close(fd);
}

//Reads all the values from the file
void readnums(int end) {
	printf("Reading numbers from file...\n");
	int fd = open("out", O_RDONLY, 0444);
	int output;
	//Reprints all values
	printf("Verification that written values were the same:\n");
	for (int i = 0; i < end; i++) {
		read(fd, &output, sizeof(int));
		printf("%d: %d\n",i, output);
	}
	close(fd);
}

int main(){
	int end = 10;
	writenums(end);
	readnums(end);
	return 0;
}
