#ifndef IMP_FLX_TUI_ENCODING_HPP
#define IMP_FLX_TUI_ENCODING_HPP

#include "flx_types.hpp"

#define FLX_TUI_ENCODING_ASCII 65001
#define FLX_TUI_ENCODING_CP437 437
#define FLX_TUI_DEFAULT_ENCODING FLX_TUI_ENCODING_CP437

#ifndef FLX_TUI_ENCODING
#define FLX_TUI_ENCODING FLX_TUI_DEFAULT_ENCODING
#endif // !FLX_TUI_ENCODING

namespace flx
{
	namespace tui
	{
		namespace characters
		{
			enum box_flags : u8
			{
				U = 1,		// up
				D = 2,		// down
				L = 4,		// left
				R = 8,		// right
				DH = 16,	// double horizontal
				DV = 32,	// double vertical};
			};

			extern const i8 box_drawing[64];
			extern const i8 box_shadow[4];
		} // namespace characters

		namespace colors
		{
			enum color_flags : u8
			{
				FOREGROUND_BLUE = 0x01,
				FOREGROUND_GREEN = 0x02,
				FOREGROUND_RED = 0x04,
				FOREGROUND_INTENSITY = 0x08,
				BACKGROUND_BLUE = 0x10,
				BACKGROUND_GREEN = 0x20,
				BACKGROUND_RED = 0x40,
				BACKGROUND_INTENSITY = 0x80,

				F_B = 0x01,
				F_G = 0x02,
				F_R = 0x04,
				F_I = 0x08,
				B_B = 0x10,
				B_G = 0x20,
				B_R = 0x40,
				B_I = 0x80
			};
		} // namespace colors

		struct cell
		{
			i8 character = ' ';
			u8 color = 0x07;

			cell() noexcept = default;
			cell(i8) noexcept;
			cell(u8) noexcept;

			cell& operator= (i8) noexcept;
			cell& operator= (u8) noexcept;
		}; // cell
	} // namespace tui
} // namespace flx

#endif // IMP_FLX_TUI_ENCODING_HPP