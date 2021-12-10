#include "Weapon.hpp"
#include "CPed.h"
#include "Patch.h"

namespace weapon
{
	Weapon::Weapon(CWeapon* weapon) : Wrapper(weapon)
	{}

	uint32_t Weapon::GetType()
	{
		return m_Wrapped->m_nType;
	}

	void Weapon::SetType(uint32_t type)
	{
		m_Wrapped->m_nType = static_cast<eWeaponType>(type);
	}

	uint32_t Weapon::GetState()
	{
		return m_Wrapped->m_nState;
	}

	void Weapon::SetState(uint32_t state)
	{
		m_Wrapped->m_nState = static_cast<eWeaponState>(state);
	}

	uint32_t Weapon::GetAmmoInClip()
	{
		return m_Wrapped->m_nAmmoInClip;
	}

	void Weapon::SetAmmoInClip(uint32_t ammo)
	{
		m_Wrapped->m_nAmmoInClip = ammo;
	}

	uint32_t Weapon::GetTotalAmmo()
	{
		return m_Wrapped->m_nTotalAmmo;
	}

	void Weapon::SetTotalAmmo(uint32_t ammo)
	{
		m_Wrapped->m_nTotalAmmo = ammo;
	}

	uint32_t Weapon::GetTimeToNextShot()
	{
		return m_Wrapped->m_nTimeForNextShot;
	}

	void Weapon::SetTimeToNextShot(uint32_t time)
	{
		m_Wrapped->m_nTimeForNextShot = time;
	}

	bool Weapon::IsTwoHanded()
	{
		return m_Wrapped->IsType2Handed();
	}

	bool Weapon::FireSniper(uintptr_t creator, uintptr_t victim, CVector& target)
	{
		CPed* creatorPtr = reinterpret_cast<CPed*>(creator);
		CPed* victimPtr = reinterpret_cast<CPed*>(victim);

		return m_Wrapped->FireSniper(creatorPtr, victimPtr, &target);
	}

	void Weapon::Reload(uintptr_t owner)
	{
		CPed* ownerPtr = reinterpret_cast<CPed*>(owner);
		m_Wrapped->Reload(ownerPtr);
	}

	bool Weapon::FireAreaEffect(uintptr_t firingEntity, CVector& origin, uintptr_t targetEntity,
		CVector& target)
	{
		CEntity* firing = reinterpret_cast<CEntity*>(firingEntity);
		CEntity* targetEntityPtr = reinterpret_cast<CEntity*>(targetEntity);

		return m_Wrapped->FireAreaEffect(firing, &origin, targetEntityPtr, &target);
	}

	bool Weapon::FireInstantHitFromCar(uintptr_t vehicle, bool leftSide, bool rightSide)
	{
		CVehicle* veh = reinterpret_cast<CVehicle*>(vehicle);
		if (!IsVehiclePointerValid(veh))
			return false;

		return m_Wrapped->FireInstantHitFromCar(veh, leftSide, rightSide);
	}

	Weapon FromMemory(uintptr_t address)
	{
		return Weapon(reinterpret_cast<CWeapon*>(address));
	}

	Weapon FromPed(uintptr_t address, uint32_t slot)
	{
		CPed* ped = reinterpret_cast<CPed*>(address);
		CWeapon* weapon = &ped->m_aWeapons[slot];

		return Weapon(weapon);
	}

	float GetExtinguisherAimAngle()
	{
		return CWeapon::ms_fExtinguisherAimAngle;
	}

	void SetExtinguisherAimAngle(float angle)
	{
		CWeapon::ms_fExtinguisherAimAngle = angle;
	}

	void GenerateDamageEvent(uintptr_t victim, uintptr_t creator, uint32_t weaponType,
		int32_t damageFactor, uint32_t pedPiece, int32_t direction)
	{
		CPed* victimPtr = reinterpret_cast<CPed*>(victim);
		CEntity* creatorPtr = reinterpret_cast<CPed*>(creator);
		eWeaponType type = static_cast<eWeaponType>(weaponType);
		ePedPieceTypes piece = static_cast<ePedPieceTypes>(pedPiece);

		CWeapon::GenerateDamageEvent(victimPtr, creatorPtr, type, damageFactor, piece, direction);
	}

	float GetPlayerAimScale()
	{
		return fPlayerAimScale;
	}

	void SetPlayerAimScale(float scale)
	{
		fPlayerAimScale = scale;
	}

	float GetShotgunSpread()
	{
		return SHOTGUN_SPREAD_RATE;
	}

	void SetShotgunSpread(float spread)
	{
		SHOTGUN_SPREAD_RATE = spread;
	}

	uint32_t GetShotgunPelletsCount()
	{
		return SHOTGUN_NUM_PELLETS;
	}

	void SetShotgunPelletsCount(uint32_t count)
	{
		SHOTGUN_NUM_PELLETS = count;
	}

	uint32_t GetSpasPelletsCount()
	{
		return SPAS_NUM_PELLETS;
	}

	void SetSpasPelletsCount(uint32_t count)
	{
		SPAS_NUM_PELLETS = count;
	}

	float GetPelletCollisionScale()
	{
		return PELLET_COL_SCALE_RATIO_MULT;
	}

	void SetPelletCollisionScale(float scale)
	{
		PELLET_COL_SCALE_RATIO_MULT = scale;
	}

	void initialize(sol::table& module)
	{
		//plugin::patch::RedirectCall(0x7360D0, Update, true);
		module.set_function("get_extinguisher_aim_angle", &GetExtinguisherAimAngle);
		module.set_function("set_extinguisher_aim_angle", &SetExtinguisherAimAngle);
		module.set_function("create_damage_event", &GenerateDamageEvent);
		module.set_function("get_player_aim_scale", &GetPlayerAimScale);
		module.set_function("set_player_aim_scale", &SetPlayerAimScale);
		module.set_function("get_shotgun_spread", &GetShotgunSpread);
		module.set_function("set_shotgun_spread", &SetShotgunSpread);
		module.set_function("get_shotgun_pellets_count", &GetShotgunPelletsCount);
		module.set_function("set_shotgun_pellets_count", &SetShotgunPelletsCount);
		module.set_function("get_spas_pellets_count", &GetSpasPelletsCount);
		module.set_function("set_spas_pellets_count", &SetSpasPelletsCount);
		module.set_function("get_pellets_collision_scale", &GetPelletCollisionScale);
		module.set_function("set_pellets_collision_scale", &SetPelletCollisionScale);

		module.new_usertype<Weapon>("weapon",
			"from_memory", sol::factories(&FromMemory),
			"from_ped", sol::factories(&FromPed),
			"get_pointer", &Weapon::GetAddress,
			"type", sol::property(&Weapon::GetType, &Weapon::SetType),
			"state", sol::property(&Weapon::GetState, &Weapon::SetState),
			"clip_ammo", sol::property(&Weapon::GetAmmoInClip, &Weapon::SetAmmoInClip),
			"ammo", sol::property(&Weapon::GetTotalAmmo, &Weapon::SetTotalAmmo),
			"time_to_next_shot", sol::property(&Weapon::GetTimeToNextShot,
					&Weapon::SetTimeToNextShot),
			"is_two_handed", &Weapon::IsTwoHanded,
			"fire_sniper", &Weapon::FireSniper,
			"reload", &Weapon::Reload,
			"fire_area_effect", &Weapon::FireAreaEffect,
			"fire_instant_hit_from_car", &Weapon::FireInstantHitFromCar);

		module.new_enum<true>("weapon_slot",
			"HAND", 0,
			"MELEE", 1,
			"HANDGUN", 2,
			"SHOTGUN", 3,
			"SUB_MACHINE_GUN", 4,
			"ASSAULT_RIFLE", 5,
			"RIFLE", 6,
			"HEAVY_WEAPON", 7,
			"PROJECTILE", 8,
			"SPECIAL1", 9,
			"GIFT", 10,
			"SPECIAL2", 11,
			"SATCHEL", 12);

		module.new_enum<true>("weapon_state",
			"READY", 0,
			"FIRING", 1,
			"RELOADING", 2,
			"OUT_OF_AMMO", 3,
			"MELEE_MADE_CONTACT", 4);

		module.new_enum<true>("weapon_type",
			"UNARMED", 0x0,
			"BRASSKNUCKLE", 0x1,
			"GOLFCLUB", 0x2,
			"NIGHTSTICK", 0x3,
			"KNIFE", 0x4,
			"BASEBALLBAT", 0x5,
			"SHOVEL", 0x6,
			"POOLCUE", 0x7,
			"KATANA", 0x8,
			"CHAINSAW", 0x9,
			"DILDO1", 0xA,
			"DILDO2", 0xB,
			"VIBE1", 0xC,
			"VIBE2", 0xD,
			"FLOWERS", 0xE,
			"CANE", 0xF,
			"GRENADE", 0x10,
			"TEARGAS", 0x11,
			"MOLOTOV", 0x12,
			"ROCKET", 0x13,
			"ROCKET_HS", 0x14,
			"FREEFALL_BOMB", 0x15,
			"PISTOL", 0x16,
			"PISTOL_SILENCED", 0x17,
			"DESERT_EAGLE", 0x18,
			"SHOTGUN", 0x19,
			"SAWNOFF", 0x1A,
			"SPAS12", 0x1B,
			"MICRO_UZI", 0x1C,
			"MP5", 0x1D,
			"AK47", 0x1E,
			"M4", 0x1F,
			"TEC9", 0x20,
			"COUNTRYRIFLE", 0x21,
			"SNIPERRIFLE", 0x22,
			"RLAUNCHER", 0x23,
			"RLAUNCHER_HS", 0x24,
			"FTHROWER", 0x25,
			"MINIGUN", 0x26,
			"SATCHEL_CHARGE", 0x27,
			"DETONATOR", 0x28,
			"SPRAYCAN", 0x29,
			"EXTINGUISHER", 0x2A,
			"CAMERA", 0x2B,
			"NIGHTVISION", 0x2C,
			"INFRARED", 0x2D,
			"PARACHUTE", 0x2E,
			"UNUSED", 0x2F,
			"ARMOUR", 0x30,
			"FLARE", 0x3A);
	}
}
