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
#include "Transmission.cpp"

namespace automobile
{
	Automobile::Automobile(CAutomobile* vehicle) : Physical(vehicle)
	{
		m_Vehicle = vehicle;
	}

	uint32_t Automobile::GetHandlingAddress()
	{
		return reinterpret_cast<uintptr_t>(m_Vehicle->m_pHandlingData);
	}

	uint32_t Automobile::GetFlyingHandlingAddress()
	{
		return reinterpret_cast<uintptr_t>(m_Vehicle->m_pFlyingHandlingData);
	}

	uint32_t Automobile::GetHandlingFlags()
	{
		return m_Vehicle->m_nHandlingFlagsIntValue;
	}

	void Automobile::SetHandlingFlags(uint32_t flags)
	{
		m_Vehicle->m_nHandlingFlagsIntValue = static_cast<eVehicleHandlingFlags>(flags);
	}

	float Automobile::GetWheelScale()
	{
		return m_Vehicle->m_fWheelScale;
	}

	void Automobile::SetWheelScale(float scale)
	{
		m_Vehicle->m_fWheelScale = scale;
	}

	float Automobile::GetSteerAngle()
	{
		return m_Vehicle->m_fSteerAngle;
	}

	void Automobile::SetSteerAngle(float angle)
	{
		m_Vehicle->m_fSteerAngle = angle;
	}

	float Automobile::GetGasPedal()
	{
		return m_Vehicle->m_fGasPedal;
	}

	void Automobile::SetGasPedal(float gas)
	{
		m_Vehicle->m_fGasPedal = gas;
	}

	float Automobile::GetBrakePedal()
	{
		return m_Vehicle->m_fBreakPedal;
	}

	void Automobile::SetBrakePedal(float brake)
	{
		m_Vehicle->m_fBreakPedal = brake;
	}

	uint8_t Automobile::GetCreatedBy()
	{
		return m_Vehicle->m_nCreatedBy;
	}

	void Automobile::SetCreatedBy(uint8_t createdBy)
	{
		m_Vehicle->m_nCreatedBy = createdBy;
	}

	uint16_t Automobile::GetRouteSeed()
	{
		return m_Vehicle->m_nForcedRandomRouteSeed;
	}

	void Automobile::SetRouteSeed(uint16_t seed)
	{
		m_Vehicle->m_nForcedRandomRouteSeed = seed;
	}

	float Automobile::GetDirtLevel()
	{
		return m_Vehicle->m_fDirtLevel;
	}

	void Automobile::SetDirtLevel(float level)
	{
		m_Vehicle->m_fDirtLevel = level;
	}

	float Automobile::GetGearChangeCount()
	{
		return m_Vehicle->m_fGearChangeCount;
	}

	void Automobile::SetGearChangeCount(float count)
	{
		m_Vehicle->m_fGearChangeCount = count;
	}

	float Automobile::GetWheelSpinForAudio()
	{
		return m_Vehicle->m_fWheelSpinForAudio;
	}

	void Automobile::SetWheelSpinForAudio(float wheelSpin)
	{
		m_Vehicle->m_fWheelSpinForAudio = wheelSpin;
	}

	void Automobile::BlowUp(uintptr_t damager, uint8_t hideExplosion)
	{
		if(!m_Vehicle)
			return;

		CEntity *entity = reinterpret_cast<CEntity*>(damager);
		m_Vehicle->BlowUpCar(entity, hideExplosion);
	}

	uint32_t Automobile::GetContactWheelsCount()
	{
		return m_Vehicle->GetNumContactWheels();
	}

	float Automobile::GetWheelWidth(bool fromRear)
	{
		return m_Vehicle->FindWheelWidth(fromRear);
	}

	transmission::Transmission Automobile::GetTransmission()
	{
		return transmission::Transmission(&m_Vehicle->m_pHandlingData->m_transmissionData);
	}

	vehicle_audio::VehicleAudio Automobile::GetAudio()
	{
		return vehicle_audio::VehicleAudio(&m_Vehicle->m_vehicleAudio);
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

	bool IsVehiclePointerValid(uintptr_t address)
	{
		return IsVehiclePointerValid(reinterpret_cast<CVehicle*>(address));
	}

	Automobile FromMemory(uintptr_t address)
	{
		return Automobile(reinterpret_cast<CAutomobile*>(address));
	}

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

	void initialize(sol::table& module)
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

		module.new_usertype<Automobile>("vehicle",
			sol::base_classes, sol::bases<Placeable, Entity, Physical>(),
			"from_memory", sol::factories(&FromMemory),
			"get_handling_pointer", &Automobile::GetHandlingAddress,
			"get_flying_handling_pointer", &Automobile::GetFlyingHandlingAddress,
			"handling_flags", sol::property(&Automobile::GetHandlingFlags,
					&Automobile::SetHandlingFlags),
			"wheel_scale", sol::property(&Automobile::GetWheelScale, &Automobile::SetWheelScale),
			"steer_angle", sol::property(&Automobile::GetSteerAngle, &Automobile::SetSteerAngle),
			"gas_pedal", sol::property(&Automobile::GetGasPedal, &Automobile::SetGasPedal),
			"brake_pedal", sol::property(&Automobile::GetBrakePedal, &Automobile::SetBrakePedal),
			"created_by", sol::property(&Automobile::GetCreatedBy, &Automobile::SetCreatedBy),
			"route_seed", sol::property(&Automobile::GetRouteSeed, &Automobile::SetRouteSeed),
			"dirt_level", sol::property(&Automobile::GetDirtLevel, &Automobile::SetDirtLevel),
			"gear_change_count", sol::property(&Automobile::GetGearChangeCount,
					&Automobile::SetGearChangeCount),
			"wheel_spin_audio", sol::property(&Automobile::GetWheelSpinForAudio,
					&Automobile::SetWheelSpinForAudio),
			"blow_up", &Automobile::BlowUp,
			"get_contact_wheels_count", &Automobile::GetContactWheelsCount,
			"get_wheel_width", &Automobile::GetWheelWidth,
			"get_transmission", &Automobile::GetTransmission,
			"get_audio", &Automobile::GetAudio,
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
