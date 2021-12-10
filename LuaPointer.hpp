#pragma once
#include <CPed.h>

class LuaPointer
{
private:
	sol::object *ptrValue;
	uintptr_t rawValue;
public:
	LuaPointer();
	LuaPointer(sol::object *ptrValue);
	CPed* ToPedPointer();
	std::string ToString();
};