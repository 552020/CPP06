#include "ScalarConverter.hpp"
#include <iostream>
#include <string>

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
	testCharLiterals();
	return 0;
}
