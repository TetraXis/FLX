#define FLX_ALL_MEMBERS_ARE_PUBLIC

#include "flx_unique_ptr.hpp"
#include "flx_dynamic_array.hpp"
#include "flx_vec.hpp"
#include "flx_utility.hpp"
#include "flx_tui.hpp"
#include "flx_timer_windows.hpp"


#include <iostream>
#include <vector>
#include <sstream>
#include <type_traits>
#include <string>
#include <unordered_set>
#include <map>


using namespace flx;
using namespace tui;

#define META_TESTS 10
#define TESTS 10'000'000

int main()
{
	using namespace flx::tui::characters;
	
	tui::tui_controller ctrl;
	flx::unique_ptr<tui::window> wnd(new tui::window("Balls", { 80, 20 }));
	flx::unique_ptr<tui::window> wnd2(new tui::window("Balls2", { 8, 2 }));
	
	wnd->pos = { 5,2 };
	wnd2->pos = { 5,20 };
	
	ctrl.add_window(flx::move(wnd));
	ctrl.add_window(flx::move(wnd2));
	
	ctrl.start();
}