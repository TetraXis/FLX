#ifndef IMP_FLX_TUI_ENCODING_HPP
#define IMP_FLX_TUI_ENCODING_HPP

#include "flx_types.hpp"

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
		} // namespace symbols
	} // namespace tui
} // namespace flx

#endif // IMP_FLX_TUI_ENCODING_HPP