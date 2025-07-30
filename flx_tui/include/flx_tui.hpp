#pragma once

#include "imp_flx_tui_encoding.hpp"
#include "imp_flx_tui_base.hpp"
#include "imp_flx_tui_window.hpp"
#include "imp_flx_tui_controller.hpp"

#if defined(_WIN32) || defined(_WIN64) // Windows
	#include "imp_flx_tui_controller_windows.hpp"
#elif defined(__linux__) // Linux
	#include "imp_flx_tui_controller_linux.hpp"
#endif