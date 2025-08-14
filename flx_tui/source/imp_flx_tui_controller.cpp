#include "imp_flx_tui_controller.hpp"

void flx::tui::tui_controller_base::add_window(flx::unique_ptr<flx::tui::window> new_window) noexcept
{
	new_window->redraw_buffer();
	new_window->parent.controller = this;
	windows.emplace_back(new_window.release());

	return;
}

void flx::tui::tui_controller_base::tick(u32 delta_time) noexcept
{
	// TODO: this should be at customer's class
	for (const auto& window_uptr : windows)
	{
		if (window_uptr->actions.size() > 0)
		{
			window_uptr->actions[0](window_uptr.get(), 0, (void**)(delta_time));
		}
	}
}
