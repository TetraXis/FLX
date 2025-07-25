#include "imp_flx_tui_encoding.hpp"

namespace flx
{
	namespace tui
	{
		namespace symbols
		{
			// order
			// ┐ ┘ └ ┌ ┬ ┤ ┴ ├ ┼ │ ─

#if FLX_TUI_ENCODING == FLX_TUI_ENCODING_CP437
			//                                     ┐   ┘   └   ┌   ┬   ┤   ┴   ├   ┼   │   ─
			const i8 box_lite[]					= "\xBf\xD9\xC0\xDA\xC2\xB4\xC1\xC3\xC5\xB3\xC4";
			const i8 box_double[]				= "\xBB\xBC\xC8\xC9\xCB\xB9\xCA\xCC\xCE\xBA\xCD";
			const i8 box_double_horizontal[]	= "\xB8\xBE\xD4\xD5\xD1\xB5\xCF\xC6\xD8\xB3\xCD";
			const i8 box_double_vertical[]		= "\xB7\xBD\xD3\xD6\xD2\xB6\xD0\xC7\xD7\xBA\xC4";

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
			const i8 box_lite[]					= "+++++++++|-";
			const i8 box_double[]				= "#########H=";
			const i8 box_double_horizontal[]	= "#########|=";
			const i8 box_double_vertical[]		= "#########H-";
#endif // FLX_TUI_ENCODING != FLX_TUI_ENCODING_CP437
		} // namespace symbols
	} // namespace tui
} // namespace flx
