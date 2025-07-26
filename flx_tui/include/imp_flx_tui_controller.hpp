#ifndef IMP_FLX_TUI_CONTROLLER_HPP
#define IMP_FLX_TUI_CONTROLLER_HPP

//#include "imp_flx_tui_encoding.hpp"
#include "flx_vec.hpp"
#include "imp_flx_tui_base.hpp"
#include "flx_dynamic_array.hpp"

namespace flx
{
	namespace tui
	{
		// handles i/o
		struct tui_controller
		{
		flx_public:
			dynamic_array<widget> widgets{};

		flx_public:
			tui_controller() = default;
			~tui_controller() = default;
		}; // tui_controller
	} // namespace tui
} // namespace flx

#endif // IMP_FLX_TUI_CONTROLLER_HPP