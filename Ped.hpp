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

#include "Physical.hpp"
#include "CPed.h"

namespace ped
{
	using Placeable = placeable::Placeable;
	using Entity = entity::Entity;
	using Physical = physical::Physical;

	class Ped : public Physical
	{
	private:
		CPed* m_Ped;
	public:
		Ped(CPed* ped);
		bool IsStanding();
		bool IsAimingGun();
		bool IsFiringWeapon();
		bool IsBleeding();
		void SetBleeding(bool bleeding);
		bool IsAllowedToDuck();
		void SetAllowedToDuck(bool allow);
		bool IsCriticalHitEnabled();
		void SetCriticalHitEnabled(bool enabled);
		bool CanSwim();
		void SetCanSwim(bool can);
		bool IsFallenDown();
		void SetFallenDown(bool fallen);
		uint8_t GetCreatedBy();
		void SetCreatedBy(uint8_t createdBy);
		uint32_t GetState();
		void SetState(uint32_t state);
		int32_t GetMoveState();
		void SetMoveState(int32_t state);
		float GetHealth();
		void SetHealth(float health);
		float GetMaxHealth();
		void SetMaxHealth(float health);
		float GetArmor();
		void SetArmor(float armor);
		uintptr_t GetVehicleAddress();
		int32_t GetType();
		void SetType(int32_t type);
		void ClearWeapons();
	};

	bool IsPedPointerValid(uintptr_t address);
	Ped FromMemory(uintptr_t address);
	void initialize(sol::table& module);
}
