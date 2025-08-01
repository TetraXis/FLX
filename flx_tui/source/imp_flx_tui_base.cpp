#include "imp_flx_tui_base.hpp"
#include "flx_utility.hpp"

flx::tui::widget::widget(widget_type new_type) : type(new_type)
{
}

flx::tui::widget::~widget()
{
}

flx::vec2<flx::u16> flx::tui::widget::get_size() const
{
	return size;
}

void flx::tui::widget::set_size(const vec2<u16>& new_size)
{
	size =
	{
		flx::max(min_size.x, new_size.x),
		flx::max(min_size.y, new_size.y)
	};
	return;
}

void flx::tui::widget::hover_begin()
{
}

void flx::tui::widget::hover_end()
{
}

void flx::tui::widget::click_begin()
{
}

void flx::tui::widget::click_end()
{
}

void flx::tui::widget::clear_buffer() noexcept
{
	for (u16 y = 0; y < buffer_size.y; y++)
	{
		for (u16 x = 0; x < buffer_size.x; x++)
		{
			buffer[xy_to_idx<u16>(x, y, buffer_size.x)] = ' ';
		}
	}
}

void flx::tui::widget::populate_buffer()
{
}