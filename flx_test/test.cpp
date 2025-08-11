#define FLX_ALL_MEMBERS_ARE_PUBLIC

#include "flx_unique_ptr.hpp"
#include "flx_dynamic_array.hpp"
#include "flx_vec.hpp"
#include "flx_utility.hpp"
#include "flx_tui.hpp"


#include <iostream>
#include <vector>
#include <sstream>
#include <type_traits>
#include <string>
#include <unordered_set>
#include <map>


using namespace flx;

#define META_TESTS 10
#define TESTS 10'000'000

struct test_str
{
	int a = 0;
	//int* data_;

	//test_str() noexcept = default;
	//{
	//	data_ = new int[10];
	//}

	//test_str(test_str&& other) noexcept = default;
	//	:data_(other.data_)
	//{
	//	other.data_ = nullptr;
	//}

	//~test_str() noexcept = default;
	//{
	//	delete[] data_;
	//}

	//test_str(test_str&&) = default;
};
using test_t_std = std::vector			< test_str >;
using test_t_flx = flx::dynamic_array	< test_str >;

//struct widget
//{
//	//friend window; // this drives me nuts
//
//flx_protected:
//	widget* parent = nullptr;
//flx_public:
//	vec2<i16> coord{};
//	vec2<u16> min_size{};
//flx_protected:
//	vec2<u16> size{};
//flx_public:
//	u16 id{};
//	//const widget_type type = widget_type::none;
//	u8 flags{}; // For possible future uses
//
//flx_public:
//	widget() = default;
//};


using test_t = std::vector<test_str>;
//using test_t = flx::dynamic_array<test_str>;

#include "D:\C++\Tools\timer.h"

//dynamic_array<unique_ptr<widget>> widgets{};

//void test(flx::unique_ptr<widget>& new_widget)
//{
//	new_widget->parent = nullptr;
//	widgets.emplace_back(flx::move(new_widget.release()));
////}
//
//
//enum struct widget_type : u8
//{
//	none,			// Not defined primitive type
//	window,			// Can be moved or changed size by user
//	textview,		// Read-only text view
//	button,
//	display,		// handles io and all widgets
//	custom			// Custom type
//};
//
//struct widget
//{
//
//flx_protected:
//	widget* parent = nullptr;
//flx_public:
//	vec2<i16> coord{};
//	vec2<u16> min_size{};
//flx_protected:
//	vec2<u16> size{};
//flx_public:
//	u16 id{};
//	const widget_type type = widget_type::none;
//	u8 flags{}; // For possible future uses
//
//flx_protected:
//	widget(widget_type new_type) : type(new_type)
//	{
//	}
//
//flx_public:
//	widget() = default;
//	virtual ~widget()
//	{
//	}
//};

dynamic_array< unique_ptr<widget> > widgets{};

void test(flx::unique_ptr<widget>& new_widget)
{
	new_widget->parent = nullptr;
	widgets.emplace_back(flx::move(new_widget.release()));
}

int main()
{
	using namespace flx::tui::characters;

	tui::tui_controller ctrl;
	flx::unique_ptr<tui::widget> wnd(static_cast<tui::widget*>(new tui::window("Balls", { 80, 20 })));
	flx::unique_ptr<tui::widget> wnd2(static_cast<tui::widget*>(new tui::window("Balls2", { 8, 2 })));

	wnd->coord = { 5,2 };
	wnd2->coord = { 5,20 };

	wnd->update_func =
		[](flx::tui::widget* self)
		{
			self->populate_buffer();
			self->buffer[self->buffer_size.x + (self->parent.controller_ptr->ticks +    0) / 50 % ((self->buffer_size.x - 1) * (self->buffer_size.y - 1))] = '\x01';
			self->buffer[self->buffer_size.x + (self->parent.controller_ptr->ticks +  500) / 50 % ((self->buffer_size.x - 1) * (self->buffer_size.y - 1))] = '\x01';
			self->buffer[self->buffer_size.x + (self->parent.controller_ptr->ticks + 1000) / 50 % ((self->buffer_size.x - 1) * (self->buffer_size.y - 1))] = '\x01';
			self->buffer[self->buffer_size.x + (self->parent.controller_ptr->ticks + 1500) / 50 % ((self->buffer_size.x - 1) * (self->buffer_size.y - 1))] = '\x01';
			//for (u16 y = 1; y < self->buffer_size.y - 1; y++)
			//{
			//	for (u16 x = 1; x < self->buffer_size.x - 1; x++)
			//	{
			//		//self->buffer[xy_to_idx<u16>(x, y, self->buffer_size.x)] = i8(((self->parent.controller_ptr->ticks / 250) % 2 + x + y) % 2 + 1);
			//	}
			//}
		};

	ctrl.add_widget(flx::move(wnd));
	ctrl.add_widget(flx::move(wnd2));

	//wnd->populate_buffer_debug();
	//wnd->print();

	ctrl.start();
	//dynamic_array<int> a;
	//dynamic_array<int, unsigned int> b;
	//dynamic_array<int, float> c;
	//unique_ptr<widget> up(new widget());

	//test(up);

	//widgets.emplace_back(new widget());
	//unique_ptr<widget> up(new widget());

	//test(up);

	
	//using namespace flx::tui;

	//window wnd;
	//
	//wnd.set_size({ 40, 30 });
	//wnd.set_name("Balls");

	//flx::dynamic_array<flx::unique_ptr<int>> a;
	//
	//a.emplace_back(new int(1));
	//a.emplace_back(new int(1));
	//a.emplace_back(new int(1));
	//a.emplace_back(new int(1));
	//a.emplace_back(new int(1));
	//a.emplace_back(new int(1));
}