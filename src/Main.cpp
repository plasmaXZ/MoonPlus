// MIT License

// Copyright (c) 2012 DK22Pac
// Copyright (c) 2017 FYP
// Copyright (c) 2021 plasma

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "sol.hpp"
#include "Bullet.hpp"
#include "Placeable.hpp"
#include "Entity.hpp"
#include "Physical.hpp"
#include "Sound.hpp"
#include "Weapon.hpp"
#include "Vehicle.hpp"
#include "Automobile.hpp"
#include "Transmission.hpp"
#include "VehicleAudio.hpp"
#include "GameSettings.hpp"
#include "Weather.hpp"
#include "Noise.hpp"
#include "NormalDistribution.hpp"
#include "Ped.hpp"

sol::table open(sol::this_state ts)
{
	sol::state_view lua(ts);
	sol::table module = lua.create_table();
	module["VERSION"] = "0.1.0";
	module["NAME"] = "MoonPlus";

	bullet::initialize(module);
	placeable::initialize(module);
	entity::initialize(module);
	physical::initialize(module);
	vehicle::initialize(module);
	automobile::initialize(module);
	transmission::initialize(module);
	sound::initialize(module);
	vehicle_audio::initialize(module);
	weapon::initialize(module);
	game_settings::initialize(module);
	weather::initialize(module);
	noise::initialize(module);
	distribution::initialize(module);
	ped::initialize(module);

	return module;
}

extern "C" __declspec(dllexport) int luaopen_MoonPlus(lua_State* L)
{
	return (sol::c_call<decltype(&(open)), &(open)>)(L);
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		// pin DLL to prevent unloading
		HMODULE module;
		GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_PIN,
			reinterpret_cast<LPCWSTR>(&DllMain), &module);
	}

	return TRUE;
}