#ifndef FLX_INC_CORE_ERROR_HPP
#define FLX_INC_CORE_ERROR_HPP

// This header defines error handling
// This header is useless. Constexpr trace is impossible and impractical.
// Runtime is arlready supplied by most IDEs
// This should be redone when C++26 Reflections are fully supported.

#error "This header should not be used."

#include "flx/core.hpp" // for types

namespace flx
{

	/* thread_local */ inline const c8* last_error = "NULL";
	// unable to thread_local, since constexpr breaks

#if defined(FLX_OPT_TRACE_DEPTH)
	constexpr szt TRACE_DEPTH = FLX_TRACE_DEPTH;
#else
	constexpr szt TRACE_DEPTH = 32;
#endif

	// it is disallowed to modify global variables in constexpr contexes. Check this functionality.
	// trace is used for tracing calls (f.e. in case of terminate)
	thread_local inline const c8* trace[TRACE_DEPTH]{};

	namespace imp
	{
		/* thread_local */ inline szt trace_pos = 0; // position of last trace entry
		// unable to thread_local, since constexpr breaks

		// to shift all contexts to one left
		constexpr void trace_shift() noexcept
		{
			for (szt i = 0; i < TRACE_DEPTH - 1; i++)
			{
				trace[i] = trace[i + 1];
			}
		}

		constexpr void trace_push(const c8* msg) noexcept
		{
			if (trace_pos < TRACE_DEPTH)
			{
				trace[trace_pos] = msg;
				++trace_pos;
			}
			else
			{
				trace_shift();
				trace[TRACE_DEPTH - 1] = msg;
			}
		}

		constexpr void trace_pop() noexcept
		{
			if (trace_pos > 0)
			{
				--trace_pos;
			}
		}

		struct trace_context_guard
		{
			constexpr explicit trace_context_guard(const c8* msg) noexcept
			{
				trace_push(msg);
			}

			constexpr ~trace_context_guard() noexcept
			{
				trace_pop();
			}

			trace_context_guard(const trace_context_guard&) = delete;
			trace_context_guard(trace_context_guard&&) = delete;
			trace_context_guard& operator = (const trace_context_guard&) = delete;
			trace_context_guard& operator = (trace_context_guard&&) = delete;
		};
	}
}

#define IMP_CONCAT_IMP(a, b) a##b
#define IMP_CONCAT(a, b) IMP_CONCAT_IMP(a, b)
#define FLX_UNIQUE_NAME(name) IMP_CONCAT(name, __COUNTER__) // replace with __LINE__ if breaks

#if defined(FLX_CFG_USE_TRACE)
	#define FLX_TRACE_CONTEXT_ADD(msg)	[[maybe_unused]] ::flx::imp::trace_context_guard FLX_UNIQUE_NAME(tcg_){msg}
	#define FLX_TRACE_PUSH(msg)			::flx::imp::trace_push(msg)
	#define FLX_TRACE_POP()				::flx::imp::trace_pop()
#else // !FLX_CFG_USE_TRACE
	#define FLX_TRACE_CONTEXT_ADD(msg)	((void)0)
	#define FLX_TRACE_PUSH(msg)			((void)0)
	#define FLX_TRACE_POP()				((void)0)
#endif // FLX_CFG_USE_TRACE

#endif // !defined(FLX_INC_CORE_ERROR_HPP)