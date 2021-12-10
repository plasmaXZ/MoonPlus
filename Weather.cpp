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

#include "Weather.hpp"

namespace weather
{
	float Weather::GetTrafficLightsBrightness()
	{
		return CWeather::TrafficLightsBrightness;
	}

	void Weather::SetTrafficLightsBrightness(float brightness)
	{
		CWeather::TrafficLightsBrightness = brightness;
	}

	uint32_t Weather::GetCurrentRainStrength()
	{
		return CWeather::CurrentRainParticleStrength;
	}

	void Weather::SetCurrentRainStrength(uint32_t strength)
	{
		CWeather::CurrentRainParticleStrength = strength;
	}

	uint32_t Weather::GetLightningDuration()
	{
		return CWeather::LightningDuration;
	}

	void Weather::SetLightningDuration(uint32_t duration)
	{
		CWeather::LightningDuration = duration;
	}

	bool Weather::IsLightningFlashEnabled()
	{
		return CWeather::LightningFlash;
	}

	void Weather::SetLightningFlashEnabled(bool enabled)
	{
		CWeather::LightningFlash = enabled;
	}

	bool Weather::IsLightningBurstEnabled()
	{
		return CWeather::LightningBurst;
	}

	void Weather::SetLightningBurstEnabled(bool enabled)
	{
		CWeather::LightningBurst = enabled;
	}

	float Weather::GetHeadLightsSpectrum()
	{
		return CWeather::HeadLightsSpectrum;
	}

	void Weather::SetHeadLightsSpectrum(float spectrum)
	{
		CWeather::HeadLightsSpectrum = spectrum;
	}

	float Weather::GetWaterFogFXControl()
	{
		return CWeather::WaterFogFXControl;
	}

	void Weather::SetWaterFogFXControl(float fog)
	{
		CWeather::WaterFogFXControl = fog;
	}

	float Weather::GetHeatHazeFXControl()
	{
		return CWeather::HeatHazeFXControl;
	}

	void Weather::SetHeatHazeFXControl(float haze)
	{
		CWeather::HeatHazeFXControl = haze;
	}

	float Weather::GetHeatHaze()
	{
		return CWeather::HeatHaze;
	}

	void Weather::SetHeatHaze(float haze)
	{
		CWeather::HeatHaze = haze;
	}

	float Weather::GetSunGlare()
	{
		return CWeather::SunGlare;
	}

	void Weather::SetSunGlare(float glare)
	{
		CWeather::SunGlare = glare;
	}

	float Weather::GetRainbow()
	{
		return CWeather::Rainbow;
	}

	void Weather::SetRainbow(float rainbow)
	{
		CWeather::Rainbow = rainbow;
	}

	float Weather::GetWavyness()
	{
		return CWeather::Wavyness;
	}

	void Weather::SetWaviness(float waviness)
	{
		CWeather::Wavyness = waviness;
	}

	float Weather::GetWind()
	{
		return CWeather::Wind;
	}

	void Weather::SetWind(float wind)
	{
		CWeather::Wind = wind;
	}

	CVector Weather::GetWindDirection()
	{
		return CWeather::WindDir;
	}

	void Weather::SetWindDirection(CVector& direction)
	{
		CWeather::WindDir = direction;
	}

	float Weather::GetSandstorm()
	{
		return CWeather::Sandstorm;
	}

	void Weather::SetSandstorm(float sandstorm)
	{
		CWeather::Sandstorm = sandstorm;
	}

	float Weather::GetRain()
	{
		return CWeather::Rain;
	}

	void Weather::SetRain(float rain)
	{
		CWeather::Rain = rain;
	}

	float Weather::GetFoggyness()
	{
		return CWeather::Foggyness;
	}

	void Weather::SetFoggyness(float foggyness)
	{
		CWeather::Foggyness = foggyness;
	}

	float Weather::GetCloudCoverage()
	{
		return CWeather::CloudCoverage;
	}

	void Weather::SetCloudCoverage(float coverage)
	{
		CWeather::CloudCoverage = coverage;
	}

	float Weather::GetWetRoads()
	{
		return CWeather::WetRoads;
	}

	void Weather::SetWetRoads(float wet)
	{
		CWeather::WetRoads = wet;
	}

	Weather Get()
	{
		return Weather();
	}

	uint16_t GetForcedWeatherType()
	{
		return CWeather::ForcedWeatherType;
	}

	void SetForcedWeatherType(uint16_t type)
	{
		CWeather::ForcedWeatherType = type;
	}

	uint16_t GetNextWeather()
	{
		return CWeather::NewWeatherType;
	}

	void SetNextWeather(uint16_t type)
	{
		CWeather::NewWeatherType = type;
	}

	uint16_t GetCurrentWeather()
	{
		return CWeather::OldWeatherType;
	}

	void SetCurrentWeather(uint16_t type)
	{
		CWeather::OldWeatherType = type;
	}

	bool ForecastWeather(uint16_t type, uint32_t steps)
	{
		return CWeather::ForecastWeather(type, steps);
	}

	void ReleaseWeather()
	{
		CWeather::ReleaseWeather();
	}

	void initialize(sol::table& module)
	{
		module.set_function("get_forced_weather", &GetForcedWeatherType);
		module.set_function("set_forced_weather", &SetForcedWeatherType);
		module.set_function("get_next_weather", &GetNextWeather);
		module.set_function("set_next_weather", &SetNextWeather);
		module.set_function("get_current_weather", &GetCurrentWeather);
		module.set_function("set_current_weather", &SetCurrentWeather);
		module.set_function("forecast_weather", &ForecastWeather);
		module.set_function("release_weather", &ReleaseWeather);

		module.new_usertype<Weather>("weather",
			"get", sol::factories(&Get),
			"traffic_lights_brightness", sol::property(&Weather::GetTrafficLightsBrightness,
					&Weather::SetTrafficLightsBrightness),
			"current_rain_strength", sol::property(&Weather::GetCurrentRainStrength,
					&Weather::SetCurrentRainStrength),
			"lightning_duration", sol::property(&Weather::GetLightningDuration,
					&Weather::SetLightningDuration),
			"is_lightning_flashing", sol::property(&Weather::IsLightningFlashEnabled,
					&Weather::SetLightningFlashEnabled),
			"is_lightning_burst_enabled", sol::property(&Weather::IsLightningBurstEnabled,
					&Weather::SetLightningBurstEnabled),
			"headlights_spectrum", sol::property(&Weather::GetHeadLightsSpectrum,
					&Weather::SetHeadLightsSpectrum),
			"water_fog_fx", sol::property(&Weather::GetWaterFogFXControl,
					&Weather::SetWaterFogFXControl),
			"heat_haze_fx", sol::property(&Weather::GetHeatHazeFXControl,
					&Weather::SetHeatHazeFXControl),
			"heat_haze_level", sol::property(&Weather::GetHeatHaze, &Weather::SetHeatHaze),
			"sun_glare_level", sol::property(&Weather::GetSunGlare, &Weather::SetSunGlare),
			"rainbow_level", sol::property(&Weather::GetRainbow, &Weather::SetRainbow),
			"waviness_level", sol::property(&Weather::GetWavyness, &Weather::SetWaviness),
			"wind_speed", sol::property(&Weather::GetWind, &Weather::SetWind),
			"wind_direction", sol::property(&Weather::GetWindDirection,
					&Weather::SetWindDirection),
			"sandstorm_level", sol::property(&Weather::GetSandstorm, &Weather::SetSandstorm),
			"rain_level", sol::property(&Weather::GetRain, &Weather::SetRain),
			"fog_level", sol::property(&Weather::GetFoggyness, &Weather::SetFoggyness),
			"cloud_coverage", sol::property(&Weather::GetCloudCoverage,
					&Weather::SetCloudCoverage),
			"road_wet_level", sol::property(&Weather::GetWetRoads, &Weather::SetWetRoads));

		module.new_enum<true>("weather_type",
			"EXTRASUNNY_LA", 0,
			"SUNNY_LA", 1,
			"EXTRASUNNY_SMOG_LA", 2,
			"SUNNY_SMOG_LA", 3,
			"CLOUDY_LA", 4,
			"SUNNY_SF", 5,
			"EXTRASUNNY_SF", 6,
			"CLOUDY_SF", 7,
			"RAINY_SF", 8,
			"FOGGY_SF", 9,
			"SUNNY_VEGAS", 10,
			"EXTRASUNNY_VEGAS", 11,
			"CLOUDY_VEGAS", 12,
			"EXTRASUNNY_COUNTRYSIDE", 13,
			"SUNNY_COUNTRYSIDE", 14,
			"CLOUDY_COUNTRYSIDE", 15,
			"RAINY_COUNTRYSIDE", 16,
			"EXTRASUNNY_DESERT", 17,
			"SUNNY_DESERT", 18,
			"SANDSTORM_DESERT", 19,
			"UNDERWATER", 20,
			"EXTRACOLOURS_1", 21,
			"EXTRACOLOURS_2", 22);
	}
}
