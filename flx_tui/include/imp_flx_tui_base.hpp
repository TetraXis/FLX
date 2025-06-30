#pragma once

#include "flx_types.hpp"
#include "flx_vec.hpp"

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
		};

		struct window;

		struct widget
		{
			friend window; // this drives me nuts

		flx_protected:
			widget* parent = nullptr;
		flx_public:
			vec2<i16> coord{};
			vec2<u16> min_size{};
		flx_protected:
			vec2<u16> size{};
		flx_public:
			u16 id{};
			const widget_type type = widget_type::none;
			/// <summary>
			/// For possible future uses
			/// </summary>
			u8 flags{};

		flx_protected:
			widget(widget_type);

		flx_public:
			widget() = default;
			virtual ~widget();

			vec2<u16>	get_size() const;
			virtual	void set_size(const vec2<u16>&);

			virtual void hover_begin();
			virtual void hover_end();
			virtual void click_begin();
			virtual void click_end();

			/// <summary>
			/// Fills the buffer with chars
			/// </summary>
			virtual void populate_buffer();
		};
	}
}