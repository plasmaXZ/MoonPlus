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

#include "Entity.hpp"
#include "CEntity.h"

namespace entity
{
	Entity::Entity(CEntity* entity) : Placeable(entity)
	{
		m_Entity = entity;
	}

	uintptr_t Entity::GetRwObjectPointer()
	{
		return reinterpret_cast<uintptr_t>(m_Entity->m_pRwObject);
	}

	uint8_t Entity::GetRwObjectType()
	{
		return RwObjectGetType(m_Entity->m_pRwObject);
	}

	uintptr_t Entity::GetRwAtomicPointer()
	{
		return reinterpret_cast<uintptr_t>(m_Entity->m_pRwAtomic);
	}

	uint8_t Entity::GetType()
	{
		return m_Entity->m_nType;
	}

	void Entity::SetType(uint8_t type)
	{
		m_Entity->m_nType = type;
	}

	uint8_t Entity::GetStatus()
	{
		return m_Entity->m_nStatus;
	}

	void Entity::SetStatus(uint8_t status)
	{
		m_Entity->m_nStatus = status;
	}

	uint16_t Entity::GetRandomSeed()
	{
		return m_Entity->m_nRandomSeed;
	}

	void Entity::SetRandomSeed(uint16_t seed)
	{
		m_Entity->m_nRandomSeed = seed;
	}

	bool Entity::HasPreRenderEffects()
	{
		return m_Entity->HasPreRenderEffects();
	}

	CVector Entity::GetBoundCenter()
	{
		return m_Entity->GetBoundCentre();
	}

	float Entity::GetDistanceFromCenterOfMassToBaseOfModel()
	{
		return m_Entity->GetDistanceFromCentreOfMassToBaseOfModel();
	}

	void Entity::UpdateRwFrame()
	{
		m_Entity->UpdateRwFrame();
	}

	void Entity::SetRwObjectAlpha(uint32_t alpha)
	{
		m_Entity->SetRwObjectAlpha(alpha);
	}

	Entity FromMemory(uintptr_t address)
	{
		return Entity(reinterpret_cast<CEntity*>(address));
	}

	bool IsPointerValid(uintptr_t address)
	{
		CEntity *entity = reinterpret_cast<CEntity*>(address);
		return IsEntityPointerValid(entity);
	}

	void initialize(sol::table& module)
	{
		module.set_function("is_entity_pointer_valid", &IsPointerValid);
		module.new_usertype<Entity>("entity",
			sol::base_classes, sol::bases<Placeable>(),
			"from_memory", sol::factories(&FromMemory),
			"get_rw_object_pointer", &Entity::GetRwObjectPointer,
			"get_rw_object_type", &Entity::GetRwObjectType,
			"get_rw_atomic_pointer", &Entity::GetRwAtomicPointer,
			"type", sol::property(&Entity::GetType, &Entity::SetType),
			"status", sol::property(&Entity::GetStatus, &Entity::SetStatus),
			"random_seed", sol::property(&Entity::GetRandomSeed, &Entity::SetRandomSeed),
			"has_pre_render_effects", &Entity::HasPreRenderEffects,
			"get_bound_center", &Entity::GetBoundCenter,
			"get_com_distance_from_base", &Entity::GetDistanceFromCenterOfMassToBaseOfModel,
			"update_rw_frame", &Entity::UpdateRwFrame,
			"set_rw_object_alpha", &Entity::SetRwObjectAlpha);

		module.new_enum<true>("entity_status",
			"PLAYER", 0,
			"PLAYER_PLAYBACKFROMBUFFER", 1,
			"SIMPLE", 2,
			"PHYSICS", 3,
			"ABANDONED", 4,
			"WRECKED", 5,
			"TRAIN_MOVING", 6,
			"TRAIN_NOT_MOVING", 7,
			"HELI", 8,
			"PLANE", 9,
			"REMOTE_CONTROLLED", 10,
			"PLAYER_DISABLED", 11,
			"TRAILER", 12,
			"SIMPLE_TRAILER", 13);

		module.new_enum<true>("rw_object_type",
			"RP_ATOMIC", 1,
			"RP_CLUMP", 2);
	}
}