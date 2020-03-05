# COMP1521 19t2 / Practice Prac Exam / Question 2
# Makefile

CC	= gcc
CFLAGS	= -Wall -Werror -std=gnu11 -g

.PHONY:	all
all:	stu

stu:		stu.o Students.o
stu.o:		stu.c Students.h
Students.o:	Students.c Students.h

.PHONY: clean
clean:
	-rm -f stu stu.o Students.o

.PHONY: give
give: Students.c
	submit q2
