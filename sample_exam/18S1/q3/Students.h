// Students.h ... interface to Students datatype

#ifndef STUDENTS_H

typedef struct _student {
	int   id;
	char  name[20];
	int   degree;
	float wam;
} Student;

void addStudent(int, Student);

#endif
