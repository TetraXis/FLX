#include "imp_flx_tui_encoding.hpp"

namespace flx
{
	namespace tui
	{
		namespace characters
		{

#if FLX_TUI_ENCODING == FLX_TUI_ENCODING_CP437

			const i8 box_drawing[64] =
			{
				// lite
				'\x14', '\x14', '\x14', '\xB3', '\x14', '\xD9', '\xBF', '\xB4', '\x14', '\xC0', '\xDA', '\xC3', '\xC4', '\xC1', '\xC2', '\xC5',
				// double horizontal
				'\x14', '\x14', '\x14', '\xB3', '\x14', '\xBE', '\xB8', '\xB5', '\x14', '\xD4', '\xD5', '\xC6', '\xCD', '\xCF', '\xD1', '\xD8',
				// double vertical
				'\x14', '\x14', '\x14', '\xBA', '\x14', '\xBD', '\xB7', '\xB6', '\x14', '\xD3', '\xD6', '\xC7', '\xC4', '\xD0', '\xD2', '\xD7',
				// double
				'\x14', '\x14', '\x14', '\xBA', '\x14', '\xBC', '\xBB', '\xB9', '\x14', '\xC8', '\xC9', '\xCC', '\xCD', '\xB9', '\xCB', '\xCE'
			};

			const i8 box_shadow[4] = { '\x20', '\xB0', '\xB1', '\xB2' };
#endif // FLX_TUI_ENCODING != FLX_TUI_ENCODING_CP437

#if FLX_TUI_ENCODING == FLX_TUI_ENCODING_ASCII
#error "imp_flx_encoding.cpp: no ascii encoding is provided."
#endif // FLX_TUI_ENCODING != FLX_TUI_ENCODING_ASCII

		} // namespace characters

		cell::cell(i8 new_char) noexcept
			: character(new_char)
		{
		}

		cell::cell(u8 new_color) noexcept
			: color(new_color)
		{
		}

		cell& cell::operator=(i8 new_char) noexcept
		{
			character = new_char;
			return *this;
		}

		cell& cell::operator=(u8 new_color) noexcept
		{
			color = new_color;
			return *this;
		}
	} // namespace tui
} // namespace flx
