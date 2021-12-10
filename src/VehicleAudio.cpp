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

#include "VehicleAudio.hpp"

namespace vehicle_audio
{
	VehicleAudio::VehicleAudio(CAEVehicleAudioEntity* audio) : Wrapper(audio)
	{}

	bool VehicleAudio::IsEnabled()
	{
		return m_Wrapped->m_bEnabled;
	}

	void VehicleAudio::SetEnabled(bool enabled)
	{
		m_Wrapped->m_bEnabled = enabled;
	}

	int8_t VehicleAudio::GetEngineState()
	{
		return m_Wrapped->m_nEngineState;
	}

	void VehicleAudio::SetEngineState(int8_t state)
	{
		m_Wrapped->m_nEngineState = state;
	}

	float VehicleAudio::GetSirenVolume()
	{
		return m_Wrapped->m_fSirenVolume;
	}

	void VehicleAudio::SetSirenVolume(float volume)
	{
		m_Wrapped->m_fSirenVolume = volume;
	}

	float VehicleAudio::GetGeneralVolume()
	{
		return m_Wrapped->m_fGeneralVehicleSoundVolume;
	}

	void VehicleAudio::SetGeneralVolume(float volume)
	{
		m_Wrapped->m_fGeneralVehicleSoundVolume = volume;
	}

	int16_t VehicleAudio::GetDecelerationSoundBankId()
	{
		return m_Wrapped->m_nEngineDecelerateSoundBankId;
	}

	void VehicleAudio::SetDecelerationSoundBankId(int16_t bankId)
	{
		m_Wrapped->m_nEngineDecelerateSoundBankId = bankId;
	}

	int16_t VehicleAudio::GetAccelerationSoundBankId()
	{
		return m_Wrapped->m_nEngineAccelerateSoundBankId;
	}

	void VehicleAudio::SetAccelerationSoundBankId(int16_t bankId)
	{
		m_Wrapped->m_nEngineAccelerateSoundBankId = bankId;
	}

	int16_t VehicleAudio::GetEngineBankId()
	{
		return m_Wrapped->m_nEngineBankSlotId;
	}

	void VehicleAudio::SetEngineBankId(int16_t bankId)
	{
		m_Wrapped->m_nEngineBankSlotId = bankId;
	}

	float VehicleAudio::GetBassEq()
	{
		return m_Wrapped->m_settings.m_fBassEq;
	}

	void VehicleAudio::SetBassEq(float eq)
	{
		m_Wrapped->m_settings.m_fBassEq = eq;
	}

	Sound VehicleAudio::GetInnerSound()
	{
		return Sound(&m_Wrapped->m_tempSound);
	}

	VehicleAudio FromMemory(uintptr_t address)
	{
		return VehicleAudio(reinterpret_cast<CAEVehicleAudioEntity*>(address));
	}

	void initialize(sol::table& module)
	{
		module.new_usertype<VehicleAudio>("vehicle_audio",
			"from_memory", sol::factories(&FromMemory),
			"get_pointer", &VehicleAudio::GetAddress,
			"is_enabled", sol::property(&VehicleAudio::IsEnabled, &VehicleAudio::SetEnabled),
			"engine_state", sol::property(&VehicleAudio::GetEngineState,
					&VehicleAudio::SetEngineState),
			"siren_volume", sol::property(&VehicleAudio::GetSirenVolume,
					&VehicleAudio::SetSirenVolume),
			"general_volume", sol::property(&VehicleAudio::GetGeneralVolume,
					&VehicleAudio::SetGeneralVolume),
			"deceleration_bank_id", sol::property(&VehicleAudio::GetDecelerationSoundBankId,
					&VehicleAudio::SetDecelerationSoundBankId),
			"acceleration_bank_id", sol::property(&VehicleAudio::GetAccelerationSoundBankId,
					&VehicleAudio::SetAccelerationSoundBankId),
			"engine_bank_id", sol::property(&VehicleAudio::GetEngineBankId,
					&VehicleAudio::SetEngineBankId),
			"bass_eq", sol::property(&VehicleAudio::GetBassEq, &VehicleAudio::SetBassEq),
			"get_inner_sound", &VehicleAudio::GetInnerSound);
	}
}
