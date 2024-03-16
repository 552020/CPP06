#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
#include <iostream>

// https://stackoverflow.com/questions/13445688/how-to-generate-a-random-number-in-c

// Generates a random Base pointer to either A, B, or C
Base *generate(void)
{
	// Seed the random number generator
	// It is only necessary to seed the random number generator once to increase the randomness of the random numbers
	static bool seeded = false;
	if (!seeded)
	{
		// srand() is used to set the initial seed for the rand() function’s sequence of pseudo-random numbers.
		std::srand(std::time(0)); // Use current time as seed for random generator
		seeded = true;
	}

	// Generate a random number between 0 and 2
	int randNum = std::rand() % 3;

	// Depending on the random number, instantiate A, B, or C
	switch (randNum)
	{
	case 0:
		return new A;
	case 1:
		return new B;
	case 2:
		return new C;
	default:
		return NULL; // This should never happen
	}
}

void identify(Base *p)
{
	if (dynamic_cast<A *>(p) != NULL)
		std::cout << "A" << std::endl;
	else if (dynamic_cast<B *>(p) != NULL)
		std::cout << "B" << std::endl;
	else if (dynamic_cast<C *>(p) != NULL)
		std::cout << "C" << std::endl;
	else
		std::cout << "This will never happen!" << std::endl;
}

void identify(Base &p)
{
	try
	{
		A &a = dynamic_cast<A &>(p);
		(void)a;
		std::cout << "A" << std::endl;
	}
	catch (const std::bad_cast &)
	{
		try
		{
			B &b = dynamic_cast<B &>(p);
			(void)b;
			std::cout << "B" << std::endl;
		}
		catch (const std::bad_cast &)
		{
			try
			{
				C &c = dynamic_cast<C &>(p);
				(void)c;
				std::cout << "C" << std::endl;
			}
			catch (const std::bad_cast &)
			{
				return;
			}
		}
	}
	std::cout << "This will never happen!" << std::endl;
}

int main(void)
{
	// Generate a random Base pointer
	Base *base = generate();

	// Identify the type of the Base pointer
	std::cout << "Identifying the type of the Base pointer:" << std::endl;
	std::cout << "Base pointer is of type ";
	if (dynamic_cast<A *>(base))
		std::cout << "A" << std::endl;
	else if (dynamic_cast<B *>(base))
		std::cout << "B" << std::endl;
	else if (dynamic_cast<C *>(base))
		std::cout << "C" << std::endl;

	std::cout << "Identifying with the pointer:" << std::endl;
	identify(base);
	std::cout << "Identifying with the reference:" << std::endl;
	identify(*base);

	// Delete the Base pointer
	delete base;

	return 0;
}