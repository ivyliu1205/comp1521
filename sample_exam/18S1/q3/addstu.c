// addstu.c ... add a new record into a file of student records

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "Students.h"

int main(int argc, char *argv[])
{
	char fname[100]; // name of input file
	int fd;          // input file descriptor
	Student stu;     // student to be added

	if (argc < 6) {
		printf("Usage: %s StuFile zID Name Program WAM\n", argv[0]);
		return 1;
	}

	// process command-line args

	strcpy(fname, argv[1]);
	if ((fd = open(fname, O_RDWR)) < 0) {
		printf("Can't open input file %s\n", fname);
		return 1;
	}
	stu.id = atoi(argv[2]);
	for (int i = 0; i < 20; i++) stu.name[i] = '\0';
	strcpy(stu.name, argv[3]);
	stu.degree = atoi(argv[4]);
	sscanf(argv[5], "%f", &stu.wam);

	// add student record into file
	addStudent(fd, stu);

	close(fd);

	return 0;
}
