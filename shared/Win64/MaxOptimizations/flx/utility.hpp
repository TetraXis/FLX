#ifndef FLX_IMP_UTILITY_HPP_
#define FLX_IMP_UTILITY_HPP_

#include "flx/imp_core.hpp"
#include "flx/new.hpp"
#include "flx/type_traits.hpp"
#include "flx/concepts.hpp"

FLX_BEGIN_

FLX_API_ extern const c8* last_error;
FLX_API_ extern void (*on_terminate) () noexcept;

FLX_API_ inline void* allocate(const szt size) {}; // todo: fix {} and link, now inline temporary

FLX_API_ inline void* allocate(const szt size, [[maybe_unused]] IMP_ nothrow_tag) noexcept {};

FLX_API_ inline void deallocate(void* ptr) noexcept {};

FLX_API_ inline void terminate() noexcept {};
FLX_API_ inline void terminate(const c8* const error_msg) noexcept {};

// construct_at is always noexcept
FLX_API_ template <class ty, class... val_ty>
	requires requires(ty* location, val_ty&&... args)
{
	::new (static_cast<void*>(location), FLX_ nothrow, FLX_ use_flx) ty(FLX_ forward<val_ty>(args)...);
}
constexpr ty* construct_at(ty* const location, val_ty&&... args) noexcept
{
	static_assert(noexcept(ty(FLX_ forward<val_ty>(args)...)), "flx_utility::construct_at: your constructor should be noexcept.");

	return ::new (static_cast<void*>(location), FLX_ nothrow, FLX_ use_flx) ty(FLX_ forward<val_ty>(args)...);
}

// copy_construct_at is always noexcept
FLX_API_ template <FLX_ copy_constructible ty>
constexpr ty* copy_construct_at(ty* const location, const ty& other) noexcept
{
	static_assert(noexcept(ty(other)), "flx_utility::copy_construct_at: your copy constructor should be noexcept.");

	return ::new (static_cast<void*>(location), FLX_ nothrow, FLX_ use_flx) ty(other);
}

// move_construct_at is always noexcept
FLX_API_ template <FLX_ move_constructible ty>
constexpr ty* move_construct_at(ty* const location, ty&& other) noexcept
{
	static_assert(noexcept(ty(FLX_ move(other))), "flx_utility::move_construct_at: your move constructor should be noexcept.");

	return ::new (static_cast<void*>(location), FLX_ nothrow, FLX_ use_flx) ty(FLX_ move(other));
}

FLX_API_ template<typename ty>
constexpr const ty& (max)(const ty& a, const ty& b) noexcept
{
	return a > b ? a : b;
}

FLX_API_ template<typename ty>
constexpr const ty& (min)(const ty& a, const ty& b) noexcept
{
	return a < b ? a : b;
}

// converts x, y, width to index for 2D array
FLX_API_ template<typename ty>
constexpr const ty(xy_to_idx) (ty x, ty y, ty width) noexcept
{
	return x + y * width;
}

FLX_END_

#endif // FLX_IMP_UTILITY_HPP_