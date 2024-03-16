#include <iostream>
#include <exception>

class Parent
{
  public:
	// Virtual destructor to enable polymorphism
	virtual ~Parent()
	{
	}
};

class Child1 : public Parent
{
  public:
	void greet()
	{
		std::cout << "Hello from Child1!" << std::endl;
	}
};

class Child2 : public Parent
{
};

int main()
{
	Parent *parentPtr = new Child1(); // Upcast, safe and implicit

	// Safe downcast with dynamic_cast
	Child1 *child1Ptr = dynamic_cast<Child1 *>(parentPtr);
	if (child1Ptr != nullptr)
	{
		child1Ptr->greet(); // Success: parentPtr actually points to a Child1
	}
	else
	{
		std::cout << "Downcast to Child1 failed." << std::endl;
	}

	// Attempt to downcast to the wrong type
	Child2 *child2Ptr = dynamic_cast<Child2 *>(parentPtr);
	if (child2Ptr != nullptr)
	{
		// This block will not execute because parentPtr does not point to a Child2
		std::cout << "Downcast to Child2 succeeded." << std::endl;
	}
	else
	{
		std::cout << "Downcast to Child2 failed." << std::endl;
	}

	delete parentPtr; // Clean up

	// Example with references
	try
	{
		Parent &parentRef = *new Child1();					   // Upcast, safe and implicit
		Child1 &child1Ref = dynamic_cast<Child1 &>(parentRef); // Safe downcast
		child1Ref.greet();									   // Success

		delete &parentRef; // Clean up
	}
	catch (const std::bad_cast &e)
	{
		std::cout << "Downcast failed: " << e.what() << std::endl;
	}

	return 0;
}
