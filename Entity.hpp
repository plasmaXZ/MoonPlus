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

#include "CVector.h"
#include "Placeable.hpp"

namespace entity
{
	using Placeable = placeable::Placeable;

	class Entity : public Placeable
	{
	private:
		CEntity* m_Entity;
	public:
		Entity(CEntity* entity);
		uintptr_t GetRwObjectPointer();
		uint8_t GetRwObjectType();
		uintptr_t GetRwAtomicPointer();
		uint8_t GetType();
		void SetType(uint8_t type);
		uint8_t GetStatus();
		void SetStatus(uint8_t status);
		uint16_t GetRandomSeed();
		void SetRandomSeed(uint16_t seed);
		bool HasPreRenderEffects();
		CVector GetBoundCenter();
		float GetDistanceFromCenterOfMassToBaseOfModel();
		void UpdateRwFrame();
		void SetRwObjectAlpha(uint32_t alpha);
	};

	Entity FromMemory(uintptr_t address);
	bool IsPointerValid(uintptr_t address);
	void initialize(sol::table& module);
}