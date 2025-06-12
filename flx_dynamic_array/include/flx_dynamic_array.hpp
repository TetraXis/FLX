#ifndef FLX_DYNAMIC_ARRAY_HPP
#define FLX_DYNAMIC_ARRAY_HPP

#include "flx_types.hpp"
#include "flx_type_traits.hpp"

#ifndef NDEBUG
#include <cassert>
#else
#define assert(expr) ((void)0)
#endif // !NDEBUG

namespace flx
{
	/// <summary>
	/// NOTE:
	/// 1. std::vector calls destructors for objects when reallocating. Not sure why.
	/// Since we MOVE the data anyway, why should we?
	/// 2. new ty[] calls constructors, why should we? Only call when actually constructing.
	/// </summary>

	template <typename ty>
	struct dynamic_array
	{
		static constexpr u64 PRE_ALLOCATED_CAPACITY = 4;
		static constexpr u64 GROWTH_RATE = 2;

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
		ty* data = static_cast<ty*>(::operator new(PRE_ALLOCATED_CAPACITY * sizeof(ty)));
		u64 size = 0;
		u64 capacity = PRE_ALLOCATED_CAPACITY;

	flx_public:
		constexpr dynamic_array() noexcept
		{
		}

		constexpr ~dynamic_array() noexcept
		{
			for (u64 i = 0; i < size; ++i)
			{
				data[i].~ty();
			}

			::operator delete(data);
		}

		constexpr dynamic_array(i64 count, const ty& val = ty()) noexcept
		{
			reallocate(count);

			while (size != count)
			{
				new (data[size]) ty(val);
				++size;
			}
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
			return const_iterator(data);
		}

		constexpr const_iterator end() const noexcept
		{
			return const_iterator(data + size);
		}

		constexpr const_iterator cbegin() const noexcept
		{
			return const_iterator(data);
		}

		constexpr const_iterator cend() const noexcept
		{
			return const_iterator(data + size);
		}

		constexpr void push_back(ty&& val) noexcept
		{
			if (size == capacity)
			{
				reallocate();
			}

			data[size] = val;
			++size;
		}

		template<typename... val_ty>
		constexpr void emplace_back(val_ty&&... vals) noexcept
		{
			if (size == capacity)
			{
				reallocate();
			}

			new (&data[size]) ty(flx::forward<val_ty>(vals)...);
			++size;
		}

		constexpr ty& operator[](u64 pos) noexcept
		{
			assert(pos < size && "flx_dynamic_array::operator[] position is out of bounds.");
		
			return data[pos];
		}

		constexpr const ty& operator[](u64 pos) const noexcept
		{
			assert(pos < size && "flx_dynamic_array::operator[] position is out of bounds.");
		
			return data[pos];
		}

	flx_private:
		constexpr void reallocate() noexcept
		{
			capacity *= GROWTH_RATE;
			ty* new_data = static_cast<ty*>(::operator new(capacity * sizeof(ty)));

			for (u64 i = 0; i < size; i++)
			{
				new_data[i] = flx::move(data[i]);
			}

			::operator delete(data);
			data = new_data;
		}

		constexpr void reallocate(u64 new_capacity) noexcept
		{
			assert(new_capacity < size && "flx_dynamic_array.hpp::reallocate new capacity is smaller than size.");

			capacity = new_capacity;
			ty* new_data = static_cast<ty*>(::operator new(capacity * sizeof(ty)));

			for (u64 i = 0; i < size; i++)
			{
				new_data[i] = flx::move(data[i]);
			}

			::operator delete(data);
			data = new_data;
		}
	}; // dynamic_array
} // namespace flx

#endif // !FLX_DYNAMIC_ARRAY_HPP
