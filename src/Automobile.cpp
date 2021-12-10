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

#include "Automobile.hpp"

namespace automobile
{
	Automobile::Automobile(CAutomobile* vehicle) : Vehicle(vehicle)
	{
		m_Vehicle = vehicle;
	}

	float Automobile::GetWheelSuspensionCompression(uint8_t wheel)
	{
		return m_Vehicle->wheelsDistancesToGround1[wheel];
	}

	float Automobile::GetWheelRotation(uint8_t wheel)
	{
		return m_Vehicle->m_fWheelRotation[wheel];
	}

	float Automobile::GetWheelPosition(uint8_t wheel)
	{
		return m_Vehicle->field_838[wheel];
	}

	float Automobile::GetWheelSpeed(uint8_t wheel)
	{
		return m_Vehicle->m_fWheelSpeed[wheel]; // maybe it should be multiplied by GAME_UNIT_TO_METERS_SEC
	}

	int32_t Automobile::GetWheelState(uint8_t wheel)
	{
		return m_Vehicle->field_968[wheel];
	}

	float Automobile::GetMoveDirection()
	{
		return m_Vehicle->m_fMoveDirection;
	}

	float Automobile::GetInertiaValue()
	{
		return m_Vehicle->field_80C;
	}

	void Automobile::SetInertiaValue(float inertia)
	{
		m_Vehicle->field_80C = inertia;
	}

	float Automobile::GetTraction()
	{
		return m_Vehicle->m_fCarTraction;
	}

	void Automobile::SetTraction(float traction)
	{
		m_Vehicle->m_fCarTraction = traction;
	}

	float Automobile::GetNitroValue()
	{
		return m_Vehicle->m_fNitroValue;
	}

	void Automobile::SetNitroValue(float value)
	{
		m_Vehicle->m_fNitroValue = value;
	}

	void Automobile::TellToGoTo(float x, float y, float z, float altitudeMin, float altitudeMax)
	{
		eVehicleSoundType type = m_Vehicle->m_vehicleAudio.m_settings.m_nVehicleSoundType;
		if (type == eVehicleSoundType::VEHICLE_SOUND_HELI)
			m_Vehicle->TellHeliToGoToCoors(x, y, z, altitudeMin, altitudeMax);
		else if (type == eVehicleSoundType::VEHICLE_SOUND_PLANE)
			m_Vehicle->TellPlaneToGoToCoors(x, y, z, altitudeMin, altitudeMax);
	}

	void Automobile::PlaceOnRoadProperly()
	{
		m_Vehicle->PlaceOnRoadProperly();
	}

	Automobile FromMemory(uintptr_t address)
	{
		return Automobile(reinterpret_cast<CAutomobile*>(address));
	}

	void initialize(sol::table& module)
	{
		module.new_usertype<Automobile>("automobile",
			sol::base_classes, sol::bases<Placeable, Entity, Physical, Vehicle>(),
			"from_memory", sol::factories(&FromMemory),
			"get_wheel_suspension_compression", &Automobile::GetWheelSuspensionCompression,
			"get_wheel_rotation", &Automobile::GetWheelRotation,
			"get_wheel_position", &Automobile::GetWheelPosition,
			"get_wheel_speed", &Automobile::GetWheelSpeed,
			"get_wheel_state", &Automobile::GetWheelState,
			"get_move_direction", &Automobile::GetMoveDirection,
			"inertia_value", sol::property(&Automobile::GetInertiaValue,
					&Automobile::SetInertiaValue),
			"traction", sol::property(&Automobile::GetTraction, &Automobile::SetTraction),
			"nitro_value", sol::property(&Automobile::GetNitroValue, &Automobile::SetNitroValue),
			"tell_to_go_to", &Automobile::TellToGoTo,
			"place_on_road_properly", &Automobile::PlaceOnRoadProperly);
	}
}
