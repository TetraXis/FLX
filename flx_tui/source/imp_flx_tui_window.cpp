#include "imp_flx_tui_window.hpp"

flx::tui::window::window() : widget(widget_type::window)
{
	min_size = { 7, 2 };
	set_size(min_size);
}

inline constexpr flx::u16 flx::tui::window::XY_TO_IDX(u16 x, u16 y, u16 width)
{
	return x + y * width;
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
	new_widget->parent = this;
	widgets.emplace_back(new_widget.release());
}

void flx::tui::window::remove_widget(flx::unique_ptr<widget>* widget_to_remove)
{
	for (u64 elem = 0; elem < widgets.size(); elem++)
	{
		if (&widgets[elem] == widget_to_remove)
		{
			widgets[elem].reset(widgets[widgets.size() - 1].release());
			widgets.pop_back();
		}
	}
}

void flx::tui::window::remove_widget(u64 remove_at)
{
	widgets[remove_at].reset(widgets[widgets.size() - 1].release());
	widgets.pop_back();
}

void flx::tui::window::update_buffer_size()
{
	if 
	(
		size.x * size.y > view_size.x * view_size.y
		||
		size.x * size.y < view_size.x * view_size.y * MAX_UNUSED_BUFFER
	)
	{
		viewport.reset(new i8[size.x * size.y]);
		view_size.x = size.x;
		view_size.y = size.y;
	}
}

void flx::tui::window::populate_buffer()
{
	draw_border();
	return;
	//  fix it
	//memset(viewport.get(), ' ', view_size.x * view_size.y);

	/*for (u16 i = 0; i < size.x * size.y; i++)
	{
		buffer[i] = '0' + i / size.x;
	}
	return;*/

	/*for (u16 i = 2; i < size.x - 1; i++)
	{
		viewport[i] = symbols::box_double_horizontal[symbols::HORIZONTAL];
	}

	for (u16 i = 0; ; i++)
	{
		if (i >= NAME_SIZE || name[i] == '\0' || i + 2 >= size.x - 2)
		{
			viewport[i + 2] = ' ';
			break;
		}
		viewport[i + 2] = name[i];
	}

	viewport[0] = symbols::box_double_horizontal[symbols::DOWN_RIGHT];
	viewport[size.x - 1] = symbols::box_double_horizontal[symbols::DOWN_LEFT];

	for (u16 y = 1; y < size.y - 1; y++)
	{
		viewport[size.x * y] = symbols::box_lite[symbols::VERTICAL];
		viewport[size.x * y + size.x - 1] = symbols::box_lite[symbols::VERTICAL];
	}

	for (u16 i = 1; i < size.x - 1; i++)
	{
		viewport[size.x * (size.y - 1) + i] = symbols::box_lite[symbols::HORIZONTAL];
	}

	viewport[size.x * (size.y - 1)] = symbols::box_lite[symbols::UP_RIGHT];
	viewport[size.x * size.y - 1] = symbols::box_lite[symbols::UP_LEFT];*/
}

void flx::tui::window::draw_border()
{
	using enum tui::symbols::box_flags;
	using tui::symbols::box_drawing;

	u16 x{}, y{}, i{};

	// top
	viewport[XY_TO_IDX(0, 0, view_size.x)] = box_drawing[R | D | DH];
	viewport[XY_TO_IDX(1, 0, view_size.x)] = '[';
	
	if (view_size.x >= MIN_WIDTH_FOR_BUTTONS)
	{
		for (i = 0, x = 3; x < view_size.x - 11 && i < NAME_SIZE && name[i] != '\0'; x++, i++)
		{
			viewport[XY_TO_IDX(x, 0, view_size.x)] = name[i];
		}

		viewport[XY_TO_IDX(x, 0, view_size.x)] = ']';

		for (x++; x < view_size.x - 11; x++)
		{
			viewport[XY_TO_IDX(x, 0, view_size.x)] = box_drawing[L | R | DH];
		}

		viewport[XY_TO_IDX(view_size.x - 10, 0, view_size.x)] = '[';
		viewport[XY_TO_IDX(view_size.x - 9,  0, view_size.x)] = '_';
		viewport[XY_TO_IDX(view_size.x - 8,  0, view_size.x)] = ']';
		viewport[XY_TO_IDX(view_size.x - 7,  0, view_size.x)] = '[';
		viewport[XY_TO_IDX(view_size.x - 6,  0, view_size.x)] = 'o';
		viewport[XY_TO_IDX(view_size.x - 5,  0, view_size.x)] = ']';
		viewport[XY_TO_IDX(view_size.x - 4,  0, view_size.x)] = '[';
		viewport[XY_TO_IDX(view_size.x - 3,  0, view_size.x)] = 'X';
		viewport[XY_TO_IDX(view_size.x - 2,  0, view_size.x)] = ']';
	}
	else
	{
		for (i = 0, x = 3; x < view_size.x - 1 && i < NAME_SIZE && name[i] != '\0'; x++, i++)
		{
			viewport[XY_TO_IDX(x, 0, view_size.x)] = name[i];
		}

		viewport[XY_TO_IDX(x, 0, view_size.x)] = ']';

		for (x++; x < view_size.x - 1; x++)
		{
			viewport[XY_TO_IDX(x, 0, view_size.x)] = box_drawing[L | R | DH];
		}
	}

	viewport[XY_TO_IDX(view_size.x - 1, 0, view_size.x)]	= box_drawing[L | D | DH];
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
#endif // NDEBUG
