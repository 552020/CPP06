#include "Serializer.hpp"

uintptr_t Serializer::serialize(Data *ptr)
{
	// uintptr_t uintptr_tPtr;
	// error: incompatible pointer to integer conversion assigning to 'uintptr_t' (aka 'unsigned long') from 'Data *'
	// uintptr_tPtr = ptr;
	// return uintptr_tPtr;
	return reinterpret_cast<uintptr_t>(ptr);
}

Data *Serializer::deserialize(uintptr_t raw)
{
	return reinterpret_cast<Data *>(raw);
}
