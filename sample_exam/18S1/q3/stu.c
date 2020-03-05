// stu.c ... display student records

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "Students.h"

int main(int argc, char *argv[])
{
	if (argc < 2) {
		fprintf(stderr, "Usage: %s StuFile\n", argv[0]);
		return 1;
	}

	// attempt to open named file
	int fd;  // input file descriptor
    if ((fd = open(argv[1], O_RDONLY)) < 0) {
		fprintf(stderr, "Can't open %s\n", argv[1]);
		return 1;
	}

	// display student records
	Student s;
	while (read(fd, &s, sizeof(Student)) > 0)
		printf("%7d %s %4d %0.1f\n", s.id, s.name, s.degree, s.wam);

    return 0;
}
