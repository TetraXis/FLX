#ifndef FLX_DYNAMIC_ARRAY_HPP
#define FLX_DYNAMIC_ARRAY_HPP

#include "flx_types.hpp"
#include "flx_new.hpp"
#include "flx_type_traits.hpp"
#include "flx_concepts.hpp"
#include "flx_utility.hpp"

//TODO: add exceptions

#ifndef NDEBUG
#include <cassert>
#else
#define assert(expr) ((void)0)
#endif // !NDEBUG

namespace flx
{
	// Now assumes nothing will throw
	// TODO: fix it, and check all the functions
	template <typename ty, flx::unsigned_integral size_ty = u64>
	struct dynamic_array
	{
		static_assert(flx::destructible<ty>, "flx_dynamic_array.hpp::dynamic_array: dynamic_array can only work with nothrow destructible objects.");

		static constexpr size_ty PREALLOCATED_CAPACITY = 0;

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

			constexpr iterator(const dynamic_array& arr, size_ty idx = 0) noexcept
				: ptr(arr.data_ + idx)
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

			constexpr iterator operator+(size_ty idx) const noexcept
			{
				return iterator(ptr + idx);
			}

			constexpr iterator& operator+=(size_ty idx) noexcept
			{
				ptr += idx;
				return *this;
			}

			constexpr iterator& operator++() noexcept // prefix ++
			{
				++ptr;
				return *this;
			}

			constexpr iterator operator-(size_ty idx) const noexcept
			{
				return iterator(ptr - idx);
			}

			constexpr iterator& operator-=(size_ty idx) noexcept
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

			constexpr const_iterator(const dynamic_array& arr, size_ty idx = 0) noexcept
				: ptr(arr.data_ + idx)
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

			constexpr const_iterator operator+(size_ty idx) const noexcept
			{
				return const_iterator(ptr + idx);
			}

			constexpr const_iterator& operator+=(size_ty idx) noexcept
			{
				ptr += idx;
				return *this;
			}

			constexpr const_iterator& operator++() noexcept // prefix ++
			{
				++ptr;
				return *this;
			}

			constexpr const_iterator operator-(size_ty idx) const noexcept
			{
				return const_iterator(ptr - idx);
			}

			constexpr const_iterator& operator-=(size_ty idx) noexcept
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
		//ty* data_ = static_cast<ty*>(flx::allocate(PREALLOCATED_CAPACITY * sizeof(ty), flx::nothrow));
		//ty* data_ = static_cast<ty*>(::operator new (PREALLOCATED_CAPACITY * sizeof(ty), flx::nothrow, flx::use_flx));
		ty* data_{};
		size_ty size_{};
		size_ty capacity_{};

	flx_public:
		constexpr dynamic_array() noexcept
		{
			try
			{
				data_ = static_cast<ty*>(::operator new (PREALLOCATED_CAPACITY * sizeof(ty)));
				size_ = 0;
				capacity_ = PREALLOCATED_CAPACITY;
			}
			catch (...)
			{
				data_ = nullptr;
				size_ = 0;
				capacity_ = 0;

				assert(false, "flx_dynamic_array.hpp::dynamic_array::dynamic_array(): bad alloc.");
				last_error = "flx_dynamic_array.hpp::dynamic_array::dynamic_array(): bad alloc.";
			}
		}

		constexpr ~dynamic_array() noexcept
		{
			if constexpr (flx::is_class<ty> && !flx::is_trivially_destructible<ty>)
			{
				for (size_ty i = 0; i < size_; ++i)
				{
					data_[i].~ty();
				}
			}

			//flx::deallocate(data_);
			::operator delete(data_);
		}

		// TODO: nothrow copy
		constexpr dynamic_array(const dynamic_array& other) noexcept requires flx::copy_constructible<ty>
		{
			try
			{
				data_(static_cast<ty*>(::operator new (other.capacity_ * sizeof(ty))));
				capacity_ = other.capacity_;
				size_ = 0;
				for (size_ = 0; size_ < other.size_; size_++)
				{
					//::new (&data_[size_], true) ty(other.data_[size_]);
					flx::copy_construct_at(&data_[size_], other.data_[size_]);
				}
			}
			catch (...)
			{
				data_ = nullptr;
				capacity_ = 0;
				size_ = 0;

				assert(false, "flx_dynamic_array.hpp::dynamic_array::dynamic_array(const dynamic_array&): bad alloc.");
				last_error = "flx_dynamic_array.hpp::dynamic_array::dynamic_array(const dynamic_array&): bad alloc.";
			}
		}

		constexpr dynamic_array(dynamic_array&& other) noexcept
			: size_(other.size_), capacity_(other.capacity_),
			data_(other.data_)
		{
			other.data_ = nullptr;
			other.size_ = 0;
			other.capacity_ = 0;
		}

		constexpr dynamic_array(const size_ty count, const ty& val = ty()) noexcept requires flx::copy_constructible<ty>
		{
			allocate_raw_array(count);

			while (size_ != count)
			{
				//::new (&data_[size_], true) ty(val);
				flx::copy_construct_at(&data_[size_], val);
				++size_;
			}
		}

		constexpr ty* data() noexcept
		{
			return data_;
		}

		constexpr iterator begin() noexcept
		{
			return iterator(data_);
		}

		constexpr iterator end() noexcept
		{
			return iterator(data_ + size_);
		}

		constexpr const_iterator begin() const noexcept
		{
			return const_iterator(data_);
		}

		constexpr const_iterator end() const noexcept
		{
			return const_iterator(data_ + size_);
		}

		constexpr const_iterator cbegin() const noexcept
		{
			return const_iterator(data_);
		}

		constexpr const_iterator cend() const noexcept
		{
			return const_iterator(data_ + size_);
		}

		constexpr bool empty() const noexcept
		{
			return size_ == 0;
		}

		constexpr void push_back(const ty& val) noexcept requires flx::copy_constructible<ty>
		{
			if (size_ >= capacity_)
			{
				reallocate(capacity_ + 1);
			}

			flx::copy_construct_at(&data_[size_], val);
			//::new (&data_[size_], true) ty(val);
			++size_;
		}

		constexpr void push_back(ty&& val) noexcept
		{
			if (size_ >= capacity_)
			{
				reallocate(capacity_ + 1);
			}

			data_[size_] = flx::move(val);
			++size_;
		}

		template<typename... val_ty>
		constexpr void emplace_back(val_ty&&... vals) noexcept
		{
			if (size_ >= capacity_)
			{
				reallocate(capacity_ + 1);
			}

			//::new (&data_[size_], true) ty( flx::forward<val_ty>(vals)... );
			flx::construct_at(&data_[size_], flx::forward<val_ty>(vals)...);
			++size_;
		}

		constexpr void pop_back() noexcept
		{
			assert(!empty() && "flx_dynamic_array::dynamic_array::pop_back: popping on empty array.");

			--size_; 
			if constexpr (flx::is_class<ty> && !flx::is_trivially_destructible<ty>)
			{
				data_[size_].~ty();
			}
		}

		constexpr void erase(iterator where) noexcept
		{
			assert((where.get() >= begin().get() && where.get() < end().get()) && "flx_dynamic_array.hpp::dynamic_array::erase: erase position is out of bounds.");

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
			assert((first.get() >= begin().get() && first.get() < end().get()) && "flx_dynamic_array.hpp::dynamic_array::erase: first erase position is out of bounds.");
			assert((last.get() >= begin().get() && last.get() < end().get()) && "flx_dynamic_array.hpp::dynamic_array::erase: last erase position is out of bounds.");
			assert(first.get() <= last.get() && "flx_dynamic_array.hpp::dynamic_array::erase: erase region is invalid.");
			
			iterator temp(first);
			size_ty diff = last.get() - first.get();

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

		constexpr size_ty size() const noexcept
		{
			return size_;
		}

		constexpr size_ty capacity() const noexcept
		{
			return capacity_;
		}

		constexpr ty& operator[](size_ty pos) noexcept
		{
			assert(pos < size_ && "flx_dynamic_array.hpp::dynamic_array::operator[]: position is out of bounds.");
		
			return data_[pos];
		}

		constexpr const ty& operator[](size_ty pos) const noexcept
		{
			assert(pos < size_ && "flx_dynamic_array.hpp::dynamic_array::operator[]: position is out of bounds.");
		
			return data_[pos];
		}

	flx_private:
		/*constexpr void reallocate() noexcept
		{
			capacity_ *= GROWTH_RATE;
			if constexpr (PREALLOCATED_CAPACITY == 0)
			{
				if (capacity_ == 0)
				{
					capacity_ = 1;
				}
			}
			ty* new_data = static_cast<ty*>(::operator new(capacity_ * sizeof(ty)));

			for (size_ty i = 0; i < size_; i++)
			{
				::new (&new_data[i], true) ty(flx::move(data_[i]));
				if constexpr (flx::is_class<ty> && !flx::is_trivially_destructible<ty>)
				{
					data_[i].~ty();
				}
			}

			::operator delete(data_);
			data_ = new_data;
		}*/

		constexpr void reallocate(const size_ty new_capacity) noexcept
		{
			capacity_ = calculate_growth(new_capacity);

			assert(capacity_ > size_ && "flx_dynamic_array.hpp::dynamic_array::reallocate: new capacity is smaller than size.");

			//ty* new_data = static_cast<ty*>(::operator new(capacity_ * sizeof(ty)));
			ty* new_data = static_cast<ty*>(flx::allocate(capacity_ * sizeof(ty), flx::nothrow));

			for (size_ty i = 0; i < size_; i++)
			{
				//::new (&new_data[i], true) ty(flx::move(data_[i]));
				flx::move_construct_at(&new_data[i], flx::move(data_[i]));

				if constexpr (flx::is_class<ty> && !flx::is_trivially_destructible<ty>)
				{
					data_[i].~ty();
				}
			}

			::operator delete(data_);
			//flx::deallocate(data_);
			data_ = new_data;
		}

		// Allocates a chuck of [new_capacity]
		constexpr void allocate_raw_array(const size_ty new_capacity)
		{
			assert(capacity_ > size_ && "flx_dynamic_array.hpp::dynamic_array::allocate_raw_array: new capacity is smaller than size.");

			capacity_ = new_capacity;
			data_ = static_cast<ty*>(::operator new(capacity_ * sizeof(ty)));
			//data_ = static_cast<ty*>(flx::allocate(capacity_ * sizeof(ty)), flx::nothrow);
		}

		// Should be called with (capacity + 1)
		constexpr size_ty calculate_growth(const size_ty new_capacity) const noexcept
		{
			size_ty desired = capacity_ + (capacity_ >> 1);

			return desired > capacity_ ? desired : new_capacity;
		}
	}; // dynamic_array
} // namespace flx

#endif // !FLX_DYNAMIC_ARRAY_HPP
