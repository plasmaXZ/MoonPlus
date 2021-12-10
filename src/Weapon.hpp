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
#include "plugin.h"
#include "Wrapper.hpp"
#include "CWeapon.h"

namespace weapon
{
	class Weapon : public Wrapper<CWeapon>
	{
	public:
		Weapon(CWeapon* weapon);
		uint32_t GetType();
		void SetType(uint32_t type);
		uint32_t GetState();
		void SetState(uint32_t state);
		uint32_t GetAmmoInClip();
		void SetAmmoInClip(uint32_t ammo);
		uint32_t GetTotalAmmo();
		void SetTotalAmmo(uint32_t ammo);
		uint32_t GetTimeToNextShot();
		void SetTimeToNextShot(uint32_t time);
		bool IsTwoHanded();
		bool FireSniper(uintptr_t creator, uintptr_t victim, CVector& target);
		void Reload(uintptr_t owner);
		bool FireAreaEffect(uintptr_t firingEntity, CVector& origin, uintptr_t targetEntity,
			CVector& target);
		bool FireInstantHitFromCar(uintptr_t vehicle, bool leftSide, bool rightSide);
	};

	Weapon FromMemory(uintptr_t address);
	Weapon FromPed(uintptr_t address, uint32_t slot);
	float GetExtinguisherAimAngle();
	void SetExtinguisherAimAngle(float angle);
	void GenerateDamageEvent(uintptr_t victim, uintptr_t creator, uint32_t weaponType,
		int32_t damageFactor, uint32_t pedPiece, int32_t direction);
	float GetPlayerAimScale();
	void SetPlayerAimScale(float scale);
	float GetShotgunSpread();
	void SetShotgunSpread(float spread);
	uint32_t GetShotgunPelletsCount();
	void SetShotgunPelletsCount(uint32_t count);
	uint32_t GetSpasPelletsCount();
	void SetSpasPelletsCount(uint32_t count);
	float GetPelletCollisionScale();
	void SetPelletCollisionScale(float scale);
	void initialize(sol::table& module);
}