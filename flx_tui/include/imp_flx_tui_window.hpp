#ifndef IMP_FLX_TUI_WINDOW_HPP
#define IMP_FLX_TUI_WINDOW_HPP

#include "imp_flx_tui_base.hpp"
#include "imp_flx_tui_encoding.hpp"
#include "flx_unique_ptr.hpp"
#include "flx_dynamic_array.hpp"

#ifndef NDEBUG
#include <cassert>
#include <iostream>
#include <sstream>
#else
#define assert(expr) ((void)0)
#endif // !NDEBUG

namespace flx
{
	namespace tui
	{
		struct window : widget
		{
			// buffer will shrink only when unused space exceeds this ratio.
			static constexpr f32 MAX_UNUSED_BUFFER = 0.6f;
			// prefer keeping this % 4 == 0 to preserve good struct padding
			static constexpr u16 NAME_SIZE = 16;
			// if window is slimmer than this, buttons are not shown
			static constexpr u16 MIN_WIDTH_FOR_BUTTONS = 12;

			c8 name[NAME_SIZE]{};
			unique_ptr<c16[]> buffer_char{ new c16[MIN_SIZE.x * MIN_SIZE.y] };
			unique_ptr<u8[]> buffer_color{ new u8[MIN_SIZE.x * MIN_SIZE.y] };
			vec2<u16> buffer_size{ MIN_SIZE.x, MIN_SIZE.y };
			vec2<i16> viewport_pos{};

			window();
			window(const char*, const vec2<u16>& = {7, 2});

			void set_size(const vec2<u16>&) noexcept override;

			void update_buffer_size() noexcept;

			void redraw_buffer() noexcept;
			void draw_border() noexcept;

//#ifndef NDEBUG
//		flx_public:
//			void print() const;
//			void populate_buffer_debug() noexcept;
//#endif // NDEBUG
		}; // window
	} // namespace tui
} // namespace flx

#endif // IMP_FLX_TUI_WINDOW_HPP