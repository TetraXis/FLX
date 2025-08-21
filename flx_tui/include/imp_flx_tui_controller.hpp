#ifndef IMP_FLX_TUI_CONTROLLER_HPP
#define IMP_FLX_TUI_CONTROLLER_HPP

#define FLX_TUI_DEFAULT_MAX_TPS 250

#ifndef FLX_TUI_MAX_TPS
#define FLX_TUI_MAX_TPS FLX_TUI_DEFAULT_MAX_TPS
#endif // !FLX_TUI_MAX_TPS

#define IMP_FLX_TUI_TICK_TARGET_MS (1'000.0 / FLX_TUI_MAX_TPS)
#define IMP_FLX_TUI_TICK_TARGET_US (1'000'000.0 / FLX_TUI_MAX_TPS)

#include "flx_vec.hpp"
#include "flx_unique_ptr.hpp"
#include "imp_flx_tui_base.hpp"
#include "imp_flx_tui_window.hpp"
#include "flx_dynamic_array.hpp"

namespace flx
{
	namespace tui
	{
		struct widget;
		struct window;

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
			constexpr static u16 DEFAULT_SIZE_X = 32;
			constexpr static u16 DEFAULT_SIZE_Y = 10;

			//friend widget;
			//friend window;

		//flx_protected:
			flx::dynamic_array<flx::unique_ptr<window>, u32> windows{}; // windows[0] is back layer
			vec2<u16> size{ DEFAULT_SIZE_X, DEFAULT_SIZE_Y };
			vec2<u16> buffer_size{ DEFAULT_SIZE_X, DEFAULT_SIZE_Y };
			u64 ticks = 0;

		flx_public:
			tui_controller_base() = default;
			~tui_controller_base() = default;

			void add_window(flx::unique_ptr<window>) noexcept;

			virtual void tick(u32 delta_milliseconds) noexcept; // u32 for x86-32 support
			virtual void redraw_window(window* window_to_redraw, const vec2<u16>& top_left, const vec2<u16>& bottom_right) noexcept = 0;

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