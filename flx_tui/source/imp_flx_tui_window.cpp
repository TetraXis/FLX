#include "imp_flx_tui_window.hpp"

#include "flx_utility.hpp"

flx::tui::window::window() : widget(widget_type::window)
{
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
	set_size(new_size);
}

void flx::tui::window::set_size(const vec2<u16>& new_size) noexcept
{
	widget::set_size(new_size);
	update_buffer_size();
}

void flx::tui::window::update_buffer_size() noexcept
{
	if (size.x * size.y > buffer_size.x * buffer_size.y || size.x * size.y < buffer_size.x * buffer_size.y * MAX_UNUSED_BUFFER)
	{
		buffer_char.reset( new c16[size.x * size.y] );
		buffer_color.reset( new u8[size.x * size.y] );
	}
}

void flx::tui::window::redraw_buffer() noexcept
{
	draw_border();
}

void flx::tui::window::draw_border() noexcept
{
	using namespace tui::characters;
	using namespace tui::colors;
	//using tui::characters::box_drawing;

	u16 x{}, y{}, i{};

	// top
	buffer_char[xy_to_idx<u16>(0, 0, buffer_size.x)] = box_drawing[R | D | DH | DV];
	buffer_char[xy_to_idx<u16>(1, 0, buffer_size.x)] = '[';
	
	if (buffer_size.x >= MIN_WIDTH_FOR_BUTTONS)
	{
		for (i = 0, x = 2; x < buffer_size.x - 11 && i < NAME_SIZE && name[i] != '\0'; x++, i++)
		{
			buffer_char[xy_to_idx<u16>(x, 0, buffer_size.x)] = name[i];
		}

		buffer_char[xy_to_idx<u16>(x, 0, buffer_size.x)] = ']';

		for (x++; x < buffer_size.x - 10; x++)
		{
			buffer_char[xy_to_idx<u16>(x, 0, buffer_size.x)] = box_drawing[L | R | DH | DV];
		}

		buffer_char[xy_to_idx<u16>(buffer_size.x - 10, 0, buffer_size.x)] = '[';
		buffer_char[xy_to_idx<u16>(buffer_size.x - 9,  0, buffer_size.x)] = '_';
		buffer_char[xy_to_idx<u16>(buffer_size.x - 8,  0, buffer_size.x)] = ']';
		buffer_char[xy_to_idx<u16>(buffer_size.x - 7,  0, buffer_size.x)] = '[';
		buffer_char[xy_to_idx<u16>(buffer_size.x - 6,  0, buffer_size.x)] = 'o';
		buffer_char[xy_to_idx<u16>(buffer_size.x - 5,  0, buffer_size.x)] = ']';
		buffer_char[xy_to_idx<u16>(buffer_size.x - 4,  0, buffer_size.x)] = '[';
		buffer_char[xy_to_idx<u16>(buffer_size.x - 3,  0, buffer_size.x)] = 'X';
		buffer_char[xy_to_idx<u16>(buffer_size.x - 2,  0, buffer_size.x)] = ']';
	}
	else
	{
		for (i = 0, x = 2; x < buffer_size.x - 2 && i < NAME_SIZE && name[i] != '\0'; x++, i++)
		{
			buffer_char[xy_to_idx<u16>(x, 0, buffer_size.x)] = name[i];
		}

		buffer_char[xy_to_idx<u16>(x, 0, buffer_size.x)] = ']';
		if (i < NAME_SIZE && name[i] != '\0' && x > 2)
		{
			buffer_char[xy_to_idx<u16>(x - 1, 0, buffer_size.x)] = '.';
		}

		for (x++; x < buffer_size.x - 1; x++)
		{
			buffer_char[xy_to_idx<u16>(x, 0, buffer_size.x)] = box_drawing[L | R | DH | DV];
		}
	}

	buffer_char[xy_to_idx<u16>(buffer_size.x - 1, 0, buffer_size.x)]	= box_drawing[L | D | DH | DV];

	// sides
	for (y = 1; y < buffer_size.y - 1; y++)
	{
		buffer_char[xy_to_idx<u16>(0, y, buffer_size.x)] = box_drawing[U | D | DH | DV];
		buffer_char[xy_to_idx<u16>(buffer_size.x - 1, y, buffer_size.x)] = box_drawing[U | D | DH | DV];
	}

	// bottom
	y = buffer_size.y - 1;

	buffer_char[xy_to_idx<u16>(0, y, buffer_size.x)] = box_drawing[R | U | DH | DV];

	for (x = 1; x < buffer_size.x - 1; x++)
	{
		buffer_char[xy_to_idx<u16>(x, y, buffer_size.x)] = box_drawing[L | R | DH | DV];
	}

	buffer_char[xy_to_idx<u16>(buffer_size.x - 1, y, buffer_size.x)] = box_drawing[L | U | DH | DV];
}

//#ifndef NDEBUG
//
//void flx::tui::window::print() const
//{
//	std::stringstream ss{};
//	for (u16 y = 0; y < size.y; y++)
//	{
//		for (u16 x = 0; x < size.x; x++)
//		{
//			ss << buffer.get()[y * size.x + x];
//		}
//		ss << "\n";
//	}
//	std::cout << ss.str() << '\n';
//}
//
//void flx::tui::window::populate_buffer_debug() noexcept
//{
//	for (u16 y = 0; y < buffer_size.y; y++)
//	{
//		for (u16 x = 0; x < buffer_size.x; x++)
//		{
//			buffer[xy_to_idx<u16>(x, y, buffer_size.x)] = 'A' + i8(y);
//		}
//	}
//}
//
//#endif // NDEBUG
