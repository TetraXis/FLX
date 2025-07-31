#include "imp_flx_tui_controller.hpp"

void flx::tui::tui_controller_base::add_widget(flx::unique_ptr<widget> new_widget) noexcept
{
	new_widget->populate_buffer();
	widgets.emplace_back(new_widget.release());

	return;
}