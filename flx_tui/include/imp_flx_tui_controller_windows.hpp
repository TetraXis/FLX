#if defined(_WIN32) || defined(_WIN64)

#ifndef IMP_FLX_TUI_CONTROLLER_WINDOWS_HPP
#define IMP_FLX_TUI_CONTROLLER_WINDOWS_HPP

#include "imp_flx_tui_controller.hpp"

#include <Windows.h>

namespace flx
{
	namespace tui
	{
		struct tui_controller_windows : tui_controller_base
		{
		flx_public:
			void start() noexcept override;

		flx_protected:
			HANDLE console_input;
			HANDLE console_output;
			DWORD prev_console_mode;
		};
	} // tui
} // flx

#endif // IMP_FLX_TUI_CONTROLLER_WINDOWS_HPP

#endif //s Windows