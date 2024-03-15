#include "ScalarConverter.hpp"
#include <iostream>

void test()
{
	std::cout << "Testing character literals:\n";
	ScalarConverter::convert("'a'");
	ScalarConverter::convert("'\n'"); // Non displayable
	std::cout << "\nTesting integer literals:\n";
	ScalarConverter::convert("42");
	ScalarConverter::convert("2147483647");	 // Max int
	ScalarConverter::convert("-2147483648"); // Min int
	std::cout << "\nTesting floating-point literals:\n";
	ScalarConverter::convert("42.0");
	ScalarConverter::convert("-42.0");
	ScalarConverter::convert("3.14");
	std::cout << "\nTesting special floating-point values:\n";
	ScalarConverter::convert("nan");
	ScalarConverter::convert("inf");
	ScalarConverter::convert("-inf");
	std::cout << "\nTesting impossible conversions:\n";
	ScalarConverter::convert("abc"); // Not a valid numeric literal
	ScalarConverter::convert("");	 // Empty string
}

int main(int argc, char *argv[])
{
	if (argc > 1)
	{ // Check if any command-line arguments are provided
		for (int i = 1; i < argc; ++i)
		{ // Start from index 1 to skip the program name
			std::cout << "Converting: " << argv[i] << "\n";
			ScalarConverter::convert(argv[i]);
			std::cout << "\n";
		}
	}
	else
	{ // No arguments provided, display usage message
		std::cout << "Usage: " << argv[0] << " <string_to_convert>...\n";
		std::cout << "Example: " << argv[0] << " 42 'a' 3.14\n";
	}
	// test();

	return 0;
}
