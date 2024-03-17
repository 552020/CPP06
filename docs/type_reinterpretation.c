#include <stdio.h>

int main()
{
	// We creeate a float
	float a = 420.42f;
	// We create a void pointer and we assign the address of the float to it
	void *b = &a;
	// We create another void pointer and we assign the address of the float to it
	void *c = (void *)&a;
	void *d = &a;
	int *e = (int *)d; // Corrected with an explicit cast

	printf("&a: %p, a: %f\n", (void *)&a, a); // Printing address of a and its value
	printf("b: %p\n", b);					  // Printing the void pointer b
	printf("c: %p\n", c);					  // Printing the void pointer c
	printf("d: %p\n", d);					  // Printing the void pointer d
	printf("e: %p, *e: %d\n", (void *)e, *e); // Printing int pointer e and dereferencing it
	// printf("f: %p, *f: %d\n", f, *f); // This line is removed

	return 0;
}
