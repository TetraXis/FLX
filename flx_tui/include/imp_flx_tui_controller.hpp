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
			constexpr static u16 DEFAULT_SIZE_X = 1;
			constexpr static u16 DEFAULT_SIZE_Y = 1;

		flx_protected:
			flx::dynamic_array<flx::unique_ptr<widget>, u32> widgets{}; // widgets[0] is back layer
			vec2<u16> size{ DEFAULT_SIZE_X, DEFAULT_SIZE_Y };
			vec2<u16> buffer_size{ DEFAULT_SIZE_X, DEFAULT_SIZE_Y };

		flx_public:
			tui_controller_base() = default;
			~tui_controller_base() = default;

			void add_widget(flx::unique_ptr<widget>) noexcept;

			virtual void start() noexcept = 0;
			virtual void process_input() noexcept = 0;

			virtual void clear_buffer() noexcept = 0;
			virtual void update_buffer_size() noexcept = 0;
			virtual void populate_buffer() noexcept = 0;
			virtual void draw_buffer() noexcept = 0;
		}; // tui_controller
	} // namespace tui
} // namespace flx

#endif // IMP_FLX_TUI_CONTROLLER_HPP