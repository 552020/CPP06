#include "ScalarConverter.hpp"
#include <cctype>  // for std::isprint
#include <climits> // for CHAR_MIN and CHAR_MAX
#include <cstdlib> // for std::strtol
#include <cerrno>  // for errno

void ScalarConverter::convert(const std::string &input)
{
	// Case 1: Input is a single character
	if (input.length() == 1 && std::isprint(input[0]) && !std::isdigit(input[0]))
	{
		std::cout << "char: '" << input[0] << "'\n";
		return;
	}

	// Case 2: Attempt to convert input to an integer for char range checking
	char *end;
	long int num = std::strtol(input.c_str(), &end, 10);

	// Check if conversion was successful and within char range
	if (*end == '\0' && errno != ERANGE && num >= CHAR_MIN && num <= CHAR_MAX)
	{
		if (std::isprint(static_cast<char>(num)))
		{
			std::cout << "char: '" << static_cast<char>(num) << "'\n";
		}
		else
		{
			std::cout << "char: Non displayable\n";
		}
	}
	else
	{
		std::cout << "char: impossible\n";
	}
}
