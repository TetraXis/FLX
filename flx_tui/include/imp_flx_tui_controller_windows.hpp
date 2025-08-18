#if defined(_WIN32) || defined(_WIN64)

#ifndef IMP_FLX_TUI_CONTROLLER_WINDOWS_HPP
#define IMP_FLX_TUI_CONTROLLER_WINDOWS_HPP

#include "flx_timer_windows.hpp"

#include "imp_flx_tui_controller.hpp"

#include <Windows.h>

#ifndef NDEBUG
#include <string>
#include <iostream>
#endif // NDEBUG

namespace flx
{
	namespace tui
	{
		struct tui_controller_windows : tui_controller_base
		{
		flx_public:
			void start() noexcept override;
			void process_input() noexcept override;

			void redraw_window(window* window_to_redraw, const vec2<u16>& top_left, const vec2<u16>& bottom_right) noexcept override;

			void clear_buffer() noexcept override;
			void update_buffer_size() noexcept override;
			void populate_buffer() noexcept override;
			void draw_buffer() noexcept override;

#ifndef NDEBUG
			HANDLE debug_console_process{};
			HANDLE debug_console_input{};
			HANDLE debug_console_output{};
			DWORD debug_prev_console_mode{};
			SMALL_RECT debug_write_region{};
#endif // NDEBUG

		//flx_protected:
			HANDLE console_input{};
			HANDLE console_output{};
			DWORD prev_console_mode{};
			SMALL_RECT write_region{ 0, 0, DEFAULT_SIZE_X, DEFAULT_SIZE_Y };
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