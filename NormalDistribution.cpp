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

#include "NormalDistribution.hpp"

namespace distribution
{
	NormalDistribution::NormalDistribution(float mean, float deviation)
	{
		m_Mean = mean;
		m_StandardDeviation = deviation;
		m_Seed = std::chrono::system_clock::now().time_since_epoch().count();
		m_Random = std::default_random_engine(m_Seed);
		m_Distribution = std::normal_distribution<float>(mean, deviation);
	}

	float NormalDistribution::Get()
	{
		return m_Distribution(m_Random);
	}

	uint32_t NormalDistribution::GetSeed()
	{
		return m_Seed;
	}

	NormalDistribution New(float mean, float deviation)
	{
		return NormalDistribution(mean, deviation);
	}

	void initialize(sol::table& module)
	{
		module.new_usertype<NormalDistribution>("gaussian",
			"new", sol::factories(&New),
			"get", &NormalDistribution::Get,
			"get_seed", &NormalDistribution::GetSeed);
	}

}