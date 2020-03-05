// Students.h ... interface to Students datatype

#ifndef STUDENTS_H
#define STUDENTS_H

#include <stdio.h>
#include <stdlib.h>

typedef struct students *Students;
typedef struct sturec *StuRec;

/// build a collection of student records from a file descriptor
Students getStudents (int fd);

/// read text from an input file;
/// write sturec structs to output file
int makeStuFile (char *, char *);

/// show a list of student records pointed to by ss
void showStudents (Students ss);
/// show one student record pointed to by s
void showStuRec (StuRec s);

/// sort a collection of student records by name
void sortByName (Students ss);
/// sort a collection of student records by WAM
void sortByWAM (Students);
/// sort a collection of student records by degree
void sortByDegree (Students);

/// create a new Students object from an original list
/// but where all students have wam >= minWAM
Students filterOnWAM (Students, float minWAM);

/// create a new Students object from an original list
/// but where all students have degree
Students filterOnDegree (Students, int deg);

#endif
