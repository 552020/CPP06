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
	long intValue;
	bool floatIsValid;
	bool floatIsPseudo;
	std::string floatLiteral;
	float floatValue;
	bool doubleIsValid;
	bool doubleIsPseudo;
	std::string doubleLiteral;
	double doubleValue;

	ConvertedLiterals()
		: charIsValid(false)
		, charIsPrintable(false)
		, intIsValid(false)
		, floatIsValid(false)
		, floatIsPseudo(false)
		, doubleIsValid(false)
		, doubleIsPseudo(false)
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

bool inputIsValidCharLiteral(const std::string &input)
{
	if (input.length() == 3 && input[0] == '\'' && input[2] == '\'')
		return true;
	return false;
}

bool isValidChar(int value, ConvertedLiterals &literals)
{
	if (value < std::numeric_limits<char>::min() || value > std::numeric_limits<char>::max())
		return false;
	char valueAsUnsignedChar = static_cast<unsigned char>(value);
	literals.charIsPrintable = std::isprint(valueAsUnsignedChar);
	return true;
}

bool inputIsValidIntLiteral(const std::string &input, long &intStructValue)
{
	char *end;
	errno = 0;
	long value = std::strtol(input.c_str(), &end, 10);
	intStructValue = value;

	if (errno == ERANGE || value > std::numeric_limits<int>::max() || value < std::numeric_limits<int>::min() ||
		*end != '\0')
		return false;
	return true;
}

bool inputIsValidFloat(const std::string &input, float &floatStructValue, bool &isPseudo)
{
	if (input == "-inff" || input == "+inff" || input == "nanf")
	{
		isPseudo = true;
		return true;
	}
	if (input == "f" || input == ".f")
		return false;
	if (input.back() != 'f' || input.find('.') == std::string::npos)
		return false;
	std::string withoutSuffix = input.substr(0, input.size() - 1);
	errno = 0;
	char *end;
	double value = std::strtod(withoutSuffix.c_str(), &end);

	if (errno == ERANGE || *end != '\0')
		return false;

	if (std::abs(value) > FLT_MAX)
		return false;
	floatStructValue = static_cast<float>(value);
	return true;
}

bool canConvertFloatOrDoubleToInt(double value)

{
	if (value < static_cast<double>(std::numeric_limits<int>::min()) ||
		value > static_cast<double>(std::numeric_limits<int>::max()))
		return false;

	return true;
}

bool inputIsValidDouble(const std::string &input, double &literalStructValue, bool &isPseudo)
{
	if (input == "+inf" || input == "-inf" || input == "nan")
	{
		isPseudo = true;
		return true;
	}
	char *end;
	double value = std::strtod(input.c_str(), &end);
	if (*end != '\0')
		return false;
	literalStructValue = value;
	return true;
}

bool doubleIsValidFloat(double value)
{
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

bool parseIntLiteral(const std::string &input, ConvertedLiterals &literals)
{
	if (inputIsValidIntLiteral(input, literals.intValue))
	{
		literals.intIsValid = true;
		literals.intLiteral = input;
		literals.floatIsValid = true;
		literals.floatLiteral = input + ".0f";
		literals.doubleIsValid = true;
		literals.doubleLiteral = input + ".0";
		if (isValidChar(static_cast<int>(literals.intValue), literals))
		{
			literals.charIsValid = true;
			literals.charLiteral = "'" + std::string(1, static_cast<char>(std::stoi(input))) + "'";
		}
		printConvertedLiterals(literals);
		return true;
	}
	return false;
}

bool parseFloatLiteral(const std::string &input, ConvertedLiterals &literals)
{
	if (inputIsValidFloat(input, literals.floatValue, literals.floatIsPseudo))
	{
		literals.floatIsValid = true;
		literals.floatLiteral = input;
		literals.doubleIsValid = true;
		literals.doubleLiteral = input.substr(0, input.size() - 1);
		if (!literals.floatIsPseudo && canConvertFloatOrDoubleToInt(literals.floatValue))
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

bool parseDoubleLiteral(const std::string &input, ConvertedLiterals &literals)
{
	if (inputIsValidDouble(input, literals.doubleValue, literals.doubleIsPseudo))
	{
		literals.doubleIsValid = true;
		literals.doubleLiteral = input;
		if (literals.doubleIsPseudo)
		{
			literals.floatIsValid = true;
			literals.floatLiteral = input + "f";
		}
		else
		{
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
		}
		printConvertedLiterals(literals);
		return true;
	}
	return false;
}

void ScalarConverter::convert(const std::string &input)
{

	ConvertedLiterals convertedLiterals;
	if (input.empty())
	{
		printConvertedLiterals(convertedLiterals);
		return;
	}
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
