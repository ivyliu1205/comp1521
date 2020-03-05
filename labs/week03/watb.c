// COMP1521 19t2 ... lab 03: where are the bits?
// watb.c: determine bit-field order

#include <stdio.h>
#include <stdlib.h>

struct _bit_fields {
	unsigned int a : 4;
	unsigned int b : 8;
	unsigned int c : 20;
};

int main (void)
{
	struct _bit_fields x;

	printf ("%zu\n", sizeof (x));
	
	unsigned char *p;
	x.a = 0;
	x.b = 0;
	x.c = 0;
	
	// p represent the beginning of x
	p = (unsigned char *)&x;
	
	printf("x: %p\n", &x);
	printf("p: %p\n", &p);
	
	(*p)++;
	
	printf("a: %d, b: %d,c: %d\n", x.a, x.b, x.c);
    // Only a changed, so a is at the beginning of x
    // so c-b-a
    
	return EXIT_SUCCESS;
}


