#pragma once
#include <string>
#include "sol.hpp"

namespace utils
{
	std::string PointerToString(unsigned int rawPtr);
	std::string PointerToString(void const* ptr);
	template <typename T>
	T* LuaToPointer(sol::object& object);
}