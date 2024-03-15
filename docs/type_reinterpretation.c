#include <stdio.h>

int main()
{
	float a = 420.42f;
	void *b = &a;
	void *c = (void *)&a;
	void *d = &a;
	int *e = (int *)d; // Corrected with an explicit cast
	// int *f = (int *)a; // This line is removed because it's incorrect

	printf("&a: %p, a: %f\n", (void *)&a, a); // Printing address of a and its value
	printf("b: %p\n", b);					  // Printing the void pointer b
	printf("c: %p\n", c);					  // Printing the void pointer c
	printf("d: %p\n", d);					  // Printing the void pointer d
	printf("e: %p, *e: %d\n", (void *)e, *e); // Printing int pointer e and dereferencing it
	// printf("f: %p, *f: %d\n", f, *f); // This line is removed

	return 0;
}
