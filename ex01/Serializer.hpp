// Serializer.hpp
#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include <string>
#include <stdint.h>

struct Data
{
	int i;
	std::string str;

	Data(int i, const std::string &str) : i(i), str(str)
	{
	}
};

class Serializer
{
  public:
	static std::size_t serialize(Data *ptr);
	static Data *deserialize(uintptr_t raw);

  private:
	Serializer();
	Serializer(const Serializer &);
	virtual ~Serializer();
	Serializer &operator=(const Serializer &);
};

#endif
