#include "ScalarConverter.hpp"
#include <iostream>
#include <sstream>
#include <limits> // For std::numeric_limits
#include <cmath>  // For std::isnan, std::isinf
#include <cctype> // For std::isprint

// Private constructor definition (prevents instantiation)
ScalarConverter::ScalarConverter()
{
}

void ScalarConverter::detectAndConvert(const std::string &literal)
{
	// Try to detect and convert the literal as double to handle all numeric cases, including special values.
	char *end;
	double dValue = std::strtod(literal.c_str(), &end);

	// Handling non-numeric literals (including failed conversions to double).
	if (*end != '\0' || (literal.size() > 1 && literal.find_first_not_of("0123456789.-") != std::string::npos))
	{
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: impossible" << std::endl;
		std::cout << "double: impossible" << std::endl;
		return;
	}

	// Handle special float and double cases (nan, inf)
	if (literal == "nan" || literal == "+inf" || literal == "inf" || literal == "-inf")
	{
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		if (literal == "nan")
		{
			std::cout << "float: nanf" << std::endl;
			std::cout << "double: nan" << std::endl;
		}
		else if (literal == "+inf" || literal == "inf")
		{
			std::cout << "float: +inff" << std::endl;
			std::cout << "double: +inf" << std::endl;
		}
		else if (literal == "-inf")
		{
			std::cout << "float: -inff" << std::endl;
			std::cout << "double: -inf" << std::endl;
		}
		return;
	}

	// For normal numeric values, attempt to fit into specific types and handle overflow or impossible cases.
	std::cout << "char: ";
	if (dValue < std::numeric_limits<char>::min() || dValue > std::numeric_limits<char>::max() ||
		dValue != static_cast<int>(dValue))
	{
		std::cout << "impossible";
	}
	else
	{
		char cValue = static_cast<char>(dValue);
		if (std::isprint(cValue))
		{
			std::cout << "'" << cValue << "'";
		}
		else
		{
			std::cout << "Non displayable";
		}
	}

	std::cout << std::endl << "int: ";
	if (dValue < std::numeric_limits<int>::min() || dValue > std::numeric_limits<int>::max() ||
		dValue != static_cast<int>(dValue))
	{
		std::cout << "impossible";
	}
	else
	{
		std::cout << static_cast<int>(dValue);
	}

	std::cout << std::endl << "float: ";
	if (std::isinf(dValue) || std::isnan(dValue))
	{
		std::cout << "impossible";
	}
	else
	{
		std::cout << static_cast<float>(dValue) << 'f';
	}

	std::cout << std::endl << "double: " << dValue << std::endl;

	// Check for char literal
	if (literal.length() == 3 && literal[0] == '\'' && literal[2] == '\'')
	{
		char c = literal[1];
		std::cout << "Original type: char" << std::endl;
		if (std::isprint(c))
		{
			std::cout << "char: '" << c << "'" << std::endl;
		}
		else
		{
			std::cout << "char: Non displayable" << std::endl;
		}
		// Direct conversion from char to other types
		std::cout << "int: " << static_cast<int>(c) << std::endl;
		std::cout << "float: " << static_cast<float>(c) << "f" << std::endl;
		std::cout << "double: " << static_cast<double>(c) << std::endl;
		return;
	}

	// Check if the entire string was consumed during conversion
	if (*end != '\0')
	{
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: impossible" << std::endl;
		std::cout << "double: impossible" << std::endl;
		return;
	}
	// Handling for integer conversions with overflow check.
	long longValue;
	std::istringstream issLong(literal);
	if (issLong >> longValue && issLong.eof())
	{
		std::cout << "Original type: int" << std::endl;
		// Check for overflow when converting long to int.
		if (longValue < std::numeric_limits<int>::min() || longValue > std::numeric_limits<int>::max())
		{
			std::cout << "int: Conversion out of range" << std::endl;
		}
		else
		{
			int intValue = static_cast<int>(longValue);
			std::cout << "char: ";
			if (intValue >= 0 && intValue <= 127)
			{
				std::cout << static_cast<char>(intValue);
			}
			else
			{
				std::cout << "Conversion does not make sense";
			}
			std::cout << ", int: " << intValue << ", float: " << static_cast<float>(intValue)
					  << ", double: " << static_cast<double>(intValue) << std::endl;
		}
		return;
	}

	std::cout << "Unrecognized literal type." << std::endl;
}

void ScalarConverter::convert(const std::string &literal)
{
	detectAndConvert(literal);
}

// Helper function to check and handle special float literals
// bool ScalarConverter::handleSpecialFloatLiterals(const std::string &literal, float &value)
// {
// 	if (literal == "-inff")
// 	{
// 		value = -std::numeric_limits<float>::infinity();
// 		return true;
// 	}
// 	else if (literal == "+inff" || literal == "inff")
// 	{
// 		value = std::numeric_limits<float>::infinity();
// 		return true;
// 	}
// 	else if (literal == "nanf")
// 	{
// 		value = std::numeric_limits<float>::quiet_NaN();
// 		return true;
// 	}
// 	return false;
// }

// New helper function to check and handle special double literals
// bool ScalarConverter::handleSpecialDoubleLiterals(const std::string &literal, double &value)
// {
// 	if (literal == "-inf")
// 	{
// 		value = -std::numeric_limits<double>::infinity();
// 		return true;
// 	}
// 	else if (literal == "+inf" || literal == "inf")
// 	{
// 		value = std::numeric_limits<double>::infinity();
// 		return true;
// 	}
// 	else if (literal == "nan")
// 	{
// 		value = std::numeric_limits<double>::quiet_NaN();
// 		return true;
// 	}
// 	return false;
// }

// Static method to convert string literals to scalar types
// void ScalarConverter::convert(const std::string &literal)
// {
// 	// Check if the literal is a single character
// 	if (literal.length() == 3 && literal[0] == '\'' && literal[2] == '\'')
// 	{
// 		// If the character is printable, print it
// 		char c = literal[1];
// 		if (std::isprint(c))
// 		{
// 			std::cout << "char: " << c << std::endl;
// 		}
// 		// Otherwise, print a message
// 		else
// 		{
// 			std::cout << "The character is not displayable." << std::endl;
// 		}
// 		return;
// 	}
// 	// Check if the literal is a valid int, float, or double
// 	int i;
// 	std::istringstream intStream(literal);
// 	if (intStream >> i)
// {
// 	std::cout << "int: " << i << std::endl;
// }

// float f;
// if (handleSpecialFloatLiterals(literal, f))
// {
// 	std::cout << "float: " << f << std::endl;
// }
// else
// {
// 	std::istringstream floatStream(literal);
// 	if (floatStream >> f)
// 	{
// 		std::cout << "float: " << f << std::endl;
// 	}
// }

// double d;
// if (handleSpecialDoubleLiterals(literal, d))
// {
// 	std::cout << "double: " << d << std::endl;
// }
// else
// {
// 	std::istringstream doubleStream(literal);
// 	if (doubleStream >> d)
// 	{
// 		std::cout << "double: " << d << std::endl;
// 	}
// }
// }
