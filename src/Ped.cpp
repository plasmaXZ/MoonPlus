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

#include "Ped.hpp"

namespace ped
{
	Ped::Ped(CPed* ped) : Physical(ped)
	{
		m_Ped = ped;
	}

	bool Ped::IsStanding()
	{
		return m_Ped->m_nPedFlags.bIsStanding;
	}

	bool Ped::IsAimingGun()
	{
		return m_Ped->m_nPedFlags.bIsAimingGun;
	}

	bool Ped::IsFiringWeapon()
	{
		return m_Ped->m_nPedFlags.bFiringWeapon;
	}

	bool Ped::IsBleeding()
	{
		return m_Ped->m_nPedFlags.bPedIsBleeding;
	}

	void Ped::SetBleeding(bool bleeding)
	{
		m_Ped->m_nPedFlags.bPedIsBleeding = bleeding;
	}

	bool Ped::IsAllowedToDuck()
	{
		return !m_Ped->m_nPedFlags.bNotAllowedToDuck;
	}

	void Ped::SetAllowedToDuck(bool allow)
	{
		m_Ped->m_nPedFlags.bNotAllowedToDuck = !allow;
	}

	bool Ped::IsCriticalHitEnabled()
	{
		return !m_Ped->m_nPedFlags.bNoCriticalHits;
	}

	void Ped::SetCriticalHitEnabled(bool enabled)
	{
		m_Ped->m_nPedFlags.bNoCriticalHits = !enabled;
	}

	bool Ped::CanSwim()
	{
		return !m_Ped->m_nPedFlags.bDrownsInWater;
	}

	void Ped::SetCanSwim(bool can)
	{
		m_Ped->m_nPedFlags.bDrownsInWater = !can;
	}

	bool Ped::IsFallenDown()
	{
		return m_Ped->m_nPedFlags.bFallenDown;
	}

	void Ped::SetFallenDown(bool fallen)
	{
		m_Ped->m_nPedFlags.bFallenDown = fallen;
	}

	uint8_t Ped::GetCreatedBy()
	{
		return m_Ped->m_nCreatedBy;
	}

	void Ped::SetCreatedBy(uint8_t createdBy)
	{
		m_Ped->m_nCreatedBy = createdBy;
	}

	uint32_t Ped::GetState()
	{
		return m_Ped->m_nPedState;
	}

	void Ped::SetState(uint32_t state)
	{
		m_Ped->SetPedState(static_cast<ePedState>(state));
	}

	int32_t Ped::GetMoveState()
	{
		return m_Ped->m_nMoveState;
	}

	void Ped::SetMoveState(int32_t state)
	{
		m_Ped->SetMoveState(static_cast<eMoveState>(state));
	}

	float Ped::GetHealth()
	{
		return m_Ped->m_fHealth;
	}

	void Ped::SetHealth(float health)
	{
		m_Ped->m_fHealth = health;
	}

	float Ped::GetMaxHealth()
	{
		return m_Ped->m_fMaxHealth;
	}

	void Ped::SetMaxHealth(float health)
	{
		m_Ped->m_fMaxHealth = health;
	}

	float Ped::GetArmor()
	{
		return m_Ped->m_fArmour;
	}

	void Ped::SetArmor(float armor)
	{
		m_Ped->m_fArmour = armor;
	}

	uintptr_t Ped::GetVehicleAddress()
	{
		return reinterpret_cast<uintptr_t>(m_Ped->m_pVehicle);
	}

	int32_t Ped::GetType()
	{
		return m_Ped->m_nPedType;
	}

	void Ped::SetType(int32_t type)
	{
		m_Ped->m_nPedType = type;
	}

	void Ped::ClearWeapons()
	{
		m_Ped->ClearWeapons();
	}

	bool IsPedPointerValid(uintptr_t address)
	{
		return IsPedPointerValid(reinterpret_cast<CPed*>(address));
	}

	Ped FromMemory(uintptr_t address)
	{
		return Ped(reinterpret_cast<CPed*>(address));
	}

	void initialize(sol::table& module)
	{
		module.set_function("is_ped_pointer_valid", &IsPedPointerValid);

		module.new_usertype<Ped>("ped",
			sol::base_classes, sol::bases<Placeable, Entity, Physical>(),
			"from_memory", sol::factories(&FromMemory),
			"is_standing", &Ped::IsStanding,
			"is_aiming", &Ped::IsAimingGun,
			"is_firing", &Ped::IsFiringWeapon,
			"is_bleeding", sol::property(&Ped::IsBleeding, &Ped::SetBleeding),
			"can_duck", sol::property(&Ped::IsAllowedToDuck, &Ped::SetAllowedToDuck),
			"is_critical_hit_enabled", sol::property(&Ped::IsCriticalHitEnabled,
					&Ped::SetCriticalHitEnabled),
			"can_swim", sol::property(&Ped::CanSwim, &Ped::SetCanSwim),
			"is_fallen_down", sol::property(&Ped::IsFallenDown, &Ped::SetFallenDown),
			"created_by", sol::property(&Ped::GetCreatedBy, &Ped::SetCreatedBy),
			"state", sol::property(&Ped::GetState, &Ped::SetState),
			"move_state", sol::property(&Ped::GetMoveState, &Ped::SetMoveState),
			"health", sol::property(&Ped::GetHealth, &Ped::SetHealth),
			"max_health", sol::property(&Ped::GetMaxHealth, &Ped::SetMaxHealth),
			"armor", sol::property(&Ped::GetArmor, &Ped::SetArmor),
			"type", sol::property(&Ped::GetType, &Ped::SetType),
			"get_vehicle_pointer", &Ped::GetVehicleAddress,
			"clear_weapons", &Ped::ClearWeapons);

		module.new_enum<true>("ped_state",
			"NONE", 0,
			"IDLE", 1,
			"LOOK_ENTITY", 2,
			"LOOK_HEADING", 3,
			"WANDER_RANGE", 4,
			"WANDER_PATH", 5,
			"SEEK_POSITION", 6,
			"SEEK_ENTITY", 7,
			"FLEE_POSITION", 8,
			"FLEE_ENTITY", 9,
			"PURSUE", 10,
			"FOLLOW_PATH", 11,
			"SNIPER_MODE", 12,
			"ROCKETLAUNCHER_MODE", 13,
			"DUMMY", 14,
			"PAUSE", 15,
			"ATTACK", 16,
			"FIGHT", 17,
			"FACE_PHONE", 18,
			"MAKE_PHONECALL", 19,
			"CHAT", 20,
			"MUG", 21,
			"AIMGUN", 22,
			"AI_CONTROL", 23,
			"SEEK_CAR", 24,
			"SEEK_BOAT_POSITION", 25,
			"FOLLOW_ROUTE", 26,
			"CPR", 27,
			"SOLICIT", 28,
			"BUY_ICE_CREAM", 29,
			"INVESTIGATE_EVENT", 30,
			"EVADE_STEP", 31,
			"ON_FIRE", 32,
			"SUNBATHE", 33,
			"FLASH", 34,
			"JOG", 35,
			"ANSWER_MOBILE", 36,
			"HANG_OUT", 37,
			"STATES_NO_AI", 38,
			"ABSEIL_FROM_HELI", 39,
			"SIT", 40,
			"JUMP", 41,
			"FALL", 42,
			"GETUP", 43,
			"STAGGER", 44,
			"EVADE_DIVE", 45,
			"STATES_CAN_SHOOT", 46,
			"ENTER_TRAIN", 47,
			"EXIT_TRAIN", 48,
			"ARREST_PLAYER", 49,
			"DRIVING", 50,
			"PASSENGER", 51,
			"TAXI_PASSENGER", 52,
			"OPEN_DOOR", 53,
			"DIE", 54,
			"DEAD", 55,
			"DIE_BY_STEALTH", 56,
			"CARJACK", 57,
			"DRAGGED_FROM_CAR", 58,
			"ENTER_CAR", 59,
			"STEAL_CAR", 60,
			"EXIT_CAR", 61,
			"HANDS_UP", 62,
			"ARRESTED", 63,
			"DEPLOY_STINGER", 64);

		module.new_enum<true>("ped_move_state",
			"NONE", 0,
			"STILL", 1,
			"TURN_L", 2,
			"TURN_R", 3,
			"WALK", 4,
			"JOG", 5,
			"RUN", 6,
			"SPRINT", 7);
	}
}