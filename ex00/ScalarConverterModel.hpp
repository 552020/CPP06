#ifndef SCALARCONVERTER_H
#define SCALARCONVERTER_H

#include <string>

class ScalarConverter
{
  private:
	ScalarConverter();

	// static bool handleSpecialFloatLiterals(const std::string &literal, float &value);
	// static bool ScalarConverter::handleSpecialDoubleLiterals(const std::string &literal, double &value);
	// Detects the type of the literal and performs the conversions.
	static void detectAndConvert(const std::string &literal);

  public:
	static void convert(const std::string &literal);
};

#endif // SCALARCONVERTER_H
