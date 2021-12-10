#include "bullet.hpp"
#include "game_sa/CPools.h"
#include "game_sa/CPed.h"
#include "game_sa/CBulletInfo.h"
#include "game_sa/eWeaponType.h"
#include "game_sa/CVector.h"
#include "game_sa/CMessages.h"

namespace bullet
{
	struct CallParameters
	{
		CPed *creator;
		eWeaponType weaponType;
		CVector origin;
		CVector velocity;
	};

	struct CallSniperParameters
	{
		CPed *creator;
		int slot;
		CVector origin;
		CVector target;

		std::string ToString()
		{
			std::string str = "slot: " + std::to_string(slot) + " originX: "
				+ std::to_string(origin.x) + " targetX: " + std::to_string(target.x);
			return str;
		}
	};

	CallParameters tableToSimpleCallParameters(sol::table& table)
	{
		int weaponType = table.get<sol::object>("weaponType").as<int>();
		eWeaponType type = static_cast<eWeaponType>(weaponType);

		double originX = table.get<sol::object>("originX").as<double>();
		double originY = table.get<sol::object>("originY").as<double>();
		double originZ = table.get<sol::object>("originZ").as<double>();
		CVector origin = CVector(originX, originY, originZ);

		double velX = table.get<sol::object>("velX").as<double>();
		double velY = table.get<sol::object>("velY").as<double>();
		double velZ = table.get<sol::object>("velZ").as<double>();
		CVector velocity = CVector(velX, velY, velZ);

		return CallParameters{nullptr, type, origin, velocity};
	}

	CallParameters tableToCallParameters(sol::table& table)
	{
		CallParameters parameters = tableToSimpleCallParameters(table);
		int creatorHandle = table.get<sol::object>("creatorHandle").as<int>();
		parameters.creator = CPools::GetPed(creatorHandle);

		return parameters;
	}

	CallSniperParameters tableToSniperCallParameters(sol::table& table)
	{
		int slot = table.get<sol::object>("slot").as<int>();

		double originX = table.get<sol::object>("originX").as<double>();
		double originY = table.get<sol::object>("originY").as<double>();
		double originZ = table.get<sol::object>("originZ").as<double>();
		CVector origin = CVector(originX, originY, originZ);

		double targetX = table.get<sol::object>("targetX").as<double>();
		double targetY = table.get<sol::object>("targetY").as<double>();
		double targetZ = table.get<sol::object>("targetZ").as<double>();
		CVector target = CVector(targetX, targetY, targetZ);

		return CallSniperParameters{nullptr, slot, origin, target};
	}

	int GetMaxBulletInfos()
	{
		return MAX_BULLET_INFOS;
	}

	void addBullet(int creatorHandle, int weaponType, float originX,
		float originY, float originZ, float velX, float velY, float velZ)
	{
		CPed* creator = CPools::GetPed(creatorHandle);
		eWeaponType type = static_cast<eWeaponType>(weaponType);
		CVector origin = CVector(originX, originY, originZ);
		CVector velocity = CVector(velX, velY, velZ);

		if (!creator)
			return;

		CBulletInfo::AddBullet(creator, type, origin, velocity);
	}

	void addBulletNow()
	{
		CPlayerPed *playerPed = FindPlayerPed();
		CVehicle *vehPtr = FindPlayerVehicle(0, false);
		CVector playerSpd = FindPlayerSpeed(0);
		CVector playerVec;

		if (vehPtr)
			playerVec = CVector(playerPed->TransformFromObjectSpace(CVector(0.0, 2.5, 0.0)));
		else
			playerVec = CVector(playerPed->TransformFromObjectSpace(CVector(0.0, 0.1, 0.0)));

		float bulletSpeed = 10.0f + playerSpd.Magnitude();
		CVector targetVec = playerPed->TransformFromObjectSpace(CVector(0.0, bulletSpeed, 0.0));
		CVector speedVec(targetVec.x - playerVec.x, targetVec.y - playerVec.y,
			targetVec.z - playerVec.z);
		CBulletInfo::AddBullet(playerPed, eWeaponType::WEAPON_SNIPERRIFLE, playerVec, speedVec);
	}

	void addBulletByPlayer(sol::table& table)
	{
		CallParameters params = tableToSimpleCallParameters(table);
		CPed* creator = FindPlayerPed();
		
		if (!creator)
			return;
		
		CBulletInfo::AddBullet(creator, params.weaponType, params.origin, params.velocity);
	}

	void addBulletByTable(sol::table& table)
	{
		CallParameters params = tableToCallParameters(table);

		if (!params.creator)
			return;
		
		CBulletInfo::AddBullet(params.creator, params.weaponType, params.origin, params.velocity);
	}

	void initialize(sol::table& module)
	{
		module.set_function("getMaxBulletInfos", &GetMaxBulletInfos);
		module.set_function("addBullet", &addBullet);
		module.set_function("addBulletNow", &addBulletNow);
		module.set_function("addBulletByTable", &addBulletByTable);
		module.set_function("addBulletByPlayer", &addBulletByPlayer);
	}
}