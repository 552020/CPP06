#include "Serializer.hpp"
#include <iostream>
#include <iomanip>

void testReinterpretCast()
{

	// long a = 42;
	long a = 1065353217;
	std::cout << "&a: " << &a << std::endl;
	std::cout << "a: " << a << std::endl;

	// error:error: reinterpret_cast from 'long' to 'float' is not allowed
	// float b = reinterpret_cast<float>(a);

	// error: reinterpret_cast from 'float' to 'long' is not allowed
	// long c = reinterpret_cast<long>(f);

	long *longPtr = &a;
	// error: static_cast from 'long *' to 'float *' is not allowed
	// float *floatPtr = static_cast<float *>(longPtr);

	// error: cast from pointer to smaller type 'int' loses information
	// int fakeIntPtr = reinterpret_cast<int>(longPtr);
	uintptr_t fakeIntPtr = reinterpret_cast<uintptr_t>(longPtr);
	(void)fakeIntPtr;
	void *voidPtr = static_cast<void *>(longPtr);
	(void)voidPtr;
	void *anotherVoidPtr = reinterpret_cast<void *>(longPtr);
	(void)anotherVoidPtr;

	float *floatPtr = reinterpret_cast<float *>(longPtr);

	float b = *floatPtr;
	std::cout << "floatPtr: " << floatPtr << std::endl;
	std::cout << "b: " << b << std::endl;
	std::cout << "a: " << a << std::endl;
	// casting float to long directly with static_cast
	a = static_cast<long>(b);
	std::cout << "a: " << a << std::endl;
}

int main()
{
	// testReinterpretCast();
	std::cout << std::endl;
	Data myData(42, "Hello, World!");

	std::cout << "Original Data pointer: " << &myData << std::endl;

	uintptr_t serializedData = Serializer::serialize(&myData);
	Data *deserializedData = Serializer::deserialize(serializedData);

	std::cout << "Deserialized Data pointer: " << deserializedData << std::endl;

	if (deserializedData == &myData)
	{
		std::cout << "It worked!" << std::endl;
		std::cout << "i: " << deserializedData->i << ", str: " << deserializedData->str << std::endl;
	}
	else
		std::cout << "Nope: something went wrong!" << std::endl;

	return 0;
}
