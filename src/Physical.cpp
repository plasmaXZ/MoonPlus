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

#include "Physical.hpp"
#include "Conversion.hpp"

namespace physical
{
	Physical::Physical(CPhysical* physical) : Entity(physical)
	{
		m_Physical = physical;
	}

	bool Physical::IsGravityEnabled()
	{
		return m_Physical->m_nPhysicalFlags.bApplyGravity == 1;
	}

	void Physical::SetGravityEnabled(bool enabled)
	{
		m_Physical->m_nPhysicalFlags.bApplyGravity = enabled;
	}

	bool Physical::IsCollisionEnabled()
	{
		return m_Physical->m_nPhysicalFlags.bDisableCollisionForce == 0;
	}

	void Physical::SetCollisionEnabled(bool enabled)
	{
		m_Physical->m_nPhysicalFlags.bDisableCollisionForce = !enabled;
	}

	CVector Physical::GetTurnSpeed()
	{
		return m_Physical->m_vecTurnSpeed;
	}

	void Physical::SetTurnSpeed(const CVector& speed)
	{
		m_Physical->m_vecTurnSpeed = speed;
	}

	CVector Physical::GetFrictionMoveSpeed()
	{
		return m_Physical->m_vecFrictionMoveSpeed;
	}

	void Physical::SetFrictionMoveSpeed(const CVector& friction)
	{
		m_Physical->m_vecFrictionMoveSpeed = friction;
	}

	CVector Physical::GetFrictionTurnSpeed()
	{
		return m_Physical->m_vecFrictionTurnSpeed;
	}

	CVector Physical::GetForceVector()
	{
		return m_Physical->m_vecForce;
	}

	void Physical::SetForceVector(const CVector& force)
	{
		m_Physical->m_vecForce = force;
	}

	CVector Physical::GetTorqueVector()
	{
		return m_Physical->m_vecTorque;
	}

	void Physical::SetTorqueVector(const CVector& torque)
	{
		m_Physical->m_vecTorque = torque;
	}

	float Physical::GetMass()
	{
		return m_Physical->m_fMass;
	}

	void Physical::SetMass(float mass)
	{
		m_Physical->m_fMass = mass;
	}

	float Physical::GetTurnMass()
	{
		return m_Physical->m_fTurnMass;
	}

	void Physical::SetTurnMass(float turnMass)
	{
		m_Physical->m_fTurnMass = turnMass;
	}

	float Physical::GetVelocityFrequency()
	{
		return m_Physical->m_fVelocityFrequency;
	}

	void Physical::SetVelocityFrequency(float vel)
	{
		m_Physical->m_fVelocityFrequency = vel;
	}

	float Physical::GetAirResistance()
	{
		return m_Physical->m_fAirResistance;
	}

	void Physical::SetAirResistance(float resistance)
	{
		m_Physical->m_fAirResistance = resistance;
	}

	float Physical::GetElasticity()
	{
		return m_Physical->m_fElasticity;
	}

	void Physical::SetElasticity(float elasticity)
	{
		m_Physical->m_fElasticity = elasticity;
	}

	float Physical::GetBuoyancy()
	{
		return m_Physical->m_fBuoyancyConstant;
	}

	void Physical::SetBuoyancy(float buoyancy)
	{
		m_Physical->m_fBuoyancyConstant = buoyancy;
	}

	CVector Physical::GetCenterOfMass()
	{
		return m_Physical->m_vecCentreOfMass;
	}

	void Physical::SetCenterOfMass(const CVector& com)
	{
		m_Physical->m_vecCentreOfMass = com;
	}

	uint8_t Physical::GetContactSurface()
	{
		return m_Physical->m_nContactSurface;
	}

	void Physical::SetContactSurface(uint8_t surface)
	{
		m_Physical->m_nContactSurface = surface;
	}

	float Physical::GetDamageIntensity()
	{
		return m_Physical->m_fDamageIntensity;
	}

	void Physical::SetDamageIntensity(float intensity)
	{
		m_Physical->m_fDamageIntensity = intensity;
	}

	void Physical::ApplyMoveForce(const CVector& force)
	{
		m_Physical->ApplyMoveForce(force);
	}

	void Physical::ApplyTurnForce(const CVector& direction, const CVector& velocity)
	{
		m_Physical->ApplyTurnForce(direction, velocity);
	}

	float Physical::GetKineticEnergy()
	{
		float speedInMs = GameUnitToMs(m_Physical->m_fMovingSpeed);
		return pow(speedInMs, 2) * m_Physical->m_fMass * 0.5f;
	}

	void Physical::SkipPhysics()
	{
		m_Physical->SkipPhysics();
	}

	Physical FromMemory(uintptr_t address)
	{
		return Physical(reinterpret_cast<CPhysical*>(address));
	}

	void initialize(sol::table& module)
	{
		module.new_usertype<Physical>("physical",
			sol::base_classes, sol::bases<Entity, Placeable>(),
			"from_memory", sol::factories(&FromMemory),
			"is_gravity_enabled", sol::property(&Physical::IsGravityEnabled,
					&Physical::SetGravityEnabled),
			"is_collision_enabled", sol::property(&Physical::IsCollisionEnabled,
					&Physical::SetCollisionEnabled),
			"turn_speed", sol::property(&Physical::GetTurnSpeed, &Physical::SetTurnSpeed),
			"friction", sol::property(&Physical::GetFrictionMoveSpeed, 
					&Physical::SetFrictionMoveSpeed),
			"get_friction_turn_speed", &Physical::GetFrictionTurnSpeed,
			"force_vector", sol::property(&Physical::GetForceVector, &Physical::SetForceVector),
			"torque_vector", sol::property(&Physical::GetTorqueVector, &Physical::SetTorqueVector),
			"mass", sol::property(&Physical::GetMass, &Physical::SetMass),
			"turn_mass", sol::property(&Physical::GetTurnMass, &Physical::SetTurnMass),
			"vel_frequency", sol::property(&Physical::GetVelocityFrequency,
					&Physical::SetVelocityFrequency),
			"air_resistance", sol::property(&Physical::GetAirResistance,
					&Physical::SetAirResistance),
			"elasticity", sol::property(&Physical::GetElasticity, &Physical::SetElasticity),
			"buoyancy", sol::property(&Physical::GetBuoyancy, &Physical::SetBuoyancy),
			"center_of_mass", sol::property(&Physical::GetCenterOfMass,
					&Physical::SetCenterOfMass),
			"contact_surface", sol::property(&Physical::GetContactSurface,
					&Physical::SetContactSurface),
			"damage_intensity", sol::property(&Physical::GetDamageIntensity,
					&Physical::SetDamageIntensity),
			"apply_move_force", &Physical::ApplyMoveForce,
			"apply_turn_force", &Physical::ApplyTurnForce,
			"get_kinetic_energy", &Physical::GetKineticEnergy,
			"skip_physics", &Physical::SkipPhysics);
	}
}
