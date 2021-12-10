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

#include "Noise.hpp"

namespace noise
{
	SimplexNoise New()
	{
		return SimplexNoise();
	}

	SimplexNoise NewSimpleParams(float frequency, float amplitude)
	{
		return SimplexNoise(frequency, amplitude);
	}

	SimplexNoise NewAllParams(float frequency, float amplitude, float lacunarity,
		float persistence)
	{
		return SimplexNoise(frequency, amplitude, lacunarity, persistence);
	}

	float MakeNoise1D(const SimplexNoise& noise, float x)
	{
		return SimplexNoise::noise(x);
	}

	float MakeNoise2D(const SimplexNoise& noise, float x, float y)
	{
		return SimplexNoise::noise(x, y);
	}

	float MakeNoise3D(const SimplexNoise& noise, float x, float y, float z)
	{
		return SimplexNoise::noise(x, y, z);
	}

	float Fractal1D(const SimplexNoise& noise, float octaves, float x)
	{
		return noise.fractal(octaves, x);
	}

	float Fractal2D(const SimplexNoise& noise, float octaves, float x, float y)
	{
		return noise.fractal(octaves, x, y);
	}

	float Fractal3D(const SimplexNoise& noise, float octaves, float x, float y, float z)
	{
		return noise.fractal(octaves, x, y, z);
	}

	void initialize(sol::table& module)
	{
		module.new_usertype<SimplexNoise>("simplex_noise",
			"new", sol::factories(&New, &NewSimpleParams, &NewAllParams),
			"noise", sol::overload(&MakeNoise1D, &MakeNoise2D, &MakeNoise3D),
			"fractal", sol::overload(&Fractal1D, &Fractal2D, &Fractal3D));
	}
}
