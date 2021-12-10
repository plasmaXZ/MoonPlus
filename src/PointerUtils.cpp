#include <sstream>
#include "PointerUtils.hpp"

std::string utils::PointerToString(unsigned int rawPtr)
{
	return PointerToString(reinterpret_cast<void*>(rawPtr));
}

std::string utils::PointerToString(void const* ptr)
{
	std::ostringstream address;
	address << ptr;
	return address.str();
}

template <typename T>
T* utils::LuaToPointer(sol::object& object)
{
	return reinterpret_cast<T*>(object.as<uint32>());
}