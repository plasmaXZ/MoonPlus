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

#include "Sound.hpp"

namespace sound
{
	Sound::Sound(CAESound* sound) : Wrapper(sound)
	{}

	float Sound::GetMaxVolume()
	{
		return m_Wrapped->m_fMaxVolume;
	}

	void Sound::SetMaxVolume(float volume)
	{
		m_Wrapped->m_fMaxVolume = volume;
	}

	float Sound::GetSpeed()
	{
		return m_Wrapped->m_fSpeed;
	}

	void Sound::SetSpeed(float speed)
	{
		m_Wrapped->m_fSpeed = speed;
	}

	float Sound::GetTimeScale()
	{
		return m_Wrapped->m_fTimeScale;
	}

	void Sound::SetTimeScale(float scale)
	{
		m_Wrapped->m_fTimeScale = scale;
	}

	float Sound::GetFrequency()
	{
		return m_Wrapped->m_fFrequency;
	}

	void Sound::SetFrequency(float frequency)
	{
		m_Wrapped->m_fFrequency = frequency;
	}

	int16_t Sound::GetCurrentPlayPosition()
	{
		return m_Wrapped->m_nCurrentPlayPosition;
	}

	void Sound::SetCurrentPlayPosition(int16_t position)
	{
		m_Wrapped->m_nCurrentPlayPosition = position;
	}

	int16_t Sound::GetLength()
	{
		return m_Wrapped->m_nSoundLength;
	}

	void Sound::SetLength(int16_t length)
	{
		m_Wrapped->m_nSoundLength = length;
	}

	void Sound::StopSound()
	{
		m_Wrapped->StopSound();
	}

	void Sound::CalculateFrequency()
	{
		m_Wrapped->CalculateFrequency();
	}

	void Sound::UpdateFrequency()
	{
		m_Wrapped->UpdateFrequency();
	}

	Sound FromMemory(uintptr_t address)
	{
		return Sound(reinterpret_cast<CAESound*>(address));
	}

	void initialize(sol::table& module)
	{
		module.new_usertype<Sound>("sound",
			"from_memory", sol::factories(&FromMemory),
			"get_pointer", &Sound::GetAddress,
			"max_volume", sol::property(&Sound::GetMaxVolume, &Sound::SetMaxVolume),
			"speed", sol::property(&Sound::GetSpeed, &Sound::SetSpeed),
			"time_scale", sol::property(&Sound::GetTimeScale, &Sound::SetTimeScale),
			"frequency", sol::property(&Sound::GetFrequency, &Sound::SetFrequency),
			"current_play_pos", sol::property(&Sound::GetCurrentPlayPosition,
					&Sound::SetCurrentPlayPosition),
			"length", sol::property(&Sound::GetLength, &Sound::SetLength),
			"stop", &Sound::StopSound,
			"calculate_frequency", &Sound::CalculateFrequency,
			"update_frequency", &Sound::UpdateFrequency);
	}
}
