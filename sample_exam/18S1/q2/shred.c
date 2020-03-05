// COMP1521 18s2 Exam Q2
// Main program
// - infd = open argv[1] for reading
// - outfd = open argv[1].shredded for writing
// - call shred function to
//   - read blocks from infd
//   - write random blocks to outfd

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

extern void shred(int infd, int outfd);

int main(int argc, char *argv[])
{
	char in_name[200];  // input file name
	int  infd;          // input file descriptor
	char out_name[200]; // output file name
	int  outfd;         // output file descriptor

	if (argc < 2) {
		printf("Usage: %s File\n", argv[0]);
		return 1;
	}
	strcpy(in_name, argv[1]);
	strcpy(out_name, argv[1]);
	strcat(out_name, ".out");
	if ((infd = open(in_name, O_RDONLY)) < 0) {
		printf("Can't read %s\n", in_name);
		return 1;
	}
	if ((outfd = open(out_name, O_WRONLY|O_CREAT|O_TRUNC, 0644)) < 0) {
		perror("Can't write");
		printf("Can't write %s\n", out_name);
		return 1;
	}
	int seed = 1;
	for (int i = 0; i < strlen(in_name); i++) seed *= in_name[i];
	srand(seed); // make sure "random" #'s are consistent
	shred(infd, outfd); // write random blocks
	close(infd);
	close(outfd);
	return 0;
}
