#include <stdio.h>

int main()
{
	int a = 42;
	int const *b = &a; // Same as const int *, points to a constant int
	int const *c = &a; // Explicit casting isn't needed here, it's the same situation as b
	int const *d = &a; // Again, pointing to a constant int
	// int *e = d;		   // Explicit cast is required to remove const qualifier // Compile error
	int *f = (int *)d; // Same as e, explicit cast required

	printf("a: %d\n", a);
	printf("b: %p, *b: %d\n", (void *)b, *b);
	printf("c: %p, *c: %d\n", (void *)c, *c);
	printf("d: %p, *d: %d\n", (void *)d, *d);
	printf("e: %p, *e: %d\n", (void *)e, *e);
	printf("f: %p, *f: %d\n", (void *)f, *f);

	return 0;
}
