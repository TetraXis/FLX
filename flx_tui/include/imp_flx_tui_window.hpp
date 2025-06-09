#pragma once

#include "imp_flx_tui_base.hpp"
#include "imp_flx_tui_encoding.hpp"
#include "flx_unique_ptr.hpp"

#include <vector>

#ifdef _DEBUG
#include <iostream>
#include <sstream>
#endif // _DEBUG

namespace flx
{
	namespace tui
	{
		struct window : widget
		{
			/// <summary>
			/// Buffer will shrink only when unused space exceeds this ratio.
			/// </summary>
			static constexpr f32 MAX_UNUSED_BUFFER = 0.6f;
			static constexpr u16 NAME_SIZE = 16;

		flx_public:
			i8 name[NAME_SIZE]{};
		flx_protected:
			std::vector< flx::unique_ptr<widget> > widgets{};
			// buffer that is cut by window size
			unique_ptr<i8[]> buffer{};
			// buffer that contains all content inside
			unique_ptr<i8[]> content_buffer{};
			vec2<u16> content_buffer_size{};
			vec2<u16> buffer_size{};
			vec2<u16> buffer_shift{};
			vec2<u16> PADDING{};

		flx_public:
			window();
			window(const char*, const vec2<u16>& = {7, 2});
			virtual ~window();

			virtual void set_size(const vec2<u16>&) override;

			virtual void add_widget(flx::unique_ptr<widget>&);
			virtual void remove_widget(flx::unique_ptr<widget>*);
			virtual void remove_widget(u64);

			virtual void update_buffer_size();

			virtual void populate_buffer() override;

#ifdef _DEBUG
			void print() const;
#endif // _DEBUG
		};
	}
}