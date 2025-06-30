#ifndef FLX_VEC_HPP
#define FLX_VEC_HPP

#include "flx_types.hpp"
#include "flx_type_traits.hpp"

#include <math.h> // NOTE: Using standard library in RELEASE

#ifndef NDEBUG
#include <cassert>
#else
#define assert(expr) ((void)0)
#endif // !NDEBUG

namespace flx
{
	template <typename ty>
	struct vec2
	{
	flx_public:
		ty x{};
		ty y{};

	flx_public:
		constexpr vec2() noexcept = default;

		constexpr ~vec2() noexcept
		{
		}

		constexpr vec2(const vec2& other) noexcept
			: x(other.x), y(other.y)
		{
		}

		constexpr vec2(vec2&& other) noexcept
			: x(flx::move(other.x)), y(flx::move(other.y))
		{
		}

		constexpr vec2(const ty& new_x, const ty& new_y) noexcept
			: x(new_x), y(new_y)
		{
		}

		constexpr vec2(ty&& new_x, ty&& new_y) noexcept
			: x(flx::move(new_x)), y(flx::move(new_y))
		{
		}

		constexpr vec2& operator=(const vec2&) noexcept = default;
		constexpr vec2& operator=(vec2&&) noexcept = default;

		constexpr vec2& operator-() noexcept
		{
			x = -x;
			y = -y;
			return *this;
		}

		constexpr vec2 operator+(const vec2& other) noexcept
		{
			return { x + other.x, y + other.y };
		}

		constexpr vec2 operator-(const vec2& other) noexcept
		{
			return { x - other.x, y - other.y };
		}

		constexpr vec2 operator*(const vec2& other) noexcept
		{
			return { x * other.x, y * other.y };
		}

		constexpr vec2 operator/(const vec2& other) noexcept
		{
			return { x / other.x, y / other.y };
		}

		constexpr vec2 operator*(const ty& scalar) noexcept
		{
			return { x * scalar, y * scalar };
		}

		constexpr vec2 operator/(const ty& scalar) noexcept
		{
			return { x / scalar, y / scalar };
		}

		constexpr vec2& operator+=(const vec2& other) noexcept
		{
			x += other.x;
			y += other.y;
			return *this;
		}

		constexpr vec2& operator-=(const vec2& other) noexcept
		{
			x -= other.x;
			y -= other.y;
			return *this;
		}

		constexpr vec2& operator*=(const vec2& other) noexcept
		{
			x *= other.x;
			y *= other.y;
			return *this;
		}

		constexpr vec2& operator/=(const vec2& other) noexcept
		{
			x /= other.x;
			y /= other.y;
			return *this;
		}

		constexpr vec2& operator*=(const ty& scalar) noexcept
		{
			x *= scalar;
			y *= scalar;
			return *this;
		}

		constexpr vec2& operator/=(const ty& scalar) noexcept
		{
			x /= scalar;
			y /= scalar;
			return *this;
		}

		constexpr f64 length() const noexcept
		{
			return sqrt(x * x + y * y);
		}

		constexpr vec2& normalize() noexcept
		{
			assert(lenght != 0.0 && "flx_vec.hpp::vec2::normalize vec length is 0.0.");

			f64 len = length();
			x /= len;
			y /= len;
			return *this;
		}

		constexpr vec2 normalized() const noexcept
		{
			assert(lenght != 0.0 && "flx_vec.hpp::vec2::normalized vec length is 0.0.");

			f64 len = length();
			return { x / len, y / len };
		}
	};
} // namespace flx

#endif // !FLX_VEC_HPP