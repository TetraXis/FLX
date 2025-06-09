#ifndef FLX_UNIQUE_PTR_HPP
#define FLX_UNIQUE_PTR_HPP

#include "flx_types.hpp"

#ifndef NDEBUG
#include <cassert>
#else
#define assert(expr) ((void)0)
#endif // !NDEBUG

namespace flx
{
    template<typename ty>
    struct unique_ptr
    {
    flx_private:
        ty* owned_ptr = nullptr;

    flx_public:
        explicit constexpr unique_ptr(ty* ptr = nullptr) noexcept 
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
            assert(this != &other && "flx_unique_ptr.hpp::unique_ptr::operator= assigning to self is forbidden.");

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
            assert(owned_ptr != nullptr && "flx_unique_ptr.hpp::unique_ptr::operator* dereferencing a nullptr.");

            return *owned_ptr;
        }

        constexpr ty* operator->() const noexcept
        {
            assert(owned_ptr != nullptr && "flx_unique_ptr.hpp::unique_ptr::operator-> dereferencing a nullptr.");

            return owned_ptr;
        }

        [[nodiscard("flx_unique_ptr.hpp::unique_ptr is a simple wrapper around heap allocated memory. Calling flx_unique_ptr.hpp::unique_ptr::release and discarding will cause memory leaks.")]]
        constexpr ty* release() noexcept
        {
            ty* ptr = owned_ptr;
            owned_ptr = nullptr;
            return ptr;
        }

        constexpr void reset(ty* ptr = nullptr) noexcept
        {
            assert(ptr != owned_ptr && "flx_unique_ptr.hpp::unique_ptr::reset resetting with self is forbidden.");

            delete owned_ptr;
            owned_ptr = ptr;
        }

        constexpr void swap(unique_ptr& other) noexcept
        {
            ty* temp_ptr = owned_ptr;
            owned_ptr = other.owned_ptr;
            other.owned_ptr = temp_ptr;
        }
    };

    template<typename ty>
    struct unique_ptr<ty[]>
    {
    flx_private:
        ty* owned_ptr = nullptr;

    flx_public:
        explicit constexpr unique_ptr(ty* ptr = nullptr) noexcept 
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
            assert(this != &other && "flx_unique_ptr.hpp::unique_ptr::operator= assigning to self is forbidden.");

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

        [[nodiscard("flx_unique_ptr.hpp::unique_ptr is a simple wrapper around heap allocated memory. Calling flx_unique_ptr.hpp::unique_ptr::release and discarding will cause memory leaks.")]]
        constexpr ty* release() noexcept
        {
            ty* ptr = owned_ptr;
            owned_ptr = nullptr;
            return ptr;
        }

        constexpr void reset(ty* ptr = nullptr) noexcept
        {
            assert(ptr != owned_ptr && "flx_unique_ptr.hpp::unique_ptr::reset resetting with self is forbidden.");

            delete[] owned_ptr;
            owned_ptr = ptr;
        }

        constexpr void swap(unique_ptr& other) noexcept
        {
            ty* temp_ptr = owned_ptr;
            owned_ptr = other.owned_ptr;
            other.owned_ptr = temp_ptr;
        }
    };

    template<typename ty, typename... args_ty>
    constexpr flx::unique_ptr<ty> make_unique(args_ty&&... args)
    {
        return flx::unique_ptr<ty>(new ty(static_cast<args_ty&&>(args)...));
    }
} // namespace flx

#endif // !FLX_UNIQUE_PTR_HPP