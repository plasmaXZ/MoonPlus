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

#include "CPhysical.h"
#include "Entity.hpp"

namespace physical
{
	using Placeable = placeable::Placeable;
	using Entity = entity::Entity;

	class Physical : public Entity
	{
	private:
		CPhysical* m_Physical;
	public:
		Physical(CPhysical* ptr);
		bool IsGravityEnabled();
		void SetGravityEnabled(bool enabled);
		bool IsCollisionEnabled();
		void SetCollisionEnabled(bool enabled);
		CVector GetTurnSpeed();
		void SetTurnSpeed(const CVector& speed);
		CVector GetFrictionMoveSpeed();
		void SetFrictionMoveSpeed(const CVector& friction);
		CVector GetFrictionTurnSpeed();
		CVector GetForceVector();
		void SetForceVector(const CVector& force);
		CVector GetTorqueVector();
		void SetTorqueVector(const CVector& torque);
		float GetMass();
		void SetMass(float mass);
		float GetTurnMass();
		void SetTurnMass(float turnMass);
		float GetVelocityFrequency();
		void SetVelocityFrequency(float vel);
		float GetAirResistance();
		void SetAirResistance(float resistance);
		float GetElasticity();
		void SetElasticity(float elasticity);
		float GetBuoyancy();
		void SetBuoyancy(float buoyancy);
		CVector GetCenterOfMass();
		void SetCenterOfMass(const CVector& com);
		uint8_t GetContactSurface();
		void SetContactSurface(uint8_t surface);
		float GetDamageIntensity();
		void SetDamageIntensity(float intensity);
		void ApplyMoveForce(const CVector& force);
		void ApplyTurnForce(const CVector& direction, const CVector& velocity);
		float GetKineticEnergy();
		void SkipPhysics();
	};

	Physical FromMemory(uintptr_t address);
	void initialize(sol::table& module);
}
