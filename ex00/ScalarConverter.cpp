#include "ScalarConverter.hpp"
#include <cctype> // for std::isprint
#include <cfloat> // for FLT_MAX

#include <climits> // for CHAR_MIN and CHAR_MAX
#include <cstdlib> // for std::strtol
#include <cerrno>  // for errno
#include <cmath>   // for std::abs
#include <iostream>

struct ConvertedLiterals
{
	bool charIsValid;
	bool charIsPrintable;
	std::string charLiteral;
	bool intIsValid;
	std::string intLiteral;
	bool floatIsValid;
	std::string floatLiteral;
	float floatValue;
	bool doubleIsValid;
	std::string doubleLiteral;
	double doubleValue;

	ConvertedLiterals()
		: charIsValid(false), charIsPrintable(false), intIsValid(false), floatIsValid(false), doubleIsValid(false)
	{
	}
};

void printConvertedLiterals(const ConvertedLiterals &literals)
{

	std::cout << "char: ";
	std::cout << (literals.charIsValid ? (literals.charIsPrintable ? literals.charLiteral : "Non displayable")
									   : "impossible")
			  << "\n";
	std::cout << "int: " << (literals.intIsValid ? literals.intLiteral : "impossible") << "\n";
	std::cout << "float: " << (literals.floatIsValid ? literals.floatLiteral : "impossible") << "\n";
	std::cout << "double: " << (literals.doubleIsValid ? literals.doubleLiteral : "impossible") << "\n";
}

// Please note that non displayable characters shouldn’t be used as inputs.
bool inputIsValidCharLiteral(const std::string &input)
{
	if (input.length() == 3 && input[0] == '\'' && input[2] == '\'')
		return true;
	return false;
}

bool isValidChar(int value, ConvertedLiterals &literals)
{
	// if (value < CHAR_MIN || value > CHAR_MAX)
	if (value < std::numeric_limits<char>::min() || value > std::numeric_limits<char>::max())
		return false;
	literals.charIsPrintable = std::isprint(static_cast<unsigned char>(value));
	return true;
}

bool inputIsValidIntLiteral(const std::string &input)
{
	char *end;
	errno = 0;										   // Reset errno before the conversion
	long value = std::strtol(input.c_str(), &end, 10); // Base 10 for decimal integers

	// Check conversion success, range, and that the entire input was consumed
	if (errno == ERANGE || value > INT_MAX || value < INT_MIN || *end != '\0')
	{
		return false; // Conversion failed or out of int range
	}
	return true;
}

bool inputIsValidFloat(const std::string &input, float &literalStructValue)
{
	if (input == "-inff" || input == "+inff" || input == "nanf")
	{
		if (input == "nanf")
		{
			literalStructValue = NAN;
		}
		else if (input == "-inff")
		{
			// std::numeric_limits<float>::infinity()
			literalStructValue = -INFINITY;
		}
		else if (input == "+inff")
		{
			literalStructValue = INFINITY;
		}
		return true; // Directly recognize these special float literals
	}
	if (input.empty() || input == "f" || input == ".f")
	{
		return false; // Reject empty strings, lone 'f', and ".f" as invalid
	}

	// Check for 'f' at the end and at least one decimal point before it
	if (input.back() != 'f' || input.find('.') == std::string::npos)
	{
		return false;
	}
	std::string withoutSuffix = input.substr(0, input.size() - 1); // Remove 'f' suffix

	errno = 0; // Reset errno to 0 before conversion
	char *end;
	double value = std::strtod(withoutSuffix.c_str(), &end);

	if (errno == ERANGE || *end != '\0')
	{
		return false; // Conversion failed or the entire input was not consumed
	}

	if (std::abs(value) > FLT_MAX)
	{
		return false; // Value is outside the float range
	}

	// Optionally, you could add further checks here, such as ensuring 'value'
	// is within the representable range of a float, but std::strtod already
	// handles numeric limits and sets errno for underflow and overflow.
	literalStructValue = static_cast<float>(value);
	return true; // Passed all checks
}

bool canConvertFloatOrDoubleToInt(double value)

{
	// Check for NaN or infinity
	if (std::isnan(value) || std::isinf(value))
		return false;

	// Check if value is within the range of int
	if (value < static_cast<double>(std::numeric_limits<int>::min()) ||
		value > static_cast<double>(std::numeric_limits<int>::max()))
		return false;

	return true;
}

bool inputIsValidDouble(const std::string &input, double &literalStructValue)
{
	// Manually handle special double literals
	if (input == "-inf")
	{
		literalStructValue = -std::numeric_limits<double>::infinity();
		return true;
	}
	else if (input == "+inf" || input == "inf")
	{
		literalStructValue = std::numeric_limits<double>::infinity();
		return true;
	}
	else if (input == "nan")
	{
		// C++98 does not have a standard way to set a variable to NaN, so this might
		// depend on your compiler/platform. As an example, you could use 0.0 / 0.0,
		// but be aware this is not portable or recommended for production code.
		literalStructValue = 0.0 / 0.0;
		return true;
	}

	char *end;
	double value = std::strtod(input.c_str(), &end);

	if (*end != '\0')
	{
		return false; // Conversion failed or the entire input was not consumed
	}

	literalStructValue = value;
	return true; // Passed all checks, input is a valid double
}

bool doubleIsValidFloat(double value)
{
	if (std::isnan(value) || std::isinf(value))
	{
		// Special float values for NaN and infinity are representable
		return true;
	}
	return value >= -FLT_MAX && value <= FLT_MAX;
}

bool parseCharLiteral(const std::string &input, ConvertedLiterals &literals)
{
	if (inputIsValidCharLiteral(input))
	{
		literals.charIsValid = true;
		isValidChar(static_cast<int>(input[1]), literals);
		literals.charLiteral = input;
		literals.intIsValid = true;
		literals.intLiteral = std::to_string(static_cast<int>(input[1]));
		literals.floatIsValid = true;
		literals.floatLiteral = literals.intLiteral + ".0f";
		literals.doubleIsValid = true;
		literals.doubleLiteral = literals.intLiteral + ".0";
		printConvertedLiterals(literals);
		return true;
	}
	return false;
}

bool parseFloatLiteral(const std::string &input, ConvertedLiterals &literals)
{
	if (inputIsValidFloat(input, literals.floatValue))
	{
		literals.floatIsValid = true;
		literals.floatLiteral = input;
		literals.doubleIsValid = true;
		literals.doubleLiteral = input.substr(0, input.size() - 1); // Remove 'f' suffix
		if (canConvertFloatOrDoubleToInt(literals.floatValue))
		{
			literals.intIsValid = true;
			literals.intLiteral = std::to_string(static_cast<int>(literals.floatValue));
			if (isValidChar(static_cast<int>(literals.floatValue), literals))
			{
				literals.charIsValid = true;
				literals.charLiteral =
					"'" + std::string(1, static_cast<char>(static_cast<int>(literals.floatValue))) + "'";
			}
		}
		printConvertedLiterals(literals);
		return true;
	}
	return false;
}

bool parseIntLiteral(const std::string &input, ConvertedLiterals &literals)
{
	if (inputIsValidIntLiteral(input))
	{
		literals.intIsValid = true;
		literals.intLiteral = input;
		literals.floatIsValid = true;
		literals.floatLiteral = input + ".0f";
		literals.doubleIsValid = true;
		literals.doubleLiteral = input + ".0";
		if (isValidChar(std::stoi(input), literals))
		{
			literals.charIsValid = true;
			literals.charLiteral = "'" + std::string(1, static_cast<char>(std::stoi(input))) + "'";
		}
		printConvertedLiterals(literals);
		return true;
	}
	return false;
}

bool parseDoubleLiteral(const std::string &input, ConvertedLiterals &literals)
{
	if (inputIsValidDouble(input, literals.doubleValue))
	{
		literals.doubleIsValid = true;
		literals.doubleLiteral = input;
		if (doubleIsValidFloat(literals.doubleValue))
		{
			literals.floatIsValid = true;
			literals.floatLiteral = input + "f";
		}
		if (canConvertFloatOrDoubleToInt(literals.doubleValue))
		{
			literals.intIsValid = true;
			literals.intLiteral = std::to_string(static_cast<int>(literals.doubleValue));
			if (isValidChar(static_cast<int>(literals.doubleValue), literals))
			{
				literals.charIsValid = true;
				literals.charLiteral =
					"'" + std::string(1, static_cast<char>(static_cast<int>(literals.doubleValue))) + "'";
			}
		}
		printConvertedLiterals(literals);
		return true;
	}
	return false;
}

void ScalarConverter::convert(const std::string &input)
{

	ConvertedLiterals convertedLiterals;

	if (parseCharLiteral(input, convertedLiterals))
		return;
	if (parseIntLiteral(input, convertedLiterals))
		return;
	if (parseFloatLiteral(input, convertedLiterals))
		return;
	if (parseDoubleLiteral(input, convertedLiterals))
		return;
	printConvertedLiterals(convertedLiterals);
}
