#ifndef IMP_MEMORY_HPP_
#define IMP_MEMORY_HPP_

#include "flx/imp_core.hpp"
#include "flx/new.hpp"
#include "flx/type_traits.hpp"
#include "flx/concepts.hpp"

FLX_BEGIN_

// ===== allocate/deallocate ====== //

FLX_API_ template<typename ty>
IMP_DEPRICATE_EXCEPTIONS_
ty* allocate()
{
	return new ty{};
}

FLX_API_ template<typename ty>
ty* allocate([[maybe_unused]] IMP_ nothrow_tag) noexcept
{
	static_assert(noexcept(ty{}), "flx/memory.hpp::allocate: your default constructor should be noexcept.");

	try
	{
		return new ty{};
	}
	catch (...)
	{
		FLX_ terminate("flx/memory.hpp::allocate: bad alloc.");
        return nullptr;
	}
}

FLX_API_ template <typename ty, typename... val_ty>
IMP_DEPRICATE_EXCEPTIONS_
ty* allocate(val_ty&&... args)
{
	return new ty{ FLX_ forward<val_ty>(args)... };
}

FLX_API_ template <typename ty, typename... val_ty>
ty* allocate([[maybe_unused]] IMP_ nothrow_tag, val_ty&&... args) noexcept
{
	static_assert(noexcept(ty(FLX_ forward<val_ty>(args)...)), "flx/memory.hpp::allocate: your constructor should be noexcept.");

	try
	{
		return new ty{ FLX_ forward<val_ty>(args)... };
	}
	catch (...)
	{
		FLX_ terminate("flx/memory.hpp::allocate: bad alloc.");
        return nullptr;
	}
}

FLX_API_ template<typename ty>
void deallocate(ty* const ptr) noexcept
{
    static_assert(FLX_ destructible<ty>, "flx/memory.hpp::deallocate: your destructor should be noexcept.");

	delete ptr;
}

FLX_API_ template<typename ty>
IMP_DEPRICATE_EXCEPTIONS_
ty* allocate_array(const szt size)
{
	return new ty[size];
}

FLX_API_ template<typename ty>
ty* allocate_array(const szt size, [[maybe_unused]] IMP_ nothrow_tag) noexcept
{
	static_assert(noexcept(ty{}), "flx/memory.hpp::allocate_array: your default constructor should be noexcept.");

	try
	{
		return new ty[size];
	}
	catch (...)
	{
		FLX_ terminate("flx/memory.hpp::allocate_array: bad alloc.");
        return nullptr;
	}
}


FLX_API_ template<typename ty>
void deallocate_array(ty* const ptr) noexcept
{
    static_assert(FLX_ destructible<ty>, "flx/memory.hpp::deallocate_array: your destructor should be noexcept.");

	delete[] ptr;
}

FLX_API_ 
IMP_DEPRICATE_EXCEPTIONS_
inline void* allocate_raw(const szt bytes)
{
	return ::operator new(bytes);
}

FLX_API_ inline void* allocate_raw(const szt bytes, [[maybe_unused]] IMP_ nothrow_tag) noexcept
{
	try
	{
		return ::operator new(bytes);
	}
	catch (...)
	{
		FLX_ terminate("flx/memory.hpp::allocate_raw: bad alloc.");
        return nullptr;
	}
}

FLX_API_ inline void deallocate_raw(void* const memory) noexcept
{
	::operator delete(memory);
	return;
}


FLX_API_ template <typename ty, typename... val_ty>
	requires requires(ty* location, val_ty&&... args)
{
	::new (static_cast<void*>(location), FLX_ use_flx) ty(FLX_ forward<val_ty>(args)...);
}
IMP_DEPRICATE_EXCEPTIONS_
constexpr ty* construct_at(ty* const location, val_ty&&... args)
{
	return ::new (static_cast<void*>(location), FLX_ use_flx) ty(FLX_ forward<val_ty>(args)...);
}

FLX_API_ template <typename ty, typename... val_ty>
	requires requires(ty* location, val_ty&&... args)
{
	::new (static_cast<void*>(location), FLX_ nothrow, FLX_ use_flx) ty(FLX_ forward<val_ty>(args)...);
}
constexpr ty* construct_at(ty* const location, [[maybe_unused]] IMP_ nothrow_tag, val_ty&&... args) noexcept
{
	static_assert(noexcept(ty(FLX_ forward<val_ty>(args)...)), "flx/memory.hpp::construct_at: your constructor should be noexcept.");

	return ::new (static_cast<void*>(location), FLX_ nothrow, FLX_ use_flx) ty(FLX_ forward<val_ty>(args)...);
}

FLX_API_ template <FLX_ copy_constructible ty>
IMP_DEPRICATE_EXCEPTIONS_
constexpr ty* copy_construct_at(ty* const location, const ty& other)
{
	return ::new (static_cast<void*>(location), FLX_ use_flx) ty(other);
}

FLX_API_ template <FLX_ copy_constructible ty>
constexpr ty* copy_construct_at(ty* const location, const ty& other, [[maybe_unused]] IMP_ nothrow_tag) noexcept
{
	static_assert(noexcept(ty(other)), "flx/memory.hpp::copy_construct_at: your copy constructor should be noexcept.");

	return ::new (static_cast<void*>(location), FLX_ nothrow, FLX_ use_flx) ty(other);
}

FLX_API_ template <FLX_ move_constructible ty>
IMP_DEPRICATE_EXCEPTIONS_
constexpr ty* move_construct_at(ty* const location, ty&& other)
{
	return ::new (static_cast<void*>(location), FLX_ use_flx) ty(FLX_ move(other));
}

FLX_API_ template <FLX_ move_constructible ty>
constexpr ty* move_construct_at(ty* const location, ty&& other, [[maybe_unused]] IMP_ nothrow_tag) noexcept
{
	static_assert(noexcept(ty(FLX_ move(other))), "flx/memory.hpp::move_construct_at: your move constructor should be noexcept.");

	return ::new (static_cast<void*>(location), FLX_ nothrow, FLX_ use_flx) ty(FLX_ move(other));
}



// ===== unique_ptr ===== //

FLX_API_ template<FLX_ can_form_pointer ty>
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
        assert(this != &other && "flx/memory.hpp::unique_ptr::operator= assigning to self is forbidden.");

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
        assert(owned_ptr != nullptr && "flx/memory.hpp::unique_ptr::operator* dereferencing a nullptr.");

        return *owned_ptr;
    }

    constexpr ty* operator->() const noexcept
    {
        assert(owned_ptr != nullptr && "flx/memory.hpp::unique_ptr::operator-> dereferencing a nullptr.");

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
        assert(ptr != owned_ptr && "flx/memory.hpp::unique_ptr::reset resetting with self is forbidden.");

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

FLX_API_ template<FLX_ can_form_pointer ty>
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
        assert(this != &other && "flx/memory.hpp::unique_ptr::operator= assigning to self is forbidden.");

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
        assert(ptr != owned_ptr && "flx/memory.hpp::unique_ptr::reset resetting with self is forbidden.");

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

FLX_API_ template<typename ty, typename... args_ty>
[[nodiscard("Discarding created flx::unique_ptr will result in memory leak.")]]
inline constexpr FLX_ unique_ptr<ty> make_unique(args_ty&&... args)
{
    return FLX_ unique_ptr<ty>(new ty(FLX_ forward<args_ty>(args)...));
}



// ===== default_allocator ===== //

// For now, FLX aims to be nothrow, so this allocator is nothrow
FLX_API_ template<FLX_ allocatable ty>
struct default_raw_allocator
{
    //TODO: finish allocator
};

FLX_END_

#endif // IMP_MEMORY_HPP_