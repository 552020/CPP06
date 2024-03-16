#include "Serializer.hpp"
#include <iostream>

int main()
{
	// Create a Data instance
	Data myData(42, "Hello, World!");

	// Serialize the Data instance
	uintptr_t serializedData = Serializer::serialize(&myData);

	// Deserialize back to a Data pointer
	Data *deserializedData = Serializer::deserialize(serializedData);

	// Test to ensure they are the same
	if (deserializedData == &myData)
	{
		std::cout << "Serialization and deserialization successful." << std::endl;
		std::cout << "Data ID: " << deserializedData->i << ", Value: " << deserializedData->str << std::endl;
	}
	else
	{
		std::cout << "Error in serialization/deserialization process." << std::endl;
	}

	return 0;
}
