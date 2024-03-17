#ifndef SCALARCONVERTER_H
#define SCALARCONVERTER_H

#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <iomanip>
#include <cctype> // for std::isprint
#include <cfloat> // for FLT_MAX
#include <climits> // for CHAR_MIN and CHAR_MAX
#include <cstdlib> // for std::strtol
#include <cerrno>  // for errno
#include <cmath>   // for std::abs

class ScalarConverter
{
  public:
	static void convert(const std::string &input);

  private:
	ScalarConverter();
	ScalarConverter(const ScalarConverter &src);
	ScalarConverter &operator=(const ScalarConverter &src);
	~ScalarConverter();
};

#endif
