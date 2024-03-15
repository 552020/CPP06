#ifndef SCALARCONVERTER_H
#define SCALARCONVERTER_H

#include <iostream>
#include <string>

class ScalarConverter
{
  public:
	static void convert(const std::string &input);

  private:
	ScalarConverter(); // Private constructor to prevent instantiation
};

#endif // SCALARCONVERTER_H
