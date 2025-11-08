#ifndef IMP_NEW_HPP_
#define IMP_NEW_HPP_

#include "flx/imp_core.hpp"

/// Defines placement new to be used in flx libraries
/// The problem is: other headers already define this placement new, so conflicts arise
/// operator new can only be global or class specific
/// Forcing all types to implement placement new is bad
/// MSVC doesn't have weak linking, so we need entierly unique placement new
/// Custom tag 'use_flx' is therefore created.

FLX_BEGIN_
IMP_BEGIN_

struct use_flx_tag
{
	explicit use_flx_tag() = default;
};

struct nothrow_tag
{
	explicit nothrow_tag() = default;
};

IMP_END_

FLX_API_ constexpr IMP_ use_flx_tag use_flx;
FLX_API_ constexpr IMP_ nothrow_tag nothrow;

FLX_END_

// ===== placement new ===== //

IMP_DEPRICATE_EXCEPTIONS_ constexpr void* operator new ([[maybe_unused]] FLX_ szt, void* ptr, [[maybe_unused]] IMP_ use_flx_tag)
{
	return ptr;
}
constexpr void* operator new ([[maybe_unused]] FLX_ szt, void* ptr, [[maybe_unused]] IMP_ nothrow_tag, [[maybe_unused]] IMP_ use_flx_tag) noexcept
{
	return ptr;
}

IMP_DEPRICATE_EXCEPTIONS_ constexpr void* operator new[] ([[maybe_unused]] FLX_ szt, void* ptr, [[maybe_unused]] IMP_ use_flx_tag)
{
	return ptr;
}
constexpr void* operator new[] ([[maybe_unused]] FLX_ szt, void* ptr, [[maybe_unused]] IMP_ nothrow_tag, [[maybe_unused]] IMP_ use_flx_tag) noexcept
{
	return ptr;
}



#endif // IMP_NEW_HPP_