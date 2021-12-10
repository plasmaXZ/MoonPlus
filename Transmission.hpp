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

#pragma once

#include "sol.hpp"
#include "cTransmission.h"
#include "tTransmissionGear.h"
#include "Conversion.hpp"

namespace transmission
{
	class Gear
	{
	private:
		tTransmissionGear* m_Gear;
	public:
		Gear(tTransmissionGear* gear);
		float GetMaxSpeed();
		void SetMaxSpeed(float speed);
		float GetChangeUpSpeed();
		void SetChangeUpSpeed(float speed);
		float GetChangeDownSpeed();
		void SetChangeDownSpeed(float speed);
	};

	class Transmission
	{
	private:
		cTransmission* m_Transmission;
	public:
		Transmission(cTransmission* transmission);
		Gear GetGear(uint32_t gear);
		uint8_t GetTractionType();
		void SetTractionType(uint8_t type);
		uint8_t GetEngineType();
		void SetEngineType(uint8_t type);
		float GetMinGearVelocity();
		void SetMinGearVelocity(float min);
		void InitGearRatios();
		uint8_t CalculateGearForSimpleCar(float speed, uint8_t currentGear);
		float CalculateDriveAcceleration(float gas, uint8_t currentGear, float gearChangeCount,
			float speed, float unk1, float unk2, bool allWheelsOnGround, uint8_t handlingCheat);
	};

	Transmission TransmissionFromMemory(uintptr_t address);
	Gear GearFromMemory(uintptr_t address);
	void initialize(sol::table& module);
}
