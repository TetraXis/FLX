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
			void process_input() noexcept override;

			void clear_buffer() noexcept override;
			void update_buffer_size() noexcept override;
			void populate_buffer() noexcept override;
			void draw_buffer() noexcept override;

		flx_protected:
			HANDLE console_input{};
			HANDLE console_output{};
			DWORD prev_console_mode{};
			SMALL_RECT write_region{};
			flx::unique_ptr<CHAR_INFO[]> buffer{ new CHAR_INFO[DEFAULT_SIZE_X * DEFAULT_SIZE_Y] };

#ifndef NDEBUG
		flx_public:
			void populate_buffer_debug() noexcept;
#endif
		};
	} // tui
} // flx

#endif // IMP_FLX_TUI_CONTROLLER_WINDOWS_HPP

#endif //s Windows