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

int main()
{
	Child1 a; // Reference value

	// Implicit upcast - converting a derived class pointer to a base class pointer
	Parent *b = &a; // Implicit reinterpretation cast

	// Explicit upcast - converting a derived class pointer to a base class pointer with an explicit cast
	Parent *c = (Parent *)&a; // Explicit reinterpretation cast

	// Implicit downcast - NOT allowed, will give a compilation error
	// Child1* e = d; // This would be an implicit downcast, which is not allowed in C++
	// Instead, you must do an explicit downcast:
	Child1 *e = (Child1 *)b; // Explicit downcast - conceptually incorrect without runtime check, as we don't know if
							 // 'b' truly points to a 'Child1'

	// Explicit downcast - even if syntactically correct, it's conceptually incorrect without knowing that 'd' is indeed
	// pointing to a 'Child1' object
	Child2 *f = (Child2 *)
		c; // Explicit downcast - will compile but is dangerous unless you are certain 'c' is pointing to a 'Child2'

	return 0;
}
