#if defined(_WIN32) || defined(_WIN64)

#ifndef FLX_TIMER_WINDOWS_HPP
#define FLX_TIMER_WINDOWS_HPP

#include "flx_types.hpp"

#include <Windows.h>

#ifndef NDEBUG
#include <cassert>
#else
#define assert(expr) ((void)0)
#endif // !NDEBUG

namespace flx
{
    struct timer
    {
    flx_private:
        LARGE_INTEGER m_start{};
        LARGE_INTEGER m_end{};
        LARGE_INTEGER m_frequency{};
        bool m_running = true;

    flx_public:
        timer();

        void start();
        void stop();

        u64 elapsed_microseconds();
        f64 elapsed_milliseconds();
        f64 elapsed_seconds();
    }; // timer
} // namespace flx

#endif // !FLX_TIMER_WINDOWS_HPP

#endif // Windows