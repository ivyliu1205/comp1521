// COMP1521 19t2 ... lab 2 warm-up

#include <stdio.h>
#include <stdlib.h>


static void range_uchar (void);
static void range_char (void);
static void range_uhint (void);
static void range_hint (void);
static void range_int (void);
static void range_uint (void);
static void range_lint (void);
static void range_ulint (void);
static void range_llint (void);
static void range_ullint (void);

int main (void)
{

	range_char ();
	range_uchar ();
	range_hint ();
	range_uhint ();
	range_int ();
	range_uint ();
	range_lint ();
	range_ulint ();
	range_llint ();
	range_ullint ();

	return EXIT_SUCCESS;
}

// Calculate and print the largest and smallest `int` values
static void range_int (void)
{
    int b_int = 8 * sizeof (int); // 4
	int int_min = 1 << (b_int - 1) ;
	int int_max = int_min - 1;
	printf (
		"                   int (%zu bytes): %d ... %d\n",
		sizeof (int), int_min, int_max
	);
}

// Calculate and print the largest and smallest `unsigned int` values
static void range_uint (void)
{
    unsigned int b_uint = 8 * sizeof (unsigned int); // 4
	unsigned int uint_min = 0 << (b_uint - 1);
	unsigned int uint_max = uint_min - 1;
	printf (
		"          unsigned int (%zu bytes): %u ... %u\n",
		sizeof (unsigned int), uint_min, uint_max
	);
}

// Calculate and print the largest and smallest `long int` values
static void range_lint (void)
{
    long int b_long = 8 * sizeof (long int); // 8
	long int long_min = 1UL << (b_long - 1);
	long int long_max = ~long_min;
	printf (
		"              long int (%zu bytes): %ld ... %ld\n",
		sizeof (long int), long_min, long_max
	);
}

// Calculate and print the largest and smallest `unsigned long int` values
static void range_ulint (void)
{
    unsigned long int b_ulong = 8 * sizeof (unsigned long int); // 8
	unsigned long int ulong_min = 0 << (b_ulong - 1);
	unsigned long int ulong_max = ~ulong_min;
	printf (
		"     unsigned long int (%zu bytes): %lu ... %lu\n",
		sizeof (unsigned long int), ulong_min, ulong_max
	);
}

// Calculate and print the largest and smallest `long long int` values
static void range_llint (void)
{
    long long int b_llong = 8 * sizeof (long long int); // 8
	long long int llong_min = 1ULL << (b_llong - 1);
	long long int llong_max = ~llong_min;
	printf (
		"         long long int (%zu bytes): %lld ... %lld\n",
		sizeof (long long int), llong_min, llong_max
	);
}

// Calculate and print the largest and smallest `unsigned long long int` values
static void range_ullint (void)
{
    unsigned long long int b_ullong = 8 * sizeof (unsigned long long int); // 8
	unsigned long long int ullong_min = 0ULL;
	unsigned long long int ullong_max = ~ullong_min;
	printf (
		"unsigned long long int (%zu bytes): %llu ... %llu\n",
		sizeof (unsigned long long int), ullong_min, ullong_max
	);
}

// Calculate and print the largest and smallest `short int` values
static void range_hint (void)
{
    short int b_hint = 8 * sizeof (short int); // 2
	short int hint_min = 1 << (b_hint - 1);
	short int hint_max = ~hint_min;
	printf (
		"             short int (%zu bytes): %hd ... %hd\n",
		sizeof (short int), hint_min, hint_max
	);
}

// Calculate and print the largest and smallest `unsigned short int` values
static void range_uhint (void)
{
    unsigned short int b_uhint = 8 * sizeof (unsigned short int); // 2
	unsigned short int uhint_min = 0 << (b_uhint - 1);
	unsigned short int uhint_max = ~uhint_min;
	printf (
		"    unsigned short int (%zu bytes): %hu ... %hu\n",
		sizeof (unsigned short int), uhint_min, uhint_max
	);
}

// Calculate and print the largest and smallest `char` values
static void range_char (void)
{
    char b_char = 8 * sizeof (char); // 1
	char char_min = 1 << (b_char - 1);
	char char_max = ~char_min;
	printf (
		"                  char (%zu bytes): %d ... %d\n",
		sizeof (char), char_min, char_max
	);
}

// Calculate and print the largest and smallest `unsigned char` values
static void range_uchar (void)
{
    unsigned char b_uchar = 8 * sizeof (unsigned char); // 1
	unsigned char uchar_min = 0 << (b_uchar - 1);
	unsigned char uchar_max = ~uchar_min;
	printf (
		"         unsigned char (%zu bytes): %hhu ... %hhu\n",
		sizeof (unsigned char), uchar_min, uchar_max
	);
}
