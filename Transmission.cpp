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

#include "Transmission.hpp"

namespace transmission
{
	Gear::Gear(tTransmissionGear* gear)
	{
		m_Gear = gear;
	}

	float Gear::GetMaxSpeed()
	{
		return GameUnitToMs(m_Gear->m_fMaxVelocity);
	}

	void Gear::SetMaxSpeed(float speed)
	{
		m_Gear->m_fMaxVelocity =  MsToGameUnit(speed);
	}

	float Gear::GetChangeUpSpeed()
	{
		return GameUnitToMs(m_Gear->m_fChangeUpVelocity);
	}

	void Gear::SetChangeUpSpeed(float speed)
	{
		m_Gear->m_fChangeUpVelocity = MsToGameUnit(speed);
	}

	float Gear::GetChangeDownSpeed()
	{
		return GameUnitToMs(m_Gear->m_fChangeDownVelocity);
	}

	void Gear::SetChangeDownSpeed(float speed)
	{
		m_Gear->m_fChangeDownVelocity = MsToGameUnit(speed);
	}

	Transmission::Transmission(cTransmission* transmission)
	{
		m_Transmission = transmission;
	}

	Gear Transmission::GetGear(uint32_t gear)
	{
		return Gear(&m_Transmission->m_aGears[gear]);
	}

	uint8_t Transmission::GetTractionType()
	{
		return m_Transmission->m_nDriveType;
	}

	void Transmission::SetTractionType(uint8_t type)
	{
		m_Transmission->m_nDriveType = type;
	}

	uint8_t Transmission::GetEngineType()
	{
		return m_Transmission->m_nEngineType;
	}

	void Transmission::SetEngineType(uint8_t type)
	{
		m_Transmission->m_nEngineType = type;
	}

	float Transmission::GetMinGearVelocity()
	{
		return GameUnitToMs(m_Transmission->m_fMinGearVelocity);
	}

	void Transmission::SetMinGearVelocity(float min)
	{
		m_Transmission->m_fMinGearVelocity = MsToGameUnit(min);
	}

	void Transmission::InitGearRatios()
	{
		m_Transmission->InitGearRatios();
	}

	uint8_t Transmission::CalculateGearForSimpleCar(float speed, uint8_t currentGear)
	{
		m_Transmission->CalculateGearForSimpleCar(MsToGameUnit(speed), currentGear);
		return currentGear;
	}

	float Transmission::CalculateDriveAcceleration(float gas, uint8_t currentGear,
		float gearChangeCount, float speed, float unk1, float unk2, bool allWheelsOnGround,
		uint8_t handlingCheat)
	{
		speed *= METERS_SEC_TO_GAME_UNIT;

		return m_Transmission->CalculateDriveAcceleration(gas, currentGear, gearChangeCount, speed,
			unk1, unk2, allWheelsOnGround, handlingCheat);
	}

	Transmission TransmissionFromMemory(uintptr_t address)
	{
		return Transmission(reinterpret_cast<cTransmission*>(address));
	}

	Gear GearFromMemory(uintptr_t address)
	{
		return Gear(reinterpret_cast<tTransmissionGear*>(address));
	}

	void initialize(sol::table& module)
	{
		module.new_usertype<Transmission>("transmission",
			"from_memory", sol::factories(&TransmissionFromMemory),
			"get_gear", &Transmission::GetGear,
			"drive_type", sol::property(&Transmission::GetTractionType,
					&Transmission::SetTractionType),
			"engine_type", sol::property(&Transmission::GetEngineType,
					&Transmission::SetEngineType),
			"min_gear_speed", sol::property(&Transmission::GetMinGearVelocity,
					&Transmission::SetMinGearVelocity),
			"calculate_gear", &Transmission::CalculateGearForSimpleCar,
			"calculate_acceleration", &Transmission::CalculateDriveAcceleration);

		module.new_usertype<Gear>("gear",
			"from_memory", sol::factories(&GearFromMemory),
			"max_speed", sol::property(&Gear::GetMaxSpeed, &Gear::SetMaxSpeed),
			"change_up_speed", sol::property(&Gear::GetChangeUpSpeed, &Gear::SetChangeUpSpeed),
			"change_down_speed", sol::property(&Gear::GetChangeDownSpeed,
					&Gear::SetChangeDownSpeed));
	}
}