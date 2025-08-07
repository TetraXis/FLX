#include "imp_flx_tui_controller.hpp"

void flx::tui::tui_controller_base::add_widget(flx::unique_ptr<widget> new_widget) noexcept
{
	new_widget->populate_buffer();
	new_widget->parent.controller_ptr = this;
	widgets.emplace_back(new_widget.release());

	return;
}

void flx::tui::tui_controller_base::tick() noexcept
{
	for (const auto& widget_uptr : widgets)
	{
		widget_uptr->update();
	}
}
