#include "flx_utility.hpp"

const flx::i8* flx::last_error = nullptr;

void (*flx::on_terminate) () noexcept = []() noexcept {};

void* flx::allocate(const flx::imp::size_type size)
{
	return ::operator new(size);
}

void* flx::allocate(const flx::imp::size_type size, flx::imp::nothrow_t) noexcept
{
	try
	{
		return ::operator new(size);
	}
	catch (...)
	{
		return nullptr;
	}
}

void flx::deallocate(void* ptr) noexcept
{
	::operator delete(ptr);
}

void flx::terminate(const flx::c8* const error_msg) noexcept
{
	last_error = error_msg;

	on_terminate();

	// Make program crash
	*(int*)(nullptr) = 0;

	while (true)
	{
		*(int*)(nullptr) = 0;
	}
}
