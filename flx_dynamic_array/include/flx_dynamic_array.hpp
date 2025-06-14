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

			constexpr ty* get() const noexcept
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

			constexpr const_iterator(const iterator& iter) noexcept
				: ptr(iter.ptr)
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

			constexpr const ty* get() const noexcept
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
		u64 size_ = 0;
		u64 capacity_ = PRE_ALLOCATED_CAPACITY;

	flx_public:
		constexpr dynamic_array() noexcept
		{
		}

		constexpr ~dynamic_array() noexcept
		{
			if constexpr (flx::is_class<ty> && !flx::is_trivially_destructible<ty>)
			{
				for (u64 i = 0; i < size_; ++i)
				{
					data[i].~ty();
				}
			}

			::operator delete(data);
		}

		constexpr dynamic_array(const dynamic_array& other) noexcept
			: capacity_(other.capacity_),
			data(static_cast<ty*>(::operator new(other.capacity_ * sizeof(ty))))
		{
			for (size_ = 0; size_ < other.size_; size_++)
			{
				new (&data[size_]) ty(other.data[size_]);
			}
		}

		constexpr dynamic_array(dynamic_array&& other) noexcept
			: size_(other.size_), capacity_(other.capacity_),
			data(other.data)
		{
			other.data = static_cast<ty*>(::operator new(PRE_ALLOCATED_CAPACITY * sizeof(ty)));
		}

		constexpr dynamic_array(i64 count, const ty& val = ty()) noexcept
		{
			reallocate(count);

			while (size_ != count)
			{
				new (&data[size_]) ty(val);
				++size_;
			}
		}

		constexpr iterator begin() noexcept
		{
			return iterator(data);
		}

		constexpr iterator end() noexcept
		{
			return iterator(data + size_);
		}

		constexpr const_iterator begin() const noexcept
		{
			return const_iterator(data);
		}

		constexpr const_iterator end() const noexcept
		{
			return const_iterator(data + size_);
		}

		constexpr const_iterator cbegin() const noexcept
		{
			return const_iterator(data);
		}

		constexpr const_iterator cend() const noexcept
		{
			return const_iterator(data + size_);
		}

		constexpr void push_back(const ty& val) noexcept
		{
			if (size_ == capacity_)
			{
				reallocate();
			}

			new (&data[size_]) ty(val);
			++size_;
		}

		constexpr void push_back(ty&& val) noexcept
		{
			if (size_ == capacity_)
			{
				reallocate();
			}

			data[size_] = val;
			++size_;
		}

		template<typename... val_ty>
		constexpr void emplace_back(val_ty&&... vals) noexcept
		{
			if (size_ == capacity_)
			{
				reallocate();
			}

			new (&data[size_]) ty(flx::forward<val_ty>(vals)...);
			++size_;
		}

		constexpr void erase(iterator where) noexcept
		{
			assert((where.get() >= begin().get() && where.get() < end().get()) && "flx_dynamic_array.hpp::flx_dynamic_array::erase erase position is out of bounds.");

			if constexpr (flx::is_class<ty> && !flx::is_trivially_destructible<ty>)
			{
				where->~ty();
			}

			while (where != end() - 1)
			{
				*where = flx::move(*(where + 1));
				++where;
			}
			--size_;
		}

		constexpr void erase(iterator first, iterator last) noexcept
		{
			assert((first.get() >= begin().get() && first.get() < end().get()) && "flx_dynamic_array.hpp::flx_dynamic_array::erase first erase position is out of bounds.");
			assert((last.get() >= begin().get() && last.get() < end().get()) && "flx_dynamic_array.hpp::flx_dynamic_array::erase last erase position is out of bounds.");
			assert(first.get() <= last.get() && "flx_dynamic_array.hpp::flx_dynamic_array::erase erase region is invalid.");
			
			iterator temp(first);
			u64 diff = last.get() - first.get();

			if constexpr (flx::is_class<ty> && !flx::is_trivially_destructible<ty>)
			{
				while (temp != last)
				{
					temp->~ty();
					++temp;
				}
			}

			temp = last;
			
			while (temp != end())
			{
				*(temp.get() - diff) = flx::move(*temp);
				++temp;
			}

			size_ -= diff;
		}

		constexpr u64 size() const noexcept
		{
			return size_;
		}

		constexpr u64 capacity() const noexcept
		{
			return capacity_;
		}

		constexpr ty& operator[](u64 pos) noexcept
		{
			assert(pos < size_ && "flx_dynamic_array.hpp::flx_dynamic_array::operator[] position is out of bounds.");
		
			return data[pos];
		}

		constexpr const ty& operator[](u64 pos) const noexcept
		{
			assert(pos < size_ && "flx_dynamic_array.hpp::flx_dynamic_array::operator[] position is out of bounds.");
		
			return data[pos];
		}

	flx_private:
		constexpr void reallocate() noexcept
		{
			capacity_ *= GROWTH_RATE;
			ty* new_data = static_cast<ty*>(::operator new(capacity_ * sizeof(ty)));

			for (u64 i = 0; i < size_; i++)
			{
				new (&new_data[i]) ty(flx::move(data[i]));
				if constexpr (flx::is_class<ty> && !flx::is_trivially_destructible<ty>)
				{
					data[i].~ty();
				}
			}

			::operator delete(data);
			data = new_data;
		}

		constexpr void reallocate(u64 new_capacity) noexcept
		{
			assert(new_capacity < size_ && "flx_dynamic_array.hpp::flx_dynamic_array::reallocate new capacity is smaller than size.");

			capacity_ = new_capacity;
			ty* new_data = static_cast<ty*>(::operator new(capacity_ * sizeof(ty)));

			for (u64 i = 0; i < size_; i++)
			{
				new (&new_data[i]) ty(flx::move(data[i]));
				if constexpr (flx::is_class<ty> && !flx::is_trivially_destructible<ty>)
				{
					data[i].~ty();
				}
			}

			::operator delete(data);
			data = new_data;
		}
	}; // dynamic_array
} // namespace flx

#endif // !FLX_DYNAMIC_ARRAY_HPP
