#include "ScalarConverter.hpp"
#include <iostream>
#include <string>
#include <iomanip>
#include <cfloat> // For FLT_MAX

void testCharLiterals()
{
	const std::string charLiterals[] = {
		"0",	// Invalid (no single quotes)
		"'0'",	// Valid and printable
		"'a'",	// Valid and printable
		"'b'",	// Valid and printable
		"'9'",	// Valid and printable
		"c",	// Invalid (no single quotes)
		"'\n'", // Valid but non-displayable (if you decide to test non-printable)
		"' '",	// Valid and printable (space)
		"'z'",	// Valid and printable
		"''",	// Invalid (empty character)
		"'ab'", // Invalid (more than one character)
	};
	const int numLiterals = sizeof(charLiterals) / sizeof(charLiterals[0]);

	for (int i = 0; i < numLiterals; ++i)
	{
		std::cout << "Testing literal: " << charLiterals[i] << std::endl;
		ScalarConverter::convert(charLiterals[i]);
		std::cout << std::endl; // Separate test outputs for readability
	}
}

void testIntLiterals()
{
	const std::string intLiterals[] = {
		std::to_string(static_cast<long>(std::numeric_limits<int>::max()) + 1),
		std::to_string(static_cast<long>(std::numeric_limits<int>::min()) - 1),
		std::to_string(static_cast<long>(std::numeric_limits<char>::max()) + 1),
		std::to_string(static_cast<long>(std::numeric_limits<char>::min()) - 1),
		std::to_string(static_cast<long>(std::numeric_limits<int>::max())),
		std::to_string(static_cast<long>(std::numeric_limits<int>::min())),
		std::to_string(0),
		"12345",
		"-12345",
	};

	const int numLiterals = sizeof(intLiterals) / sizeof(intLiterals[0]);

	for (int i = 0; i < numLiterals; ++i)
	{
		std::cout << "Testing integer literal: " << intLiterals[i] << std::endl;
		ScalarConverter::convert(intLiterals[i]);
		std::cout << std::endl; // Separate test outputs for readability
	}
}

void testFloatLiterals()
{
	std::cout << "FLT_MAX as double: " << std::fixed << std::setprecision(10) << static_cast<double>(FLT_MAX)
			  << std::endl;
	std::cout << "FLT_MAX as double (wihtou setting precisioin): " << std::fixed << static_cast<double>(FLT_MAX)
			  << std::endl;
	const char *floatLiterals[] = {
		"3.14f",	 // Valid
		"-123.456f", // Valid
		"1.0e20f",	 // Valid, large number
		"-inff",	 // Negative infinity
		"+inff",	 // Positive infinity
		"nanf",		 // Not a number
		"123.",		 // Invalid, missing 'f' suffix
		"f",		 // Invalid, no digits
		".f",		 // Invalid, no digits before the dot
		"0.0f",		 // Valid
		"65.0f",	 // Valid
		NULL		 // Sentinel value to mark the end of the array
	};

	for (int i = 0; floatLiterals[i] != NULL; ++i)
	{
		std::cout << "Testing float literal: " << floatLiterals[i] << std::endl;
		ScalarConverter::convert(std::string(floatLiterals[i]));
		std::cout << std::endl; // Separate test outputs for readability
	}
}

void testDoubleLiterals()
{
	const std::string doubleLiterals[] = {
		"0.0",
		"-0.0",
		"123.456",
		"-123.456",
		std::to_string(std::numeric_limits<double>::max()),	 // Maximum double
		std::to_string(-std::numeric_limits<double>::max()), // Minimum double (negative)
		"1.7976931348623157e+308",							 // Another representation of the maximum double value
		"-1.7976931348623157e+308",							 // Negative max double value representation
		"1e309",											 // Beyond maximum double, should result in infinity
		"-1e309",											 // Beyond minimum double, should result in -infinity
		"nan",
		"+inf",
		"-inf",
	};

	const int numLiterals = sizeof(doubleLiterals) / sizeof(doubleLiterals[0]);
	for (int i = 0; i < numLiterals; ++i)
	{
		std::cout << "Testing double literal: " << doubleLiterals[i] << std::endl;
		ScalarConverter::convert(doubleLiterals[i]);
		std::cout << std::endl; // Separate test outputs for readability
	}
}

// int main(int argc, char *argv[])
// {
// 	if (argc != 2)
// 	{
// 		std::cerr << "Usage: " << argv[0] << " <literal>\n";
// 		return 1;
// 	}

// 	ScalarConverter::convert(argv[1]);

// 	return 0;
// }

int main(int argc, char *argv[])
{
	if (argc != 1)
	{
		std::cerr << "To use the version which takes input from the command line, please uncomment the other main:\n"
				  << std::endl;
	}
	(void)argv;
	// testCharLiterals();
	// testIntLiterals();
	// testFloatLiterals();
	testDoubleLiterals();
	return 0;
}
