#ifndef FLX_NEW_HPP
#define FLX_NEW_HPP

#ifndef NDEBUG
#include <cassert>
#else
#define assert(expr) ((void)0)
#endif // !NDEBUG

// TODO: fix placment new problem
// It is now used in flx_dynamic_array.hpp

/// Defines placement new to be used in flx libraries
/// The problem is: other headers already define this placement new, so conflicts arise
/// operator new can only be global or class specific
/// Forcing all types to implement placement new is bad
/// MSVC doesn't have weak linking, so we need entierly unique placement new
///                                               This makes this placement new unique    vvvvvvvvvvvv
constexpr inline void* operator new ([[maybe_unused]] unsigned long long size, void* ptr, [[maybe_unused]] bool use_flx) noexcept
{
	return ptr;
}

// To use this placement new we need:
//                  vvvvvv
// new (&new_data[i], true) ty(flx::move(data[i]));

#endif // !FLX_NEW_HPP