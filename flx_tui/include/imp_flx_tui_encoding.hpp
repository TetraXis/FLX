#pragma once

#include "flx_types.hpp"

// CP437


#define FLX_TUI_ENCODING_ASCII 0
#define FLX_TUI_ENCODING_CP437 437
#define FLX_TUI_DEFAULT_ENCODING FLX_TUI_ENCODING_CP437

#ifndef FLX_TUI_ENCODING
#define FLX_TUI_ENCODING FLX_TUI_DEFAULT_ENCODING
#endif // !FLX_TUI_DEFAULT_ENCODING


namespace flx
{
	namespace tui
	{
		namespace symbols
		{
			enum box_flags : u8
			{
				U = 1,		// up
				D = 2,		// down
				L = 4,		// left
				R = 8,		// right
				DH = 16,	// double horizontal
				DV = 32		// double vertical
			};

			extern const i8 box_drawing[64];
			extern const i8 box_shadow[4];

			constexpr u8 DOWN_LEFT				= 0;
			constexpr u8 UP_LEFT				= 1;
			constexpr u8 UP_RIGHT				= 2;
			constexpr u8 DOWN_RIGHT				= 3;
			constexpr u8 DOWN_AND_HORIZONTAL	= 4;
			constexpr u8 LEFT_AND_VERTICAL		= 5;
			constexpr u8 UP_AND_HORIZONTAL		= 6;
			constexpr u8 RIGHT_AND_VERTICAL		= 7;
			constexpr u8 CROSS					= 8;
			constexpr u8 VERTICAL				= 9;
			constexpr u8 HORIZONTAL				= 10;

			// order
			// ┐ ┘ └ ┌ ┬ ┤ ┴ ├ ┼ │ ─
			extern const i8 box_lite[];
			extern const i8 box_double[];
			extern const i8 box_double_horizontal[];
			extern const i8 box_double_vertical[];
		} // namespace symbols
	} // namespace tui
} // namespace flx