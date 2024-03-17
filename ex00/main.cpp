#include "ScalarConverter.hpp"

std::string toString(long value);

void testStaticCast()
{

	int a = 42;
	std::cout << "a (int): " << a << std::endl;

	// Implicit Promotion
	double b = a;
	std::cout << "b (double, implicit cast from a): " << b << std::endl;
	// Explicit Promotion
	double c = static_cast<double>(a);
	std::cout << "c (double, explicit static_cast from a): " << c << std::endl;

	double d = 3.14;
	b = b + d;
	std::cout << "b : " << b << std::endl;
	// Implicit Demotion
	int e = b;
	std::cout << "e (int, implicit cast from b): " << e << std::endl;

	// Demotion (Explicit cast)
	// But there is no difference between the implicit and explicit cast in this case
	e = static_cast<int>(b);
	std::cout << "e (int, explicit static_cast from b): " << e << std::endl;
}

void testCharLiterals()
{
	const std::string charLiterals[] = {
		"0",	
		"'0'",
		"'a'",
		"'b'",
		"'9'",
		"c",
		"'\n'",
		"' '",
		"'ab'",
	};
	const int numLiterals = sizeof(charLiterals) / sizeof(charLiterals[0]);

	for (int i = 0; i < numLiterals; ++i)
	{
		std::cout << "Testing literal: " << charLiterals[i] << std::endl;
		ScalarConverter::convert(charLiterals[i]);
		std::cout << std::endl;
	}
}

void testIntLiterals()
{
	const std::string intLiterals[] = {
		toString(static_cast<long>(std::numeric_limits<int>::max()) + 1),
		toString(static_cast<long>(std::numeric_limits<int>::min()) - 1),
		toString(static_cast<long>(std::numeric_limits<char>::max()) + 1),
		toString(static_cast<long>(std::numeric_limits<char>::min()) - 1),
		toString(static_cast<long>(std::numeric_limits<int>::max())),
		toString(static_cast<long>(std::numeric_limits<int>::min())),
		"'0'",
		"12345",
		"-12345",
	};

	const int numLiterals = sizeof(intLiterals) / sizeof(intLiterals[0]);

	for (int i = 0; i < numLiterals; ++i)
	{
		std::cout << "Testing integer literal: " << intLiterals[i] << std::endl;
		ScalarConverter::convert(intLiterals[i]);
		std::cout << std::endl;
	}
}

void testFloatLiterals()
{
	std::cout << "FLT_MAX as double: " << std::fixed << std::setprecision(10) << static_cast<double>(FLT_MAX)
			  << std::endl;
	std::cout << "FLT_MAX as double (wiithout setting precisioin): " << std::fixed << static_cast<double>(FLT_MAX)
			  << std::endl;
	const char *floatLiterals[] = {
		"3.14f", "-123.456f", "-inff", "+inff", "nanf", "123.", "f", ".f", "0.0f", "65.0f", NULL};

	for (int i = 0; floatLiterals[i] != NULL; ++i) 
	{
		std::cout << "Testing float literal: " << floatLiterals[i] << std::endl;
		ScalarConverter::convert(std::string(floatLiterals[i]));
		std::cout << std::endl;
	}
}

void testDoubleLiterals()
{
	const std::string doubleLiterals[] = {
		"0.0",
		"-0.0",
		"123.456",
		"-123.456",
		toString(std::numeric_limits<double>::max()),
		toString(-std::numeric_limits<double>::max()),
		"nan",
		"+inf",
		"-inf",
	};

	const int numLiterals = sizeof(doubleLiterals) / sizeof(doubleLiterals[0]);
	for (int i = 0; i < numLiterals; ++i)
	{
		std::cout << "Testing double literal: " << doubleLiterals[i] << std::endl;
		ScalarConverter::convert(doubleLiterals[i]);
		std::cout << std::endl;
	}
}
// main for testing from the command line
int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		std::cerr << "Usage: " << argv[0] << " <literal>\n";
		return 1;
	}

	ScalarConverter::convert(argv[1]);

	return 0;
}

// main for automated testing
/*
int main(int argc, char *argv[])
{
	if (argc != 1)
	{
		std::cerr << "To use the version which takes input from the command line, please uncomment the other main:\n"
				  << std::endl;
	}
	(void)argv;
	 testStaticCast();
	 testCharLiterals();
	 testIntLiterals();
	 testFloatLiterals();
	testDoubleLiterals();
	return 0;
}
*/
