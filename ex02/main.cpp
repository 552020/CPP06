#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
#include <iostream>

// https://stackoverflow.com/questions/13445688/how-to-generate-a-random-number-in-c

Base *generate(void)
{
	static bool seeded = false;
	if (!seeded)
	{
		std::srand(std::time(0));
		seeded = true;
	}

	int randNum = std::rand() % 3;

	std::cout << "Generated instance of ";
	switch (randNum)
	{
	case 0:
		std::cout << "A!" << std::endl;
		return new A;
	case 1:
		std::cout << "B!" << std::endl;
		return new B;
	case 2:
		std::cout << "C!" << std::endl;
		return new C;
	default:
		std::cout << "This should not have happen!" << std::endl;
		return NULL;
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
	catch (const std::bad_cast &e)
	{
		try
		{
			std::cout << "Error for A: " << e.what() << std::endl;
			B &b = dynamic_cast<B &>(p);
			(void)b;
			std::cout << "B" << std::endl;
		}
		catch (const std::bad_cast &e)
		{
			try
			{
				std::cout << "Error for B: " << e.what() << std::endl;
				C &c = dynamic_cast<C &>(p);
				(void)c;
				std::cout << "C" << std::endl;
				return;
			}
			catch (const std::bad_cast &e)
			{
				std::cout << "This will never happen! But it did!" << std::endl;
				std::cout << "Error for C: " << e.what() << std::endl;
				return;
			}
		}
	}
}

int main(void)
{
	Base *base = generate();

	std::cout << "\nIdentifying via pointer:" << std::endl;
	identify(base);
	std::cout << "\nIdentifying via reference:" << std::endl;
	identify(*base);

	delete base;

	return 0;
}