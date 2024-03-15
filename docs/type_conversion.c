#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

// Function to dump the bits of a 32-bit integer, separated into octets
void dump_32bits_integer(int32_t value)
{
	for (int i = 31; i >= 0; i--)
	{
		putchar('0' + ((value >> i) & 1));
		if (i % 8 == 0)
			putchar(' '); // Separate into octets (every 8 bits)
	}
	putchar('\n');
}

// Function to dump the bits of a 64 - bit double, separating sign, exponent, and mantissa
void dump_64bits_double(double value)
{
	union
	{
		double d;
		uint64_t u;
	} du;
	du.d = value;

	// Print sign bit
	putchar('0' + ((du.u >> 63) & 1));
	putchar(' ');

	// Print exponent bits
	for (int i = 62; i >= 52; i--)
	{
		putchar('0' + ((du.u >> i) & 1));
	}
	putchar(' ');

	// Print mantissa bits
	for (int i = 51; i >= 0; i--)
	{
		putchar('0' + ((du.u >> i) & 1));
		if (i % 4 == 0 && i != 0)
			putchar(' '); // For readability, optionally add a space every 4 bits in the mantissa
	}
	putchar('\n');
}

int main()
{
	int a = 42;
	double b = a;
	double c = (double)a;

	double d = a;
	int e = d;		// Implicit conversion, potential loss of precision
	int f = (int)d; // Explicit casting

	printf("a = %d\n", a);
	dump_32bits_integer(a);

	printf("b = %f\n", b);
	dump_64bits_double(b);

	printf("c = %f\n", c);
	dump_64bits_double(c);

	printf("d = %f\n", d);
	dump_64bits_double(d);

	printf("e = %d\n", e);
	dump_32bits_integer(e);

	printf("f = %d\n", f);
	dump_32bits_integer(f);

	return 0;
}
