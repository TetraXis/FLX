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

		flx_public:
			i8 name[NAME_SIZE]{};
		flx_protected:
			dynamic_array< unique_ptr<widget>, u32 > widgets{};
			// buffer that is cut by window size
			unique_ptr<i8[]> viewport{};
			vec2<u16> buffer_size{};
			vec2<u16> view_size{};
			vec2<u16> view_offset{};
			vec2<u16> PADDING{};

		flx_public:
			window();
			window(const char*, const vec2<u16>& = {7, 2});
			virtual ~window();

			virtual void set_size(const vec2<u16>&) override;
			void set_name(const i8*);

			virtual void add_widget(flx::unique_ptr<widget>);
			virtual void remove_widget(flx::unique_ptr<widget>*);
			virtual void remove_widget(u32);

			virtual void update_buffer_size();

			virtual void populate_buffer() override;

		flx_protected:
			virtual void draw_border();

#ifndef NDEBUG
		flx_public:
			void print() const;
			void populate_buffer_debug() noexcept;
#endif // NDEBUG
		}; // window
	} // namespace tui
} // namespace flx

#endif // IMP_FLX_TUI_WINDOW_HPP