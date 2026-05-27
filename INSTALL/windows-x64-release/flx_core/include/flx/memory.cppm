module;

#include "flx/core.hpp"
//#include "flx/type_traits.hpp"
//#include "flx/concepts.hpp"

export module flx.memory;

import flx.assert;
import flx.terminate;

/*export namespace flx
{

	// ===== allocate/deallocate ====== //

	template<typename ty>
	constexpr ty* allocate() noexcept
	{
		static_assert(noexcept(ty{}), "flx/memory.hpp::allocate: your default constructor should be noexcept.");

		try
		{
			return new ty{};
		}
		catch (...)
		{
			::flx::terminate("flx/memory.hpp::allocate: bad alloc.");
			return nullptr;
		}
	}

	template <typename ty, typename... val_ty>
	constexpr ty* allocate(val_ty&&... args) noexcept
	{
		static_assert(noexcept(ty(::flx::forward<val_ty>(args)...)), "flx/memory.hpp::allocate: your constructor should be noexcept.");

		try
		{
			return new ty{ ::flx::forward<val_ty>(args)... };
		}
		catch (...)
		{
			::flx::terminate("flx/memory.hpp::allocate: bad alloc.");
			return nullptr;
		}
	}

	template<typename ty>
	constexpr void deallocate(ty* const ptr) noexcept
	{
		static_assert(::flx::destructible<ty>, "flx/memory.hpp::deallocate: your destructor should be noexcept.");

		delete ptr;
	}

	template<typename ty>
	constexpr ty* allocate_array(const szt size) noexcept
	{
		static_assert(noexcept(ty{}), "flx/memory.hpp::allocate_array: your default constructor should be noexcept.");

		try
		{
			return new ty[size];
		}
		catch (...)
		{
			::flx::terminate("flx/memory.hpp::allocate_array: bad alloc.");
			return nullptr;
		}
	}


	template<typename ty>
	constexpr void deallocate_array(ty* const ptr) noexcept
	{
		static_assert(::flx::destructible<ty>, "flx/memory.hpp::deallocate_array: your destructor should be noexcept.");

		delete[] ptr;
	}

	constexpr void* allocate_raw(const szt bytes) noexcept
	{
		try
		{
			return ::operator new(bytes);
		}
		catch (...)
		{
			::flx::terminate("flx/memory.hpp::allocate_raw: bad alloc.");
			return nullptr;
		}
	}

	constexpr void deallocate_raw(void* const memory) noexcept
	{
		::operator delete(memory);
	}

	template <typename ty, typename... val_ty>
		requires requires(ty* location, val_ty&&... args)
	{
		::new (static_cast<void*>(location), ::flx::use_flx) ty(::flx::forward<val_ty>(args)...);
	}
	constexpr ty* construct_at(ty* const location, val_ty&&... args) noexcept
	{
		static_assert(noexcept(ty(::flx::forward<val_ty>(args)...)), "flx/memory.hpp::construct_at: your constructor should be noexcept.");

		return ::new (static_cast<void*>(location), ::flx::use_flx) ty(::flx::forward<val_ty>(args)...);
	}

	template <::flx::copy_constructible ty>
	constexpr ty* copy_construct_at(ty* const location, const ty& other) noexcept
	{
		static_assert(noexcept(ty(other)), "flx/memory.hpp::copy_construct_at: your copy constructor should be noexcept.");

		return ::new (static_cast<void*>(location) ::flx::use_flx) ty(other);
	}

	template <::flx::move_constructible ty>
	constexpr ty* move_construct_at(ty* const location, ty&& other) noexcept
	{
		static_assert(noexcept(ty(::flx::move(other))), "flx/memory.hpp::move_construct_at: your move constructor should be noexcept.");

		return ::new (static_cast<void*>(location), ::flx::use_flx) ty(::flx::move(other));
	}



	// ===== unique_ptr ===== //

	template<::flx::can_form_pointer ty>
		struct unique_ptr
	{
		using value_type = ty;

	flx_private:
		ty* owned_ptr = nullptr;

	flx_public:
		constexpr unique_ptr() noexcept = default;

		explicit constexpr unique_ptr(ty* ptr) noexcept
			: owned_ptr(ptr)
		{
		}

		constexpr ~unique_ptr() noexcept
		{
			delete owned_ptr;
		}

		constexpr unique_ptr(const unique_ptr&) = delete;

		constexpr unique_ptr(unique_ptr&& other) noexcept
			: owned_ptr(other.release())
		{
		}

		constexpr unique_ptr& operator=(const unique_ptr&) = delete;

		constexpr unique_ptr& operator=(unique_ptr&& other) noexcept
		{
			::flx::assert(this != &other && "flx/memory.hpp::unique_ptr::operator= assigning to self is forbidden.");

			reset(other.release());
			return *this;
		}


		explicit constexpr operator bool() const noexcept
		{
			return owned_ptr != nullptr;
		}

		constexpr bool operator==(const unique_ptr& other) const noexcept
		{
			return owned_ptr == other.owned_ptr;
		}

		constexpr bool operator==(decltype(nullptr)) const noexcept
		{
			return owned_ptr == nullptr;
		}

		constexpr bool operator!=(const unique_ptr& other) const noexcept
		{
			return owned_ptr != other.owned_ptr;
		}

		constexpr bool operator!=(decltype(nullptr)) const noexcept
		{
			return owned_ptr != nullptr;
		}

		constexpr ty* get() const noexcept
		{
			return owned_ptr;
		}

		constexpr ty& operator*() const noexcept
		{
			::flx::assert(owned_ptr != nullptr && "flx/memory.hpp::unique_ptr::operator* dereferencing a nullptr.");

			return *owned_ptr;
		}

		constexpr ty* operator->() const noexcept
		{
			::flx::assert(owned_ptr != nullptr && "flx/memory.hpp::unique_ptr::operator-> dereferencing a nullptr.");

			return owned_ptr;
		}

		[[nodiscard("flx/memory.hpp::unique_ptr is a simple wrapper around heap allocated memory. Calling flx/memory.hpp::unique_ptr::release and discarding will cause memory leaks.")]]
		constexpr ty* release() noexcept
		{
			ty* ptr = owned_ptr;
			owned_ptr = nullptr;
			return ptr;
		}

		constexpr void reset(ty* ptr = nullptr) noexcept
		{
			::flx::assert(ptr != owned_ptr && "flx/memory.hpp::unique_ptr::reset resetting with self is forbidden.");

			delete owned_ptr;
			owned_ptr = ptr;
		}

		constexpr void swap(unique_ptr& other) noexcept
		{
			ty* temp_ptr = owned_ptr;
			owned_ptr = other.owned_ptr;
			other.owned_ptr = temp_ptr;
		}
	}; // unique_ptr<ty>

	template<::flx::can_form_pointer ty>
		struct unique_ptr<ty[]>
	{
		using value_type = ty;

	flx_private:
		ty* owned_ptr = nullptr;

	flx_public:
		constexpr unique_ptr() noexcept = default;

		explicit constexpr unique_ptr(ty* ptr) noexcept
			: owned_ptr(ptr)
		{
		}

		constexpr ~unique_ptr() noexcept
		{
			delete[] owned_ptr;
		}

		constexpr unique_ptr(const unique_ptr&) = delete;

		constexpr unique_ptr(unique_ptr&& other) noexcept
			: owned_ptr(other.release())
		{
		}

		constexpr unique_ptr& operator=(const unique_ptr&) = delete;

		constexpr unique_ptr& operator=(unique_ptr&& other) noexcept
		{
			::flx::assert(this != &other && "flx/memory.hpp::unique_ptr::operator= assigning to self is forbidden.");

			reset(other.release());
			return *this;
		}

		explicit constexpr operator bool() const noexcept
		{
			return owned_ptr != nullptr;
		}

		constexpr bool operator==(const unique_ptr& other) const noexcept
		{
			return owned_ptr == other.owned_ptr;
		}

		constexpr bool operator==(decltype(nullptr)) const noexcept
		{
			return owned_ptr == nullptr;
		}

		constexpr bool operator!=(const unique_ptr& other) const noexcept
		{
			return owned_ptr != other.owned_ptr;
		}

		constexpr bool operator!=(decltype(nullptr)) const noexcept
		{
			return owned_ptr != nullptr;
		}

		constexpr ty* get() const noexcept
		{
			return owned_ptr;
		}

		constexpr ty& operator[](u64 idx) const noexcept
		{
			return owned_ptr[idx];
		}

		[[nodiscard("flx/memory.hpp::unique_ptr is a simple wrapper around heap allocated memory. Calling flx/memory.hpp::unique_ptr::release and discarding will cause memory leaks.")]]
		constexpr ty* release() noexcept
		{
			ty* ptr = owned_ptr;
			owned_ptr = nullptr;
			return ptr;
		}

		constexpr void reset(ty* ptr = nullptr) noexcept
		{
			::flx::assert(ptr != owned_ptr && "flx/memory.hpp::unique_ptr::reset resetting with self is forbidden.");

			delete[] owned_ptr;
			owned_ptr = ptr;
		}

		constexpr void swap(unique_ptr& other) noexcept
		{
			ty* temp_ptr = owned_ptr;
			owned_ptr = other.owned_ptr;
			other.owned_ptr = temp_ptr;
		}
	}; // unique_ptr<ty[]>

	template<typename ty, typename... args_ty>
		[[nodiscard("Discarding created flx::unique_ptr will result in memory leak.")]]
	inline constexpr ::flx::unique_ptr<ty> make_unique(args_ty&&... args)
	{
		return ::flx::unique_ptr<ty>(new ty(::flx::forward<args_ty>(args)...));
	}



	// ===== default_raw_allocator ===== //

	template<::flx::allocatable ty>
		struct default_raw_allocator
	{
		//TODO: finish allocator
		using value_type = ty;

		[[nodiscard("Discarding allocated memory will result in memory leak.")]]
		constexpr ty* allocate(const szt n) noexcept
		{
			//FLX_TRACE_CONTEXT_ADD("flx/memory.hpp::default_raw_allocator::allocate");

			// if (::flx::is_constant_evaluated())
			// {
			//     static_assert(::flx::is_constant_evaluated() && ::flx::is_default_constructible<ty>, "C++20 does not allow raw memory allocation in constexpr, your type should have default constructor.");
			//
			//     return new ty[n]{};
			// }
			// else
			// {
			//     return static_cast<ty*>(::flx::allocate_raw(n * sizeof(ty), flx::nothrow));
			// }
			return static_cast<ty*>(::flx::allocate_raw(n * sizeof(ty), ::flx::nothrow));
		}

		constexpr void deallocate(ty* addr, [[maybe_unused]] const szt n = 0) noexcept
		{
			//FLX_TRACE_CONTEXT_ADD("flx/memory.hpp::default_raw_allocator::deallocate");

			// if (::flx::is_constant_evaluated())
			// {
			//     delete[] addr;
			// }
			// else
			// {
			//     ::flx::deallocate_raw(addr);
			// }

			::flx::deallocate_raw(addr);
		}
	};
} // export namespace flx
*/