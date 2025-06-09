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
#endif // FLX_TUI_ENCODING != FLX_TUI_ENCODING_CP437

#if FLX_TUI_ENCODING == FLX_TUI_ENCODING_ASCII
			const i8 box_lite[]					= "+++++++++|-";
			const i8 box_double[]				= "#########H=";
			const i8 box_double_horizontal[]	= "#########|=";
			const i8 box_double_vertical[]		= "#########H-";
#endif // FLX_TUI_ENCODING != FLX_TUI_ENCODING_CP437
		}
	}
}
