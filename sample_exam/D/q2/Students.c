// Students.c ... implementation of Students datatype

#include <sys/types.h>
#include <sys/stat.h>

#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "Students.h"

typedef struct sturec sturec;
typedef struct students students;

struct sturec {
	int id;
	char name[20];
	int degree;
	float wam;
};

struct students {
	int nstu;
	StuRec recs;
};

// build a collection of student records from a file descriptor
Students getStudents (int in)
{
	// Make a skeleton Students struct
	students *ss;
	if ((ss = malloc (sizeof (struct students))) == NULL) {
		fprintf (stderr, "Can't allocate Students\n");
		return NULL;
	}

	// And read in StuRec objects.
	ss->nstu = 0;
	ss->recs = NULL;

	for (;;) {
		sturec rec;
		if (read (in, &rec, sizeof (sturec)) != sizeof(sturec))
			break;

		sturec *recs = realloc (ss->recs, ++ss->nstu * sizeof (sturec));
		if (recs == NULL) {
			fprintf (stderr, "Can't allocate Students\n");
			free (ss);
			return NULL;
		}
		ss->recs = recs;
		ss->recs[ss->nstu - 1] = rec;
	}

	close (in);
	return ss;
}

// show a list of student records pointed to by ss
void showStudents (Students ss)
{
	if (ss == NULL)
		printf ("NULL\n");
	else if (ss->nstu == 0)
		printf ("<no students>\n");
	else
		for (int i = 0; i < ss->nstu; i++)
			showStuRec (&(ss->recs[i]));
}

// show one student record pointed to by s
void showStuRec (StuRec s)
{
	printf ("%7d %s %4d %0.1f\n", s->id, s->name, s->degree, s->wam);
}

// sort students records by WAM, then by name
void sortByWAM (Students ss)
{
	// TODO
}
