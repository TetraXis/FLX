#ifndef FLX_INC_NEW_HPP
#define FLX_INC_NEW_HPP

// This header defines custom placement news for FLX.
// The problem is: other headers already define this placement new, so conflicts arise
// operator new can only be global or class specific
// Forcing all types to implement placement new is bad
// MSVC doesn't have weak linking, so we need entirely unique placement new
// Custom tag 'use_flx' is therefore used.
// Since operator new can only be global, there is no point of making this a module.

#include "flx/core.hpp"

constexpr void* operator new ([[maybe_unused]] ::flx::szt, void* ptr, [[maybe_unused]] ::flx::imp::tag_use_flx) noexcept
{
	return ptr;
}

constexpr void* operator new[]([[maybe_unused]] ::flx::szt, void* ptr, [[maybe_unused]] ::flx::imp::tag_use_flx) noexcept
{
	return ptr;
}

#endif // !FLX_INC_CORE_NEW_HPP
