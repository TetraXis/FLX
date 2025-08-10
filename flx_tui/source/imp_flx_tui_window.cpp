#include "imp_flx_tui_window.hpp"

#include "flx_utility.hpp"

flx::tui::window::window() : widget(widget_type::window)
{
	min_size = { 7, 2 };
	set_size(min_size);
}

flx::tui::window::window(const char* new_name, const vec2<u16>& new_size) : widget(widget_type::window)
{
	for (u16 i = 0; i < NAME_SIZE; i++)
	{
		if (new_name[i] == '\0')
		{
			name[i] = new_name[i];
			break;
		}
		name[i] = new_name[i];
	}
	min_size = { 7, 2 };
	set_size(new_size);
}

flx::tui::window::~window()
{
}

void flx::tui::window::set_size(const vec2<u16>& new_size)
{
	widget::set_size(new_size);
	update_buffer_size();
	populate_buffer();
}


void flx::tui::window::set_name(const i8* new_name)
{
	for (u8 i = 0; i < NAME_SIZE && name[i] != '\0'; i++)
	{
		name[i] = new_name[i];
	}
}

void flx::tui::window::add_widget(flx::unique_ptr<widget> new_widget)
{
	new_widget->parent.widget_ptr = this;
	widgets.emplace_back(new_widget.release());
}

void flx::tui::window::remove_widget(flx::unique_ptr<widget>* widget_to_remove)
{
	for (u32 elem = 0; elem < widgets.size(); elem++)
	{
		if (&widgets[elem] == widget_to_remove)
		{
			widgets[elem].reset(widgets[widgets.size() - 1].release());
			widgets.pop_back();
		}
	}
}

void flx::tui::window::remove_widget(u32 remove_at)
{
	widgets[remove_at].reset(widgets[widgets.size() - 1].release());
	widgets.pop_back();
}

void flx::tui::window::update_buffer_size()
{
	if 
	(
		size.x * size.y > buffer_size.x * buffer_size.y
		||
		size.x * size.y < buffer_size.x * buffer_size.y/* * MAX_UNUSED_BUFFER*/
	)
	{
		buffer.reset(new i8[size.x * size.y]);
		buffer_size.x = size.x;
		buffer_size.y = size.y;
	}
}

void flx::tui::window::populate_buffer()
{
	clear_buffer();
	//populate_buffer_debug();
	draw_border();
	return;
}

void flx::tui::window::draw_border()
{
	using namespace tui::characters;
	using namespace tui::colors;
	//using tui::characters::box_drawing;

	u16 x{}, y{}, i{};

	// top
	buffer[xy_to_idx<u16>(0, 0, buffer_size.x)] = box_drawing[R | D | DH | DV];
	buffer[xy_to_idx<u16>(1, 0, buffer_size.x)] = '[';
	
	if (buffer_size.x >= MIN_WIDTH_FOR_BUTTONS)
	{
		for (i = 0, x = 2; x < buffer_size.x - 11 && i < NAME_SIZE && name[i] != '\0'; x++, i++)
		{
			buffer[xy_to_idx<u16>(x, 0, buffer_size.x)] = name[i];
		}

		buffer[xy_to_idx<u16>(x, 0, buffer_size.x)] = ']';

		for (x++; x < buffer_size.x - 10; x++)
		{
			buffer[xy_to_idx<u16>(x, 0, buffer_size.x)] = box_drawing[L | R | DH];
		}

		buffer[xy_to_idx<u16>(buffer_size.x - 10, 0, buffer_size.x)] = '[';
		buffer[xy_to_idx<u16>(buffer_size.x - 9,  0, buffer_size.x)] = '_';
		buffer[xy_to_idx<u16>(buffer_size.x - 8,  0, buffer_size.x)] = ']';
		buffer[xy_to_idx<u16>(buffer_size.x - 7,  0, buffer_size.x)] = '[';
		buffer[xy_to_idx<u16>(buffer_size.x - 6,  0, buffer_size.x)] = 'o';
		buffer[xy_to_idx<u16>(buffer_size.x - 5,  0, buffer_size.x)] = ']';
		buffer[xy_to_idx<u16>(buffer_size.x - 4,  0, buffer_size.x)] = '[';
		buffer[xy_to_idx<u16>(buffer_size.x - 3,  0, buffer_size.x)] = 'X';
		buffer[xy_to_idx<u16>(buffer_size.x - 2,  0, buffer_size.x)] = ']';
	}
	else
	{
		for (i = 0, x = 2; x < buffer_size.x - 2 && i < NAME_SIZE && name[i] != '\0'; x++, i++)
		{
			buffer[xy_to_idx<u16>(x, 0, buffer_size.x)] = name[i];
		}

		buffer[xy_to_idx<u16>(x, 0, buffer_size.x)] = ']';
		if (i < NAME_SIZE && name[i] != '\0' && x > 2)
		{
			buffer[xy_to_idx<u16>(x - 1, 0, buffer_size.x)] = '.';
		}

		for (x++; x < buffer_size.x - 1; x++)
		{
			buffer[xy_to_idx<u16>(x, 0, buffer_size.x)] = box_drawing[L | R | DH];
		}
	}

	buffer[xy_to_idx<u16>(buffer_size.x - 1, 0, buffer_size.x)]	= box_drawing[L | D | DH | DV];

	// sides
	for (y = 1; y < buffer_size.y - 1; y++)
	{
		buffer[xy_to_idx<u16>(0, y, buffer_size.x)] = box_drawing[U | D | DV];
		buffer[xy_to_idx<u16>(buffer_size.x - 1, y, buffer_size.x)] = box_drawing[U | D | DV];
	}

	// bottom
	y = buffer_size.y - 1;

	buffer[xy_to_idx<u16>(0, y, buffer_size.x)] = box_drawing[R | U | DH | DV];

	for (x = 1; x < buffer_size.x - 1; x++)
	{
		buffer[xy_to_idx<u16>(x, y, buffer_size.x)] = box_drawing[L | R | DH];
	}

	buffer[xy_to_idx<u16>(buffer_size.x - 1, y, buffer_size.x)] = box_drawing[L | U | DH | DV];
}

#ifndef NDEBUG

void flx::tui::window::print() const
{
	std::stringstream ss{};
	for (u16 y = 0; y < size.y; y++)
	{
		for (u16 x = 0; x < size.x; x++)
		{
			ss << buffer.get()[y * size.x + x];
		}
		ss << "\n";
	}
	std::cout << ss.str() << '\n';
}

void flx::tui::window::populate_buffer_debug() noexcept
{
	for (u16 y = 0; y < buffer_size.y; y++)
	{
		for (u16 x = 0; x < buffer_size.x; x++)
		{
			buffer[xy_to_idx<u16>(x, y, buffer_size.x)] = 'A' + i8(y);
		}
	}
}

#endif // NDEBUG
