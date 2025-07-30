#ifndef IMP_FLX_TUI_CONTROLLER_HPP
#define IMP_FLX_TUI_CONTROLLER_HPP

#include "flx_vec.hpp"
#include "flx_unique_ptr.hpp"
#include "imp_flx_tui_base.hpp"
#include "flx_dynamic_array.hpp"

namespace flx
{
	namespace tui
	{
		struct tui_controller_windows;
		struct tui_controller_linux;

#if defined(_WIN32) || defined(_WIN64) // Windows
		using tui_controller = tui_controller_windows;
#elif defined(__linux__) // Linux
		using tui_controller = tui_controller_linux;
#endif

		// handles i/o, base for platform specific controllers
		struct tui_controller_base
		{
		flx_protected:
			flx::dynamic_array<flx::unique_ptr<widget>, u32> widgets{};

		flx_public:
			tui_controller_base() = default;
			~tui_controller_base() = default;

			virtual void start() noexcept = 0;
		}; // tui_controller
	} // namespace tui
} // namespace flx

#endif // IMP_FLX_TUI_CONTROLLER_HPP