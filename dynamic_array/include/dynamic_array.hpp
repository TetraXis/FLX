#ifndef IMP_FLX_DYNAMIC_ARRAY_HPP_
#define IMP_FLX_DYNAMIC_ARRAY_HPP_

#include "flx/imp_core.hpp"
#include "flx/new.hpp"
#include "flx/type_traits.hpp"
#include "flx/concepts.hpp"
#include "flx/utility.hpp"

// dynamic_array does not support IMP_FLX_DARR_CONSTEXPR_ yet
#define IMP_FLX_DARR_CONSTEXPR_ 

FLX_BEGIN_

FLX_API_ template <typename ty, FLX_ unsigned_integral size_ty = u64>
struct dynamic_array
{
	static_assert(FLX_ destructible<ty>, "flx/dynamic_array.hpp::dynamic_array: dynamic_array can only work with nothrow destructible objects.");

	static constexpr size_ty PREALLOCATED_CAPACITY = 0;

	FLX_API_ struct iterator
	{
		friend dynamic_array;

	flx_private:
		ty* ptr = nullptr;

	flx_public:
		IMP_FLX_DARR_CONSTEXPR_ iterator() noexcept = default;
		IMP_FLX_DARR_CONSTEXPR_ ~iterator() noexcept = default;

		IMP_FLX_DARR_CONSTEXPR_ explicit iterator(ty* new_ptr = nullptr) noexcept
			: ptr(new_ptr)
		{
		}

		IMP_FLX_DARR_CONSTEXPR_ iterator(const dynamic_array& arr, size_ty idx = 0) noexcept
			: ptr(arr.data_ + idx)
		{
		}

		IMP_FLX_DARR_CONSTEXPR_ ty& operator*() const noexcept
		{
			return *ptr;
		}

		IMP_FLX_DARR_CONSTEXPR_ ty* operator->() const noexcept
		{
			return ptr;
		}

		IMP_FLX_DARR_CONSTEXPR_ ty* get() const noexcept
		{
			return ptr;
		}

		IMP_FLX_DARR_CONSTEXPR_ bool operator==(const iterator& other) const noexcept
		{
			return ptr == other.ptr;
		}

		IMP_FLX_DARR_CONSTEXPR_ bool operator!=(const iterator& other) const noexcept
		{
			return ptr != other.ptr;
		}

		IMP_FLX_DARR_CONSTEXPR_ iterator operator+(size_ty idx) const noexcept
		{
			return iterator(ptr + idx);
		}

		IMP_FLX_DARR_CONSTEXPR_ iterator& operator+=(size_ty idx) noexcept
		{
			ptr += idx;
			return *this;
		}

		IMP_FLX_DARR_CONSTEXPR_ iterator& operator++() noexcept // prefix ++
		{
			++ptr;
			return *this;
		}

		IMP_FLX_DARR_CONSTEXPR_ iterator operator-(size_ty idx) const noexcept
		{
			return iterator(ptr - idx);
		}

		IMP_FLX_DARR_CONSTEXPR_ iterator& operator-=(size_ty idx) noexcept
		{
			ptr -= idx;
			return *this;
		}

		IMP_FLX_DARR_CONSTEXPR_ iterator& operator--() noexcept // prefix --
		{
			--ptr;
			return *this;
		}
	};

	FLX_API_ struct const_iterator
	{
		friend dynamic_array;

	flx_private:
		const ty* ptr = nullptr;

	flx_public:
		IMP_FLX_DARR_CONSTEXPR_ const_iterator() noexcept = default;
		IMP_FLX_DARR_CONSTEXPR_ ~const_iterator() noexcept = default;

		IMP_FLX_DARR_CONSTEXPR_ explicit const_iterator(const ty* new_ptr = nullptr) noexcept
			: ptr(new_ptr)
		{
		}

		IMP_FLX_DARR_CONSTEXPR_ const_iterator(const dynamic_array& arr, size_ty idx = 0) noexcept
			: ptr(arr.data_ + idx)
		{
		}

		IMP_FLX_DARR_CONSTEXPR_ const_iterator(const iterator& iter) noexcept
			: ptr(iter.ptr)
		{
		}

		IMP_FLX_DARR_CONSTEXPR_ const ty& operator*() const noexcept
		{
			return *ptr;
		}

		IMP_FLX_DARR_CONSTEXPR_ const ty* operator->() const noexcept
		{
			return ptr;
		}

		IMP_FLX_DARR_CONSTEXPR_ const ty* get() const noexcept
		{
			return ptr;
		}

		IMP_FLX_DARR_CONSTEXPR_ bool operator==(const const_iterator& other) const noexcept
		{
			return ptr == other.ptr;
		}

		IMP_FLX_DARR_CONSTEXPR_ bool operator!=(const const_iterator& other) const noexcept
		{
			return ptr != other.ptr;
		}

		IMP_FLX_DARR_CONSTEXPR_ const_iterator operator+(size_ty idx) const noexcept
		{
			return const_iterator(ptr + idx);
		}

		IMP_FLX_DARR_CONSTEXPR_ const_iterator& operator+=(size_ty idx) noexcept
		{
			ptr += idx;
			return *this;
		}

		IMP_FLX_DARR_CONSTEXPR_ const_iterator& operator++() noexcept // prefix ++
		{
			++ptr;
			return *this;
		}

		IMP_FLX_DARR_CONSTEXPR_ const_iterator operator-(size_ty idx) const noexcept
		{
			return const_iterator(ptr - idx);
		}

		IMP_FLX_DARR_CONSTEXPR_ const_iterator& operator-=(size_ty idx) noexcept
		{
			ptr -= idx;
			return *this;
		}

		IMP_FLX_DARR_CONSTEXPR_ const_iterator& operator--() noexcept // prefix --
		{
			--ptr;
			return *this;
		}
	};

flx_private:
	//ty* data_ = static_cast<ty*>(FLX_ allocate(PREALLOCATED_CAPACITY * sizeof(ty), FLX_ nothrow));
	//ty* data_ = static_cast<ty*>(::operator new (PREALLOCATED_CAPACITY * sizeof(ty), FLX_ nothrow, FLX_ use_flx));

	// we are storing size_ and capacity_ so we can choose their size and make smaller memory footprint
	ty* data_{};
	size_ty size_{};
	size_ty capacity_{};

flx_public:
	IMP_FLX_DARR_CONSTEXPR_ dynamic_array() noexcept
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

			FLX_ASSERT_(false && "flx/dynamic_array.hpp::dynamic_array::dynamic_array(): bad alloc.");

			FLX_ terminate("flx/dynamic_array.hpp::dynamic_array::dynamic_array(): bad alloc.");
		}
	}

	IMP_FLX_DARR_CONSTEXPR_ ~dynamic_array() noexcept
	{
		clear();

		//FLX_ deallocate(data_);
		::operator delete(data_);
	}

	IMP_FLX_DARR_CONSTEXPR_ dynamic_array(const dynamic_array& other) noexcept requires FLX_ is_nothrow_copy_constructible<ty>
	{
		try
		{
			data_ = static_cast<ty*>(::operator new (other.capacity_ * sizeof(ty)));
			capacity_ = other.capacity_;
			size_ = 0;
			for (size_ = 0; size_ < other.size_; size_++)
			{
				//::new (&data_[size_], true) ty(other.data_[size_]);
				FLX_ copy_construct_at(&data_[size_], other.data_[size_]);
			}
		}
		catch (...)
		{
			data_ = nullptr;
			capacity_ = 0;
			size_ = 0;

			FLX_ASSERT_(false && "flx/dynamic_array.hpp::dynamic_array::dynamic_array(const dynamic_array&): bad alloc.");

			FLX_ terminate("flx/dynamic_array.hpp::dynamic_array::dynamic_array(const dynamic_array&): bad alloc.");
		}
	}

	IMP_FLX_DARR_CONSTEXPR_ dynamic_array(dynamic_array&& other) noexcept
		: size_(other.size_), capacity_(other.capacity_),
		data_(other.data_)
	{
		other.data_ = nullptr;
		other.size_ = 0;
		other.capacity_ = 0;
	}

	IMP_FLX_DARR_CONSTEXPR_ dynamic_array(const size_ty count, const ty& val = ty()) noexcept requires FLX_ is_nothrow_copy_constructible<ty>
	{
		allocate_raw_array(count);

		while (size_ != count)
		{
			//::new (&data_[size_], true) ty(val);
			FLX_ copy_construct_at(&data_[size_], val);
			++size_;
		}
	}

	IMP_FLX_DARR_CONSTEXPR_ dynamic_array& operator= (const dynamic_array& other) noexcept requires FLX_ is_nothrow_copy_constructible<ty>
	{
		clear();

		if (capacity_ < other.size_)
		{
			try
			{
				::operator delete(data_);
				data_ = static_cast<ty*>(::operator new (other.size_ * sizeof(ty)));
			}
			catch (...)
			{
				data_ = nullptr;
				capacity_ = 0;
				size_ = 0;

				FLX_ASSERT_(false && "flx/dynamic_array.hpp::dynamic_array::operator=: bad alloc.");

				FLX_ terminate("flx/dynamic_array.hpp::dynamic_array::operator=: bad alloc.");
			}
		}

		for (size_ = 0; size_ < other.size_; size_++)
		{
			//::new (&data_[size_], true) ty(other.data_[size_]);
			FLX_ copy_construct_at(&data_[size_], other.data_[size_]);
		}

		return *this;
	}

	IMP_FLX_DARR_CONSTEXPR_ void clear() noexcept
	{
		if IMP_FLX_DARR_CONSTEXPR_ (FLX_ is_class<ty> && !FLX_ is_trivially_destructible<ty>)
		{
			while (size_ > 0)
			{
				data_[--size_].~ty();
			}
		}
	}

	IMP_FLX_DARR_CONSTEXPR_ ty* data() noexcept
	{
		return data_;
	}

	IMP_FLX_DARR_CONSTEXPR_ const ty* data() const noexcept
	{
		return data_;
	}

	IMP_FLX_DARR_CONSTEXPR_ iterator begin() noexcept
	{
		return iterator(data_);
	}

	IMP_FLX_DARR_CONSTEXPR_ iterator end() noexcept
	{
		return iterator(data_ + size_);
	}

	IMP_FLX_DARR_CONSTEXPR_ const_iterator begin() const noexcept
	{
		return const_iterator(data_);
	}

	IMP_FLX_DARR_CONSTEXPR_ const_iterator end() const noexcept
	{
		return const_iterator(data_ + size_);
	}

	IMP_FLX_DARR_CONSTEXPR_ const_iterator cbegin() const noexcept
	{
		return const_iterator(data_);
	}

	IMP_FLX_DARR_CONSTEXPR_ const_iterator cend() const noexcept
	{
		return const_iterator(data_ + size_);
	}

	IMP_FLX_DARR_CONSTEXPR_ bool empty() const noexcept
	{
		return size_ == 0;
	}

	IMP_FLX_DARR_CONSTEXPR_ size_ty max_size() const noexcept
	{
		size_ty temp = 0;
		return --temp;
	}

	IMP_FLX_DARR_CONSTEXPR_ void push_back(const ty& val) noexcept requires FLX_ is_nothrow_copy_constructible<ty>
	{
		if (size_ >= capacity_)
		{
			reallocate(capacity_ + 1);
		}

		FLX_ copy_construct_at(&data_[size_], val);
		//::new (&data_[size_], true) ty(val);
		++size_;
	}

	IMP_FLX_DARR_CONSTEXPR_ void push_back(ty&& val) noexcept
	{
		if (size_ >= capacity_)
		{
			reallocate(capacity_ + 1);
		}

		data_[size_] = FLX_ move(val);
		++size_;
	}

	FLX_API_ template<typename... val_ty>
	IMP_FLX_DARR_CONSTEXPR_ void emplace_back(val_ty&&... vals) noexcept
	{
		if (size_ >= capacity_)
		{
			reallocate(capacity_ + 1);
		}

		//::new (&data_[size_], true) ty( FLX_ forward<val_ty>(vals)... );
		FLX_ construct_at(&data_[size_], FLX_ forward<val_ty>(vals)...);
		++size_;
	}

	IMP_FLX_DARR_CONSTEXPR_ void pop_back() noexcept
	{
		FLX_ASSERT_(!empty() && "flx_dynamic_array::dynamic_array::pop_back: popping on empty array.");

		--size_;
		if IMP_FLX_DARR_CONSTEXPR_ (FLX_ is_class<ty> && !FLX_ is_trivially_destructible<ty>)
		{
			data_[size_].~ty();
		}
	}

	IMP_FLX_DARR_CONSTEXPR_ void erase(iterator where) noexcept
	{
		FLX_ASSERT_((where.get() >= begin().get() && where.get() < end().get()) && "flx/dynamic_array.hpp::dynamic_array::erase: erase position is out of bounds.");

		if IMP_FLX_DARR_CONSTEXPR_ (FLX_ is_class<ty> && !FLX_ is_trivially_destructible<ty>)
		{
			where->~ty();
		}

		while (where != end() - 1)
		{
			*where = FLX_ move(*(where + 1));
			++where;
		}
		--size_;
	}

	IMP_FLX_DARR_CONSTEXPR_ void erase(iterator first, iterator last) noexcept
	{
		FLX_ASSERT_((first.get() >= begin().get() && first.get() < end().get()) && "flx/dynamic_array.hpp::dynamic_array::erase: first erase position is out of bounds.");
		FLX_ASSERT_((last.get() >= begin().get() && last.get() < end().get()) && "flx/dynamic_array.hpp::dynamic_array::erase: last erase position is out of bounds.");
		FLX_ASSERT_(first.get() <= last.get() && "flx/dynamic_array.hpp::dynamic_array::erase: erase region is invalid.");

		iterator temp(first);
		size_ty diff = last.get() - first.get();

		if IMP_FLX_DARR_CONSTEXPR_ (FLX_ is_class<ty> && !FLX_ is_trivially_destructible<ty>)
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
			*(temp.get() - diff) = FLX_ move(*temp);
			++temp;
		}

		size_ -= diff;
	}

	IMP_FLX_DARR_CONSTEXPR_ size_ty size() const noexcept
	{
		return size_;
	}

	IMP_FLX_DARR_CONSTEXPR_ size_ty capacity() const noexcept
	{
		return capacity_;
	}

	IMP_FLX_DARR_CONSTEXPR_ ty& operator[](size_ty pos) noexcept
	{
		FLX_ASSERT_(pos < size_ && "flx/dynamic_array.hpp::dynamic_array::operator[]: position is out of bounds.");

		return data_[pos];
	}

	IMP_FLX_DARR_CONSTEXPR_ const ty& operator[](size_ty pos) const noexcept
	{
		FLX_ASSERT_(pos < size_ && "flx/dynamic_array.hpp::dynamic_array::operator[]: position is out of bounds.");

		return data_[pos];
	}

flx_private:
	/*IMP_FLX_DARR_CONSTEXPR_ void reallocate() noexcept
	{
		capacity_ *= GROWTH_RATE;
		if IMP_FLX_DARR_CONSTEXPR_ (PREALLOCATED_CAPACITY == 0)
		{
			if (capacity_ == 0)
			{
				capacity_ = 1;
			}
		}
		ty* new_data = static_cast<ty*>(::operator new(capacity_ * sizeof(ty)));

		for (size_ty i = 0; i < size_; i++)
		{
			::new (&new_data[i], true) ty(FLX_ move(data_[i]));
			if IMP_FLX_DARR_CONSTEXPR_ (FLX_ is_class<ty> && !FLX_ is_trivially_destructible<ty>)
			{
				data_[i].~ty();
			}
		}

		::operator delete(data_);
		data_ = new_data;
	}*/

	IMP_FLX_DARR_CONSTEXPR_ void reallocate(const size_ty new_capacity) noexcept
	{
		capacity_ = calculate_growth(new_capacity);

		FLX_ASSERT_(capacity_ > size_ && "flx/dynamic_array.hpp::dynamic_array::reallocate: new capacity is smaller than size.");

		ty* new_data{};

		try
		{
			new_data = static_cast<ty*>(::operator new(capacity_ * sizeof(ty)));
		}
		catch (...)
		{
			capacity_ = 0;
			size_ = 0;
			::operator delete(data_);
			data_ = nullptr;

			FLX_ASSERT_(false && "flx/dynamic_array.hpp::dynamic_array::reallocate: bad alloc.");

			FLX_ terminate("flx/dynamic_array.hpp::dynamic_array::reallocate: bad alloc.");

			return;
		}
		//ty* new_data = static_cast<ty*>(FLX_ allocate(capacity_ * sizeof(ty), FLX_ nothrow));

		for (size_ty i = 0; i < size_; i++)
		{
			//::new (&new_data[i], true) ty(FLX_ move(data_[i]));
			FLX_ move_construct_at(&new_data[i], FLX_ move(data_[i]));

			if IMP_FLX_DARR_CONSTEXPR_ (FLX_ is_class<ty> && !FLX_ is_trivially_destructible<ty>)
			{
				data_[i].~ty();
			}
		}

		::operator delete(data_);
		//FLX_ deallocate(data_);
		data_ = new_data;
	}

	// Allocates a chuck of [new_capacity]
	IMP_FLX_DARR_CONSTEXPR_ void allocate_raw_array(const size_ty new_capacity)
	{
		FLX_ASSERT_(new_capacity > size_ && "flx/dynamic_array.hpp::dynamic_array::allocate_raw_array: new capacity is smaller than size.");

		capacity_ = new_capacity;
		try
		{
			data_ = static_cast<ty*>(::operator new(capacity_ * sizeof(ty)));
		}
		catch (...)
		{
			data_ = nullptr;
			capacity_ = 0;
			size_ = 0;

			FLX_ASSERT_(false && "flx/dynamic_array.hpp::dynamic_array::allocate_raw_array: bad alloc.");
			FLX_ terminate("flx/dynamic_array.hpp::dynamic_array::allocate_raw_array: bad alloc.");
		}
		//data_ = static_cast<ty*>(FLX_ allocate(capacity_ * sizeof(ty)), FLX_ nothrow);
	}

	// Should be called with (capacity + 1)
	IMP_FLX_DARR_CONSTEXPR_ size_ty calculate_growth(const size_ty new_capacity) const noexcept
	{
		if (capacity_ > max_size() - (capacity_ >> 1))
		{
			return max_size();
		}

		const size_ty desired = capacity_ + (capacity_ >> 1);

		return desired > capacity_ ? desired : new_capacity;
	}
}; // dynamic_array

FLX_END_

#endif // IMP_FLX_DYNAMIC_ARRAY_HPP_