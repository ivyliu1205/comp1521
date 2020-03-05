// Simple factorial calculator
//
// Doesn't do error checking
// n < 1 or not a number produce n! = 1

#include <stdio.h>

int main (void)
{
	int n = 0;                      // int n = 0;
	printf ("n  = ");               // print n
	scanf ("%d", &n);               // scan n
	int fac = 1;                    // int fac = 1
	for (int i = 1; i <= n; i++)    // loop:
		fac *= i;                   //  if (i > n) goto end;
	printf ("n! = %d\n", fac);      //  frac = frac * i;
	return 0;                       //  i++:
}                                   //  goto loop;
                                    // end:
