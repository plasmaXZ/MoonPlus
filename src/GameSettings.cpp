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

#include "GameSettings.hpp"

namespace game_settings
{
	GameSettings::GameSettings(CMenuManager* menu) : Wrapper(menu)
	{}

	bool GameSettings::IsHudEnabled()
	{
		return m_Wrapped->m_bHudOn;
	}

	void GameSettings::SetHudEnabled(bool enabled)
	{
		m_Wrapped->m_bHudOn = enabled;
	}

	bool GameSettings::IsWidescreenEnabled()
	{
		return m_Wrapped->m_bWidescreenOn;
	}

	void GameSettings::SetWidescreenEnabled(bool enabled)
	{
		m_Wrapped->m_bWidescreenOn = enabled;
	}

	int32_t GameSettings::GetBrightness()
	{
		return m_Wrapped->m_nBrightness;
	}

	void GameSettings::SetBrightness(uint32_t brightness)
	{
		m_Wrapped->m_nBrightness = brightness;
	}

	float GameSettings::GetDrawDistance()
	{
		return m_Wrapped->m_fDrawDistance;
	}

	void GameSettings::SetDrawDistance(float distance)
	{
		m_Wrapped->m_fDrawDistance = distance;
	}

	void GameSettings::SaveSettings()
	{
		m_Wrapped->SaveSettings();
	}

	GameSettings Get()
	{
		return GameSettings(&FrontEndMenuManager);
	}

	void initialize(sol::table & module)
	{
		module.new_usertype<GameSettings>("game_settings",
			"get", sol::factories(&Get),
			"is_hub_enabled", sol::property(&GameSettings::IsHudEnabled,
					&GameSettings::SetHudEnabled),
			"is_widescreen_enabled", sol::property(&GameSettings::IsWidescreenEnabled,
					&GameSettings::SetWidescreenEnabled),
			"brightness", sol::property(&GameSettings::GetBrightness,
					&GameSettings::SetBrightness),
			"draw_distance", sol::property(&GameSettings::GetDrawDistance,
					&GameSettings::SetDrawDistance),
			"save_settings", &GameSettings::SaveSettings);
	}
}
