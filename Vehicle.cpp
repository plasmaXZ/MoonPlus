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

#include "Vehicle.hpp"
#include "Transmission.cpp"

namespace vehicle
{
	float GetAirResistanceMult()
	{
		return CVehicle::m_fAirResistanceMult;
	}

	void SetAirResistanceMult(float mult)
	{
		CVehicle::m_fAirResistanceMult = mult;
	}

	void SetWheelSpinLoss(float loss)
	{
		WS_ALREADY_SPINNING_LOSS = loss;
	}

	float GetWheelSpinLoss()
	{
		return WS_ALREADY_SPINNING_LOSS;
	}

	Vehicle::Vehicle(CVehicle *ptr) : Physical(ptr)
	{
		this->m_Vehicle = ptr;
	}

	uint32_t Vehicle::GetHandlingAddress()
	{
		return reinterpret_cast<uintptr_t>(m_Vehicle->m_pHandlingData);
	}

	uint32_t Vehicle::GetFlyingHandlingAddress()
	{
		return reinterpret_cast<uintptr_t>(m_Vehicle->m_pFlyingHandlingData);
	}

	uint32_t Vehicle::GetHandlingFlags()
	{
		return m_Vehicle->m_nHandlingFlagsIntValue;
	}

	void Vehicle::SetHandlingFlags(uint32_t flags)
	{
		m_Vehicle->m_nHandlingFlagsIntValue = static_cast<eVehicleHandlingFlags>(flags);
	}

	float Vehicle::GetWheelScale()
	{
		return m_Vehicle->m_fWheelScale;
	}

	void Vehicle::SetWheelScale(float scale)
	{
		m_Vehicle->m_fWheelScale = scale;
	}

	float Vehicle::GetSteerAngle()
	{
		return m_Vehicle->m_fSteerAngle;
	}

	void Vehicle::SetSteerAngle(float angle)
	{
		m_Vehicle->m_fSteerAngle = angle;
	}

	float Vehicle::GetGasPedal()
	{
		return m_Vehicle->m_fGasPedal;
	}

	void Vehicle::SetGasPedal(float gas)
	{
		m_Vehicle->m_fGasPedal = gas;
	}

	float Vehicle::GetBrakePedal()
	{
		return m_Vehicle->m_fBreakPedal;
	}

	void Vehicle::SetBrakePedal(float brake)
	{
		m_Vehicle->m_fBreakPedal = brake;
	}

	uint8_t Vehicle::GetCreatedBy()
	{
		return m_Vehicle->m_nCreatedBy;
	}

	void Vehicle::SetCreatedBy(uint8_t createdBy)
	{
		m_Vehicle->m_nCreatedBy = createdBy;
	}

	uint16_t Vehicle::GetRouteSeed()
	{
		return m_Vehicle->m_nForcedRandomRouteSeed;
	}

	void Vehicle::SetRouteSeed(uint16_t seed)
	{
		m_Vehicle->m_nForcedRandomRouteSeed = seed;
	}

	float Vehicle::GetDirtLevel()
	{
		return m_Vehicle->m_fDirtLevel;
	}

	void Vehicle::SetDirtLevel(float level)
	{
		m_Vehicle->m_fDirtLevel = level;
	}

	float Vehicle::GetGearChangeCount()
	{
		return m_Vehicle->m_fGearChangeCount;
	}

	void Vehicle::SetGearChangeCount(float count)
	{
		m_Vehicle->m_fGearChangeCount = count;
	}

	float Vehicle::GetWheelSpinForAudio()
	{
		return m_Vehicle->m_fWheelSpinForAudio;
	}

	void Vehicle::SetWheelSpinForAudio(float wheelSpin)
	{
		m_Vehicle->m_fWheelSpinForAudio = wheelSpin;
	}

	void Vehicle::BlowUp(uintptr_t damager, uint8_t hideExplosion)
	{
		if (!m_Vehicle)
			return;

		CEntity *entity = reinterpret_cast<CEntity*>(damager);
		m_Vehicle->BlowUpCar(entity, hideExplosion);
	}

	uint32_t Vehicle::GetContactWheelsCount()
	{
		return m_Vehicle->GetNumContactWheels();
	}

	float Vehicle::GetWheelWidth(bool fromRear)
	{
		return m_Vehicle->FindWheelWidth(fromRear);
	}

	transmission::Transmission Vehicle::GetTransmission()
	{
		return transmission::Transmission(&m_Vehicle->m_pHandlingData->m_transmissionData);
	}

	vehicle_audio::VehicleAudio Vehicle::GetAudio()
	{
		return vehicle_audio::VehicleAudio(&m_Vehicle->m_vehicleAudio);
	}

	Vehicle FromMemory(uintptr_t address)
	{
		return Vehicle(reinterpret_cast<CVehicle*>(address));
	}

	bool IsVehiclePointerValid(uintptr_t address)
	{
		return IsVehiclePointerValid(reinterpret_cast<CVehicle*>(address));
	}

	void SetWheelSpinValues(float targetRate, float inAirTargetRate, float riseRate,
		float fallRate)
	{
		CVehicle::WHEELSPIN_TARGET_RATE = targetRate;
		CVehicle::WHEELSPIN_INAIR_TARGET_RATE = inAirTargetRate;
		CVehicle::WHEELSPIN_RISE_RATE = riseRate;
		CVehicle::WHEELSPIN_FALL_RATE = fallRate;
	}

	void ResetWheelSpinValues()
	{
		CVehicle::WHEELSPIN_TARGET_RATE = 1.0f;
		CVehicle::WHEELSPIN_INAIR_TARGET_RATE = 10.0f;
		CVehicle::WHEELSPIN_RISE_RATE = 0.95f;
		CVehicle::WHEELSPIN_FALL_RATE = 0.7f;
	}

	float GetBikeWheelTurnForce()
	{
		return fTweakBikeWheelTurnForce;
	}

	void SetBikeWheelTurnForce(float force)
	{
		fTweakBikeWheelTurnForce = force;
	}
	
	void initialize(sol::table & module)
	{
		module.set_function("is_vehicle_pointer_valid", &IsVehiclePointerValid);
		module.set_function("set_wheel_spin_values", &SetWheelSpinValues);
		module.set_function("reset_wheel_spin_values", &ResetWheelSpinValues);
		module.set_function("get_wheel_spin_loss", &GetWheelSpinLoss);
		module.set_function("set_wheel_spin_loss", &SetWheelSpinLoss);
		module.set_function("get_air_resistance", &GetAirResistanceMult);
		module.set_function("set_air_resistance", &SetAirResistanceMult);
		module.set_function("get_bike_wheel_turn_force", &GetBikeWheelTurnForce);
		module.set_function("set_bike_wheel_turn_force", &SetBikeWheelTurnForce);

		module.new_usertype<Vehicle>("vehicle",
			sol::base_classes, sol::bases<Placeable, Entity, Physical>(),
			"from_memory", sol::factories(&FromMemory),
			"get_handling_pointer", &Vehicle::GetHandlingAddress,
			"get_flying_handling_pointer", &Vehicle::GetFlyingHandlingAddress,
			"handling_flags", sol::property(&Vehicle::GetHandlingFlags,
					&Vehicle::SetHandlingFlags),
			"wheel_scale", sol::property(&Vehicle::GetWheelScale, &Vehicle::SetWheelScale),
			"steer_angle", sol::property(&Vehicle::GetSteerAngle, &Vehicle::SetSteerAngle),
			"gas_pedal", sol::property(&Vehicle::GetGasPedal, &Vehicle::SetGasPedal),
			"brake_pedal", sol::property(&Vehicle::GetBrakePedal, &Vehicle::SetBrakePedal),
			"created_by", sol::property(&Vehicle::GetCreatedBy, &Vehicle::SetCreatedBy),
			"route_seed", sol::property(&Vehicle::GetRouteSeed, &Vehicle::SetRouteSeed),
			"dirt_level", sol::property(&Vehicle::GetDirtLevel, &Vehicle::SetDirtLevel),
			"gear_change_count", sol::property(&Vehicle::GetGearChangeCount,
					&Vehicle::SetGearChangeCount),
			"wheel_spin_audio", sol::property(&Vehicle::GetWheelSpinForAudio,
					&Vehicle::SetWheelSpinForAudio),
			"blow_up", &Vehicle::BlowUp,
			"get_contact_wheels_count", &Vehicle::GetContactWheelsCount,
			"get_wheel_width", &Vehicle::GetWheelWidth,
			"get_transmission", &Vehicle::GetTransmission,
			"get_audio", &Vehicle::GetAudio);

		module.new_enum<true>("vehicle_created_by",
			"RANDOM_VEHICLE", 1,
			"MISSION_VEHICLE", 2,
			"PARKED_VEHICLE", 3,
			"PERMANENT_VEHICLE", 4);

		module.new_enum<true>("wheel_enum",
			"FRONT_LEFT", 0,
			"REAR_LEFT", 1,
			"FRONT_RIGHT", 2,
			"REAR_RIGHT", 3);

		module.new_enum<true>("wheel_state",
			"NORMAL", 0,
			"SPINNING", 1,
			"SKIDDING", 2,
			"FIXED", 3);
	}
}