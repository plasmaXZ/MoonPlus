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

#include "Placeable.hpp"
#include "CVector.h"
#include "CMatrixLink.h"

namespace placeable
{
	Placeable::Placeable(CPlaceable* placeable) : Wrapper(placeable)
	{}

	void Placeable::SetMatrixScale(float scale)
	{
		CMatrixLink *matrix = m_Wrapped->m_matrix;
		if (matrix)
			matrix->SetScale(scale);
	}

	CMatrix Placeable::GetMatrix()
	{
		CMatrix *matrix = m_Wrapped->m_matrix;
		if (matrix)
			return *matrix;

		return CMatrix();
	}

	// https://github.com/codenulls/gta-reversed/blob/d5e83be9f188daf57902d0199f6c5019ba6f3e8d/source/game_sa/Entity/CPlaceable.cpp
	CVector Placeable::GetOrientation()
	{
		CVector forward = this->GetForwardVector();
		float x = asinf(forward.z);

		float cosx = cosf(x);
		float cosy = this->GetTopVector().z;
		float y = acosf(cosy);

		float cosz = forward.y;
		float z = acosf(cosz);

		return CVector(x, y, z);
	}

	CVector Placeable::GetTopVector()
	{
		CMatrixLink *matrix = m_Wrapped->m_matrix;
		if (matrix)
			return matrix->up;

		return CVector(0.0f, 0.0f, 1.0f);
	}

	CVector Placeable::GetForwardVector()
	{
		return CVector(-sin(m_Wrapped->m_placement.m_fHeading),
			cos(m_Wrapped->m_placement.m_fHeading), 0.0f);
	}

	CVector Placeable::GetRightVector()
	{
		CMatrixLink *matrix = m_Wrapped->m_matrix;
		if (matrix)
			return matrix->right;

		return CVector(cos(m_Wrapped->m_placement.m_fHeading),
			sin(m_Wrapped->m_placement.m_fHeading), 0.0f);
	}

	bool Placeable::IsWithinArea(float x1, float y1, float x2, float y2)
	{
		if (!m_Wrapped)
			return false;

		return m_Wrapped->IsWithinArea(x1, y1, x2, y2);
	}

	bool Placeable::IsWithinVolume(float x1, float y1, float z1, float x2, float y2, float z2)
	{
		if (!m_Wrapped)
			return false;

		return m_Wrapped->IsWithinArea(x1, y1, z1, x2, y2, z2);
	}

	Placeable FromMemory(uintptr_t address)
	{
		return Placeable(reinterpret_cast<CPlaceable*>(address));
	}

	void initialize(sol::table& module)
	{
		module.new_usertype<Placeable>("placeable",
			"from_memory", sol::factories(&FromMemory),
			"get_pointer", &Placeable::GetAddress,
			"set_matrix_scale", &Placeable::SetMatrixScale,
			"get_matrix", &Placeable::GetMatrix,
			"get_orientation", &Placeable::GetOrientation,
			"get_top_vector", &Placeable::GetTopVector,
			"get_forward_vector", &Placeable::GetForwardVector,
			"get_right_vector", &Placeable::GetRightVector,
			"is_within_area_2d", &Placeable::IsWithinArea,
			"is_within_area_3d", &Placeable::IsWithinVolume);
	}
}