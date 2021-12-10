// MIT License

// Copyright (c) 2012 DK22Pac
// Copyright (c) 2017 FYP

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
#include "plugin.h"

namespace sol
{
	// CRGBA
	template <>
	struct lua_size<CRGBA> : std::integral_constant<int, 4> {};
	template <>
	struct lua_type_of<CRGBA> : std::integral_constant<sol::type, sol::type::number> {};
	namespace stack
	{
		template <>
		struct checker<CRGBA>
		{
			template <typename Handler>
			static bool check(lua_State* L, int index, Handler&& handler, record& tracking)
			{
				int idx = lua_absindex(L, index);
				bool success = stack::check<byte>(L, idx, handler)
					&& stack::check<byte>(L, idx + 1, handler)
					&& stack::check<byte>(L, idx + 2, handler)
					&& stack::check<byte>(L, idx + 3, handler);
				tracking.use(4);
				return success;
			}
		};

		template <>
		struct getter<CRGBA>
		{
			static CRGBA get(lua_State* L, int index, record& tracking)
			{
				int idx = lua_absindex(L, index);
				byte r = stack::get<byte>(L, idx);
				byte g = stack::get<byte>(L, idx + 1);
				byte b = stack::get<byte>(L, idx + 2);
				byte a = stack::get<byte>(L, idx + 3);
				tracking.use(4);
				return CRGBA{r, g, b, a};
			}
		};

		template <>
		struct pusher<CRGBA>
		{
			static int push(lua_State* L, const CRGBA& color)
			{
				int amount = stack::multi_push(L, color.r, color.g, color.b, color.a);
				return amount;
			}
		};
	}

	// CRect
	template <>
	struct lua_size<CRect> : std::integral_constant<int, 4> {};
	template <>
	struct lua_type_of<CRect> : std::integral_constant<sol::type, sol::type::number> {};
	namespace stack
	{
		template <>
		struct checker<CRect>
		{
			template <typename Handler>
			static bool check(lua_State* L, int index, Handler&& handler, record& tracking)
			{
				int idx = lua_absindex(L, index);
				bool success = stack::check<float>(L, idx, handler)
					&& stack::check<float>(L, idx + 1, handler)
					&& stack::check<float>(L, idx + 2, handler)
					&& stack::check<float>(L, idx + 3, handler);
				tracking.use(4);
				return success;
			}
		};

		template <>
		struct getter<CRect>
		{
			static CRect get(lua_State* L, int index, record& tracking)
			{
				int idx = lua_absindex(L, index);
				float left = stack::get<float>(L, idx);
				float top = stack::get<float>(L, idx + 1);
				float right = stack::get<float>(L, idx + 2);
				float bottom = stack::get<float>(L, idx + 3);
				tracking.use(4);
				return CRect{left, top, right, bottom};
			}
		};

		template <>
		struct pusher<CRect>
		{
			static int push(lua_State* L, const CRect& rect)
			{
				int amount = stack::multi_push(L, rect.left, rect.top, rect.right, rect.bottom);
				return amount;
			}
		};
	}
}