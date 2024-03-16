#include "Serializer.hpp"

uintptr_t Serializer::serialize(Data *ptr)
{
	// gives a compile error cuase uintptr_t is not a pointer type
	// return ptr;
	return reinterpret_cast<uintptr_t>(ptr);
}

Data *Serializer::deserialize(uintptr_t raw)
{
	return reinterpret_cast<Data *>(raw);
}
