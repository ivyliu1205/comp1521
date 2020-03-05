# Makefile for COMP1521 Practice Prac Exam

CC=gcc
CFLAGS=-std=c99 -Wall -Werror

all : stu addstu

stu : stu.o
addstu : addstu.o q3.o

stu.o : stu.c Students.h
addstu.o : addstu.c Students.h

clean :
	rm -f stu addstu stu.o addstu.o q3.o
