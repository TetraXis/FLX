#ifndef IMP_FLX_TUI_BASE_HPP
#define IMP_FLX_TUI_BASE_HPP

#include "flx_types.hpp"
#include "flx_vec.hpp"
#include "flx_unique_ptr.hpp"
#include "flx_dynamic_array.hpp"
#include "flx_utility.hpp"

#ifndef NDEBUG
#include <cassert>
#else
#define assert(expr) ((void)0)
#endif // !NDEBUG

namespace flx
{
	namespace tui
	{
		enum struct widget_type : u8
		{
			none,			// Not defined primitive type
			window,			// Can be moved or changed size by user
			textview,		// Read-only text view
			button,
			display,		// handles io and all widgets
			custom			// Custom type
		}; // widget_type

		/// When constructed by default:
		/// automatically assigns 'val' to next ''free'' id
		struct id_t
		{
			static inline u32 last_id = 0;

			u32 val;

			id_t() noexcept;
			explicit id_t(u32) noexcept;
			explicit operator u32() noexcept
			{
				return val;
			}

			bool operator== (const id_t&) const noexcept;
		};

		struct window;
		struct tui_controller_base;

		struct widget
		{
			static constexpr vec2<u16> MIN_SIZE = { 5,2 };

			union parent_union
			{
				widget* widget;
				tui_controller_base* controller;
			} parent{};
			dynamic_array<unique_ptr<widget>, u32> widgets{};
			/// Actions can be used for anything
			/// 
			/// 'argc' - amount of arguments
			/// 'argv' - arguments
			dynamic_array<bool (*) (widget*, u64 argc, void* argv[]), u32> actions;

			vec2<i16> pos{};
			vec2<u16> size = MIN_SIZE;
			id_t id{};
			u16 flags{};
			const widget_type type = widget_type::none;
			//u8 PADDING; // unused space 

			widget(widget_type = widget_type::none) noexcept;

			virtual void set_size(const vec2<u16>&) noexcept;

			void add_widget(unique_ptr<widget>) noexcept;
			unique_ptr<widget> remove_widget(id_t removed_id) noexcept;
			unique_ptr<widget> remove_widget(u32 removed_idx) noexcept;

			/// <summary>
			/// Redraws a given widget. This call should propagate to all the parents.
			/// </summary>
			/// <param name="widget_to_redraw"> - Original widget caller</param>
			/// <param name="top_left"> - Top left corner of dirty rectangle</param>
			/// <param name="bottom_right"> - Bottom right corner of dirty rectangle</param>
			virtual void redraw_widget(widget* widget_to_redraw, const vec2<u16>& top_left, const vec2<u16>& bottom_right) noexcept;
		}; // widget
	} // namespace tui
} // namespace flx

#endif // !IMP_FLX_TUI_BASE_HPP