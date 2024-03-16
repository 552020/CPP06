#include "Serializer.hpp"
#include <iostream>
#include <iomanip> // For std::hex

int main()
{
	Data myData(42, "Hello, World!");

	std::cout << "Original Data pointer: " << &myData << std::endl;

	uintptr_t serializedData = Serializer::serialize(&myData);
	Data *deserializedData = Serializer::deserialize(serializedData);

	std::cout << "Deserialized Data pointer: " << deserializedData << std::endl;

	if (deserializedData == &myData)
	{
		std::cout << "Serialization and deserialization successful." << std::endl;
		std::cout << "Data ID: " << deserializedData->i << ", Value: " << deserializedData->str << std::endl;
	}
	else
		std::cout << "Error in serialization/deserialization process." << std::endl;

	return 0;
}
