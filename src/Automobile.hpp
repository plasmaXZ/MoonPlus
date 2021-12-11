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

#include "Transmission.hpp"
#include "VehicleAudio.hpp"
#include "CAutomobile.h"
#include "Physical.hpp"

namespace automobile
{
	using Placeable = placeable::Placeable;
	using Entity = entity::Entity;
	using Physical = physical::Physical;
	using Transmission = transmission::Transmission;
	using VehicleAudio = vehicle_audio::VehicleAudio;

	class Automobile : public Physical
	{
	private:
		CAutomobile* m_Vehicle;
	public:
		Automobile(CAutomobile* vehicle);
		uintptr_t GetHandlingAddress();
		uintptr_t GetFlyingHandlingAddress();
		uint32_t GetHandlingFlags();
		void SetHandlingFlags(uint32_t flags);
		float GetWheelScale();
		void SetWheelScale(float scale);
		float GetSteerAngle();
		void SetSteerAngle(float angle);
		float GetGasPedal();
		void SetGasPedal(float gas);
		float GetBrakePedal();
		void SetBrakePedal(float brake);
		uint8_t GetCreatedBy();
		void SetCreatedBy(uint8_t createdBy);
		uint16_t GetRouteSeed();
		void SetRouteSeed(uint16_t seed);
		float GetDirtLevel();
		void SetDirtLevel(float level);
		float GetGearChangeCount();
		void SetGearChangeCount(float count);
		float GetWheelSpinForAudio();
		void SetWheelSpinForAudio(float wheelSpin);
		void BlowUp(uintptr_t damager, uint8_t hideExplosion);
		uint32_t GetContactWheelsCount();
		float GetWheelWidth(bool fromRear);
		Transmission GetTransmission();
		VehicleAudio GetAudio();
		float GetWheelSuspensionCompression(uint8_t wheel);
		float GetWheelRotation(uint8_t wheel);
		float GetWheelPosition(uint8_t wheel);
		float GetWheelSpeed(uint8_t wheel);
		int32_t GetWheelState(uint8_t wheel);
		float GetMoveDirection();
		float GetInertiaValue();
		void SetInertiaValue(float inertia);
		float GetTraction();
		void SetTraction(float traction);
		float GetNitroValue();
		void SetNitroValue(float value);
		void TellToGoTo(float x, float y, float z, float altitudeMin, float altitudeMax);
		void PlaceOnRoadProperly();
	};

	bool IsVehiclePointerValid(uintptr_t address);
	Automobile FromMemory(uintptr_t address);
	float GetAirResistanceMult();
	void SetAirResistanceMult(float mult);
	float GetWheelSpinLoss();
	void SetWheelSpinLoss(float loss);
	void SetWheelSpinValues(float targetRate, float inAirTargetRate, float riseRate,
		float fallRate);
	void ResetWheelSpinValues();
	float GetBikeWheelTurnForce();
	void SetBikeWheelTurnForce(float force);
	void initialize(sol::table& module);
}