#ifndef FLX_DYNAMIC_ARRAY_HPP
#define FLX_DYNAMIC_ARRAY_HPP

#include "flx_types.hpp"

#ifndef NDEBUG
#include <cassert>
#else
#define assert(expr) ((void)0)
#endif // !NDEBUG

namespace flx
{
	template <typename ty>
	struct dynamic_array
	{
		static constexpr u64 PRE_ALLOCATED_CAPACITY = 4;

		struct iterator
		{
			friend dynamic_array;

		flx_private:
			ty* ptr = nullptr;

		flx_public:
			constexpr iterator() noexcept = default;
			constexpr ~iterator() noexcept = default;

			constexpr explicit iterator(ty* new_ptr = nullptr) noexcept
				: ptr(new_ptr)
			{
			}

			constexpr iterator(const dynamic_array& arr, u64 idx = 0) noexcept
				: ptr(arr.data + idx)
			{
			}

			constexpr ty& operator*() const noexcept
			{
				return *ptr;
			}

			constexpr ty* operator->() const noexcept
			{
				return ptr;
			}

			constexpr bool operator==(const iterator& other) const noexcept
			{
				return ptr == other.ptr;
			}

			constexpr bool operator!=(const iterator& other) const noexcept
			{
				return ptr != other.ptr;
			}

			constexpr iterator operator+(u64 idx) const noexcept
			{
				return iterator(ptr + idx);
			}

			constexpr iterator& operator+=(u64 idx) noexcept
			{
				ptr += idx;
				return *this;
			}

			constexpr iterator& operator++() noexcept // prefix ++
			{
				++ptr;
				return *this;
			}

			constexpr iterator operator-(u64 idx) const noexcept
			{
				return iterator(ptr - idx);
			}

			constexpr iterator& operator-=(u64 idx) noexcept
			{
				ptr -= idx;
				return *this;
			}

			constexpr iterator& operator--() noexcept // prefix --
			{
				--ptr;
				return *this;
			}
		};

		struct const_iterator
		{
			friend dynamic_array;

		flx_private:
			const ty* ptr = nullptr;

		flx_public:
			constexpr const_iterator() noexcept = default;
			constexpr ~const_iterator() noexcept = default;

			constexpr explicit const_iterator(const ty* new_ptr = nullptr) noexcept
				: ptr(new_ptr)
			{
			}

			constexpr const_iterator(const dynamic_array& arr, u64 idx = 0) noexcept
				: ptr(arr.data + idx)
			{
			}

			constexpr const ty& operator*() const noexcept
			{
				return *ptr;
			}

			constexpr const ty* operator->() const noexcept
			{
				return ptr;
			}

			constexpr bool operator==(const const_iterator& other) const noexcept
			{
				return ptr == other.ptr;
			}

			constexpr bool operator!=(const const_iterator& other) const noexcept
			{
				return ptr != other.ptr;
			}

			constexpr const_iterator operator+(u64 idx) const noexcept
			{
				return const_iterator(ptr + idx);
			}

			constexpr const_iterator& operator+=(u64 idx) noexcept
			{
				ptr += idx;
				return *this;
			}

			constexpr const_iterator& operator++() noexcept // prefix ++
			{
				++ptr;
				return *this;
			}

			constexpr const_iterator operator-(u64 idx) const noexcept
			{
				return const_iterator(ptr - idx);
			}

			constexpr const_iterator& operator-=(u64 idx) noexcept
			{
				ptr -= idx;
				return *this;
			}

			constexpr const_iterator& operator--() noexcept // prefix --
			{
				--ptr;
				return *this;
			}
		};

	flx_private:
		ty* data = new ty[PRE_ALLOCATED_CAPACITY];
		u64 size = 0;
		u64 capacity = PRE_ALLOCATED_CAPACITY;

	flx_public:
		constexpr dynamic_array() noexcept = default;

		constexpr ~dynamic_array() noexcept
		{
			for (u64 i = 0; i < size; ++i)
			{
				data[i].~ty();
			}

			::operator delete(data);
		}

		constexpr iterator begin() noexcept
		{
			return iterator(data);
		}

		constexpr iterator end() noexcept
		{
			return iterator(data + size);
		}

		constexpr const_iterator begin() const noexcept
		{
			return iterator(data);
		}

		constexpr const_iterator end() const noexcept
		{
			return iterator(data + size);
		}

		constexpr const_iterator cbegin() const noexcept
		{
			return iterator(data);
		}

		constexpr const_iterator cend() const noexcept
		{
			return iterator(data + size);
		}
	}; // dynamic_array
} // namespace flx

#endif // !FLX_DYNAMIC_ARRAY_HPP
