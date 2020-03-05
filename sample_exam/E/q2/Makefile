# COMP1521 19t2 / Practice Prac Exam / Question 2
# Makefile

CC	= gcc
CFLAGS	= -Wall -Werror -std=gnu11 -g

.PHONY:	all
all:	mkstu stu

mkstu:		mkstu.o Students.o
mkstu.o:	mkstu.c Students.h

stu:		stu.o Students.o
stu.o:		stu.c Students.h

Students.o:	Students.c Students.h

.PHONY: clean
clean:
	-rm -f mkstu mkstu.o
	-rm -f stu stu.o
	-rm -f Students.o

.PHONY: give
give: Students.c
	submit q2
