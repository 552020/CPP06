#include <iostream>

#include <iostream>

class Parent
{
}; // Base class
class Child1 : public Parent
{
}; // Child class 1, inherits from Parent
class Child2 : public Parent
{
}; // Child class 2, inherits from Parent
class Unrelated
{
}; // Unrelated class, not part of the hierarchy

void classCast()
{
	Child1 a; // Reference value

	// Implicit upcast - no need for static_cast
	Parent *b = &a;

	// Invalid downcast - would need to be a dynamic_cast in a real scenario
	// Child1 *c = b; // This is not allowed, implicit downcast is not valid

	// Invalid downcast - wrong type, this is conceptually incorrect
	// and will compile but lead to undefined behavior
	Child2 *d = static_cast<Child2 *>(b); // Explicit downcast - very unsafe, incorrect

	// Invalid static_cast - no relationship between Unrelated and Child1 or Parent
	// Unrelated *e = static_cast<Unrelated *>(&a); // Will not compile, unrelated types
	// Instead, the correct way would be not to cast at all since there's no valid conversion
}

void simpleCast()
{
	// Start with an integer value 'a'
	int a = 42;

	// Promotion
	// Implicitly cast 'a' to a double, assigning the value to 'b'
	double b = a;

	// Demotion (Implicit cast)
	// Implicitly cast 'b' back to an int, assigning the value to 'c'
	// Note: This will truncate the double to an integer
	int c = b;

	// Demotion (Explicit cast)
	// Now perform an explicit cast from 'b' to 'd'
	// Use static_cast to explicitly convert 'b' to an integer
	// But there is no difference between the implicit and explicit cast in this case
	int d = static_cast<int>(b);

	std::cout << "a (int): " << a << std::endl;
	std::cout << "b (double, implicit cast from a): " << b << std::endl;
	std::cout << "c (int, implicit cast from b): " << c << std::endl;
	std::cout << "d (int, explicit static_cast from b): " << d << std::endl;
}

int main()
{
	// simpleCast();
	classCast();

	return 0;
}
