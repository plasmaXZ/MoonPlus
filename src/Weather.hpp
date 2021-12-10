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

#include "sol.hpp"
#include "CWeather.h"

namespace weather
{
	// Since the CWeather class only has static attributes, this struct is only used as an
	// organization tool.
	struct Weather
	{
		float GetTrafficLightsBrightness();
		void SetTrafficLightsBrightness(float brightness);
		uint32_t GetCurrentRainStrength();
		void SetCurrentRainStrength(uint32_t strength);
		uint32_t GetLightningDuration();
		void SetLightningDuration(uint32_t duration);
		bool IsLightningFlashEnabled();
		void SetLightningFlashEnabled(bool enabled);
		bool IsLightningBurstEnabled();
		void SetLightningBurstEnabled(bool enabled);
		float GetHeadLightsSpectrum();
		void SetHeadLightsSpectrum(float spectrum);
		float GetWaterFogFXControl();
		void SetWaterFogFXControl(float fog);
		float GetHeatHazeFXControl();
		void SetHeatHazeFXControl(float haze);
		float GetHeatHaze();
		void SetHeatHaze(float haze);
		float GetSunGlare();
		void SetSunGlare(float glare);
		float GetRainbow();
		void SetRainbow(float rainbow);
		float GetWavyness();
		void SetWaviness(float wavyness);
		float GetWind();
		void SetWind(float wind);
		CVector GetWindDirection();
		void SetWindDirection(CVector& direction);
		float GetSandstorm();
		void SetSandstorm(float sandstorm);
		float GetRain();
		void SetRain(float rain);
		float GetFoggyness();
		void SetFoggyness(float foggyness);
		float GetCloudCoverage();
		void SetCloudCoverage(float coverage);
		float GetWetRoads();
		void SetWetRoads(float wet);
	};

	Weather Get();
	uint16_t GetForcedWeatherType();
	void SetForcedWeatherType(uint16_t type);
	uint16_t GetNextWeather();
	void SetNextWeather(uint16_t type);
	uint16_t GetCurrentWeather();
	void SetCurrentWeather(uint16_t type);
	bool ForecastWeather(uint16_t type, uint32_t steps);
	void ReleaseWeather();
	void initialize(sol::table& module);
}