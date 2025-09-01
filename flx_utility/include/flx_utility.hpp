#ifndef FLX_UTILITY_HPP
#define FLX_UTILITY_HPP

#include "flx_types.hpp"
#include "flx_new.hpp"
#include "flx_type_traits.hpp"
#include "flx_concepts.hpp"

#ifndef NDEBUG
#include <cassert>
#else
#define assert(expr) ((void)0)
#endif // !NDEBUG

namespace flx
{
	extern const c8* last_error;
	extern void (*on_terminate) () noexcept;

	void* allocate(const imp::size_type size);

	void* allocate(const imp::size_type size, [[maybe_unused]] imp::nothrow_t) noexcept;

	void deallocate(void* ptr) noexcept;

	void terminate(const c8* const error_msg) noexcept;

	// construct_at is always noexcept
	template <class ty, class... val_ty>
	requires requires(ty* location, val_ty&&... args)
	{
		::new (static_cast<void*>(location), flx::nothrow, flx::use_flx) ty(flx::forward<val_ty>(args)...);
	}
	constexpr ty* construct_at(ty* const location, val_ty&&... args) noexcept
	{
		static_assert(noexcept(ty(flx::forward<val_ty>(args)...)), "flx_utility::construct_at: your constructor should be noexcept.");

		return ::new (static_cast<void*>(location), flx::nothrow, flx::use_flx) ty(flx::forward<val_ty>(args)...);
	}

	// copy_construct_at is always noexcept
	template <flx::copy_constructible ty>
	constexpr ty* copy_construct_at(ty* const location, const ty& other) noexcept
	{
		static_assert(noexcept(ty(other)), "flx_utility::copy_construct_at: your copy constructor should be noexcept.");

		return ::new (static_cast<void*>(location), flx::nothrow, flx::use_flx) ty(other);
	}

	// move_construct_at is always noexcept
	template <flx::move_constructible ty>
	constexpr ty* move_construct_at(ty* const location, ty&& other) noexcept
	{
		static_assert(noexcept(ty(flx::move(other))), "flx_utility::move_construct_at: your move constructor should be noexcept.");

		return ::new (static_cast<void*>(location), flx::nothrow, flx::use_flx) ty(flx::move(other));
	}

	template<typename ty>
	constexpr const ty& (max) (const ty& a, const ty& b) noexcept
	{
		return a > b ? a : b;
	}
	
	template<typename ty>
	constexpr const ty& (min) (const ty& a, const ty& b) noexcept
	{
		return a < b ? a : b;
	}

	// converts x, y, width to index for 2D array
	template<typename ty>
	constexpr const ty (xy_to_idx) (ty x, ty y, ty width) noexcept
	{
		return x + y * width;
	}
} // namespace flx

#endif // !FLX_UTILITY_HPP