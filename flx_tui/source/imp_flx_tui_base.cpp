#include "imp_flx_tui_base.hpp"
#include "flx_utility.hpp"

flx::tui::widget::widget(flx::tui::widget_type new_type) noexcept : type(new_type)
{
}

void flx::tui::widget::set_size(const flx::vec2<flx::u16>& new_size) noexcept
{
	size =
	{
		flx::max<flx::u16>(MIN_SIZE.x, new_size.x),
		flx::max<flx::u16>(MIN_SIZE.y, new_size.y)
	};
	return;
}

void flx::tui::widget::add_widget(flx::unique_ptr<flx::tui::widget> new_widget) noexcept
{
	new_widget->parent.widget = this;
	widgets.push_back(flx::move(new_widget));
	return;
}

flx::unique_ptr<flx::tui::widget> flx::tui::widget::remove_widget(flx::tui::id_t removed_id) noexcept
{
	flx::unique_ptr<flx::tui::widget> result;

	for (auto& item : widgets)
	{
		if (item->id == removed_id)
		{
			result = flx::unique_ptr<widget>(item.release());

			widgets.erase(flx::dynamic_array<flx::unique_ptr<flx::tui::widget>, u32>::iterator{ &item });

			break;
		}
	}

	return result;
}

flx::unique_ptr<flx::tui::widget> flx::tui::widget::remove_widget(flx::u32 removed_idx) noexcept
{
	assert(removed_idx < widgets.size() && "imp_flx_tui_base.cpp::widget::remove_widget(u32): index for removal is out of bounds.");

	flx::unique_ptr<flx::tui::widget> result(widgets[removed_idx].release());

	widgets.erase(widgets.begin() + removed_idx);

	return result;
}

void flx::tui::widget::redraw_widget(widget* widget_to_redraw, const vec2<u16>& top_left, const vec2<u16>& bottom_right) noexcept
{
	// Since widget doesn't have a buffer, it just propagates to it's owner
	if (parent.widget)
	{
		parent.widget->redraw_widget(widget_to_redraw, top_left, bottom_right);
	}
}

flx::tui::id_t::id_t() noexcept
	: val(last_id++)
{
}

flx::tui::id_t::id_t(u32 new_val) noexcept 
	: val(new_val)
{
}

bool flx::tui::id_t::operator==(const id_t& other) const noexcept
{
	return val == other.val;
}
