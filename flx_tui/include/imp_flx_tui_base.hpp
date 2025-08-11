#ifndef IMP_FLX_TUI_BASE_HPP
#define IMP_FLX_TUI_BASE_HPP

#include "flx_types.hpp"
#include "flx_vec.hpp"
#include "flx_unique_ptr.hpp"
#include "flx_dynamic_array.hpp"

#ifndef NDEBUG
#include <cassert>
#else
#define assert(expr) ((void)0)
#endif // !NDEBUG

namespace flx
{
	namespace tui
	{
		enum struct widget_type : u8
		{
			none,			// Not defined primitive type
			window,			// Can be moved or changed size by user
			textview,		// Read-only text view
			button,
			display,		// handles io and all widgets
			custom			// Custom type
		}; // widget_type

		/// When contructed by default:
		/// automatically assigns 'va' to next free id
		struct id_t
		{
			static inline u32 last_id = 0;

			u32 val;

			constexpr id_t() noexcept;
			constexpr explicit id_t(u32 new_val) noexcept;
			constexpr explicit operator u32() noexcept;

			constexpr bool operator== (const id_t&) noexcept;
		};

		struct window;
		struct tui_controller_base;
		struct tui_controller_windows;

		struct widget
		{
			static constexpr vec2<u16> MIN_SIZE = { 5,2 };

			widget* parent{};
			dynamic_array<unique_ptr<widget>, u32> widgets{};
			/// Actions can be used for anything
			/// 
			/// 'argc' - amount of arguments
			/// 'argv' - arguments
			/// 
			/// Have a habit of passing the caller as 0th argument
			/// Actions should not free 'argv'
			dynamic_array<bool (*) (u32 argc, void* argv[]), u32> actions;
			vec2<i16> pos{};
			vec2<u16> size = MIN_SIZE;
			id_t id{};
			u16 flags{};
			const widget_type type = widget_type::none;
			//u8 PADDING; // unused space 

			constexpr void set_size(const vec2<u16>&) noexcept;

			constexpr void add_widget(unique_ptr<widget>) noexcept;
			constexpr unique_ptr<widget> remove_widget(id_t removed_id) noexcept;
			constexpr unique_ptr<widget> remove_widget(u32 removed_idx) noexcept;


		//	friend window; // this drives me nuts
		//	friend tui_controller_base;
		//	friend tui_controller_windows;

		//flx_protected:
		//	union parent_union
		//	{
		//		widget* widget_ptr;
		//		tui_controller_base* controller_ptr;
		//	} parent{ nullptr };
		//	//widget* parent = nullptr;
		//	// buffer that contains all content inside
		//	flx::unique_ptr<i8[]> buffer{};
		//	vec2<u16> buffer_size{};
		//flx_public:
		//	vec2<i16> coord{};
		//	vec2<u16> min_size{};
		//flx_protected:
		//	vec2<u16> size{};
		//flx_public:
		//	flx::dynamic_array< unique_ptr<widget>, u32 > widgets{};
		//	u16 id{};
		//	const widget_type type = widget_type::none;
		//	u8 flags{}; // For possible future uses
		//	void (*update_func) (widget*) = [](widget*){};

		//flx_protected:
		//	widget(widget_type);

		//flx_public:
		//	widget() = default;
		//	virtual ~widget();

		//	vec2<u16> get_size() const;
		//	virtual	void set_size(const vec2<u16>&);

		//	void update() noexcept;

		//	virtual void hover_begin();
		//	virtual void hover_end();
		//	virtual void click_begin();
		//	virtual void click_end();

		//	void clear_buffer() noexcept;
		//	/// <summary>
		//	/// Fills the buffer with chars
		//	/// </summary>
		//	virtual void populate_buffer();
		}; // widget
	} // namespace tui
} // namespace flx

#endif // !IMP_FLX_TUI_BASE_HPP