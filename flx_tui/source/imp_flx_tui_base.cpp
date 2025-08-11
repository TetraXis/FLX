#include "imp_flx_tui_base.hpp"
#include "flx_utility.hpp"


//inline flx::u32 flx::tui::id_t::last_id = 0;

//flx::tui::widget::widget(widget_type new_type) : type(new_type)
//{
//}
//
//flx::tui::widget::~widget()
//{
//}
//
//flx::vec2<flx::u16> flx::tui::widget::get_size() const
//{
//	return size;
//}
//
//void flx::tui::widget::update() noexcept
//{
//	update_func(this);
//	for (const auto& widget_uptr : widgets)
//	{
//		widget_uptr->update();
//	}
//}
//
//void flx::tui::widget::set_size(const vec2<u16>& new_size)
//{
//	size =
//	{
//		flx::max(min_size.x, new_size.x),
//		flx::max(min_size.y, new_size.y)
//	};
//	return;
//}
//
//void flx::tui::widget::hover_begin()
//{
//}
//
//void flx::tui::widget::hover_end()
//{
//}
//
//void flx::tui::widget::click_begin()
//{
//}
//
//void flx::tui::widget::click_end()
//{
//}
//
//void flx::tui::widget::clear_buffer() noexcept
//{
//	for (u16 y = 0; y < buffer_size.y; y++)
//	{
//		for (u16 x = 0; x < buffer_size.x; x++)
//		{
//			buffer[xy_to_idx<u16>(x, y, buffer_size.x)] = ' ';
//		}
//	}
//}
//
//void flx::tui::widget::populate_buffer()
//{
//}

constexpr void flx::tui::widget::set_size(const flx::vec2<flx::u16>& new_size) noexcept
{
	size =
	{
		flx::max(MIN_SIZE.x, new_size.x),
		flx::max(MIN_SIZE.y, new_size.y)
	};
	return;
}

constexpr void flx::tui::widget::add_widget(flx::unique_ptr<flx::tui::widget> new_widget) noexcept
{
	new_widget->parent = this;
	widgets.push_back(flx::move(new_widget));
	return;
}

constexpr flx::unique_ptr<flx::tui::widget> flx::tui::widget::remove_widget(flx::tui::id_t removed_id) noexcept
{
	flx::unique_ptr<flx::tui::widget> result;

	for (auto& item : widgets)
	{
		if (item->id == removed_id)
		{
			result = flx::make_unique<widget>(item.release());

			widgets.erase(flx::dynamic_array<flx::unique_ptr<flx::tui::widget>, u32>::iterator{ &item });

			break;
		}
	}

	return result;
}

constexpr flx::unique_ptr<flx::tui::widget> flx::tui::widget::remove_widget(flx::u32 removed_idx) noexcept
{
	assert(removed_idx < widgets.size() && "imp_flx_tui_base.cpp::widget::remove_widget(u32): index for removal is out of bounds.");

	flx::unique_ptr<flx::tui::widget> result(widgets[removed_idx].release());

	widgets.erase(widgets.begin() + removed_idx);

	return result;
}

constexpr flx::tui::id_t::id_t() noexcept
	: val(last_id++)
{
}

constexpr flx::tui::id_t::id_t(u32 new_val) noexcept 
	: val(new_val)
{
}

constexpr flx::tui::id_t::operator u32() noexcept
{
	return val;
}

constexpr bool flx::tui::id_t::operator==(const id_t& other) noexcept
{
	return val == other.val;
}
