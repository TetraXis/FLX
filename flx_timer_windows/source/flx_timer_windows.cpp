#if defined(_WIN32) || defined(_WIN64)

#include "flx_timer_windows.hpp"

flx::timer::timer()
{
    QueryPerformanceFrequency(&m_frequency);
    QueryPerformanceCounter(&m_start);
}

void flx::timer::start()
{
    QueryPerformanceCounter(&m_start);
    m_running = true;
}

void flx::timer::stop()
{
    QueryPerformanceCounter(&m_end);
    m_running = false;
}

flx::u64 flx::timer::elapsed_microseconds()
{
    if (m_running)
    {
        QueryPerformanceCounter(&m_end);
    }

    return (m_end.QuadPart - m_start.QuadPart) * 1'000'000 / m_frequency.QuadPart;
}

flx::f64 flx::timer::elapsed_milliseconds()
{
    if (m_running)
    {
        QueryPerformanceCounter(&m_end);
    }

    return f64(m_end.QuadPart - m_start.QuadPart) * 1'000.0 / m_frequency.QuadPart;
}

flx::f64 flx::timer::elapsed_seconds()
{
    if (m_running)
    {
        QueryPerformanceCounter(&m_end);
    }

    return f64(m_end.QuadPart - m_start.QuadPart) / m_frequency.QuadPart;
}

#endif // Windows
