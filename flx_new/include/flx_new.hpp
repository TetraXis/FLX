#ifndef FLX_NEW_HPP
#define FLX_NEW_HPP

#ifndef NDEBUG
#include <cassert>
#else
#define assert(expr) ((void)0)
#endif // !NDEBUG

// HACK: Added unique placement new to avoid collision with std one
// It is now used in flx_dynamic_array.hpp

/// Defines placement new to be used in flx libraries
/// The problem is: other headers already define this placement new, so conflicts arise
/// operator new can only be global or class specific
/// Forcing all types to implement placement new is bad
/// MSVC doesn't have weak linking, so we need entierly unique placement new
///                                                                This makes this placement new unique    vvvvvvvvvvvv

#if defined(_M_X64) || defined(__x86_64__) // x64
constexpr inline void* operator new ([[maybe_unused]] unsigned long long size, void* ptr, [[maybe_unused]] bool use_flx) noexcept
{
	return ptr;
}
#else // x86
constexpr inline void* operator new ([[maybe_unused]] unsigned int size, void* ptr, [[maybe_unused]] bool use_flx) noexcept
{
	return ptr;
}
#endif

// To use this placement new we need:
//                  vvvvvv
// new (&new_data[i], true) ty(flx::move(data_[i]));

#endif // !FLX_NEW_HPP