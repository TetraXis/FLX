#ifndef IMP_FLX_TUI_CONTROLLER_HPP
#define IMP_FLX_TUI_CONTROLLER_HPP

//#include "imp_flx_tui_encoding.hpp"
#include "flx_vec.hpp"
#include "imp_flx_tui_base.hpp"
#include "flx_dynamic_array.hpp"

namespace flx
{
	namespace tui
	{
		// handles i/o, base for platform specific controllers
		struct tui_controller_base
		{
		flx_protected:
			dynamic_array<widget, u32> widgets{};

		flx_public:
			tui_controller_base() = default;
			~tui_controller_base() = default;

			virtual void start() noexcept = 0;
		}; // tui_controller

		struct tui_controller_windows;
		struct tui_controller_linux;

#if defined(_WIN32) || defined(_WIN64) // Windows
		using tui_controller = tui_controller_windows;
#elif defined(__linux__) // Linux
		using tui_controller = tui_controller_linux;
#endif

	} // namespace tui
} // namespace flx

#endif // IMP_FLX_TUI_CONTROLLER_HPP