#ifndef FLX_NEW_HPP
#define FLX_NEW_HPP

#ifndef NDEBUG
#include <cassert>
#else
#define assert(expr) ((void)0)
#endif // !NDEBUG

/// Defines placement new to be used in flx libraries
/// The problem is: other headers already define this placement new, so conflicts arise
/// operator new can only be global or class specific
/// Forcing all types to implement placement new is bad
/// MSVC doesn't have weak linking, so we need entierly unique placement new
/// Custom tag 'use_flx' is therefore created.

namespace flx
{
	namespace imp
	{

#if defined(_M_X64) || defined(__x86_64__) // x64
		using size_type = unsigned long long;
#else // x86
		using size_type = unsigned int;
#endif

		struct use_flx_t
		{
			explicit use_flx_t() = default;
		};

		struct nothrow_t
		{
			explicit nothrow_t() = default;
		};
	} // namespace imp

	constexpr imp::use_flx_t use_flx;
	constexpr imp::nothrow_t nothrow;
} // namespace flx

// ===== placement news ===== //

constexpr inline void* operator new ([[maybe_unused]] flx::imp::size_type, void* ptr, [[maybe_unused]] flx::imp::use_flx_t)
{
	return ptr;
}
constexpr inline void* operator new ([[maybe_unused]] flx::imp::size_type, void* ptr, [[maybe_unused]] flx::imp::nothrow_t nothrow, [[maybe_unused]] flx::imp::use_flx_t) noexcept
{
	return ptr;
}

constexpr inline void* operator new[] ([[maybe_unused]] flx::imp::size_type, void* ptr, [[maybe_unused]] flx::imp::use_flx_t)
{
	return ptr;
}
constexpr inline void* operator new[] ([[maybe_unused]] flx::imp::size_type, void* ptr, [[maybe_unused]] flx::imp::nothrow_t nothrow, [[maybe_unused]] flx::imp::use_flx_t) noexcept
{
	return ptr;
}

#endif // !FLX_NEW_HPP