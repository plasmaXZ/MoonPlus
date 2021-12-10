#include "PointerUtils.hpp"
#include "LuaPointer.hpp"

LuaPointer::LuaPointer(){}

LuaPointer::LuaPointer(sol::object *ptrValue)
{
	this->ptrValue = ptrValue;
	this->rawValue = ptrValue->as<uintptr_t>();
}

CPed* LuaPointer::ToPedPointer()
{
	return reinterpret_cast<CPed*>(this->rawValue);
}

std::string LuaPointer::ToString()
{
	return utils::PointerToString(this->rawValue);
}