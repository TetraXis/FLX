#ifndef IMP_FLX_TUI_ENCODING_HPP
#define IMP_FLX_TUI_ENCODING_HPP

#include "flx_types.hpp"

#define FLX_TUI_ENCODING_UTF16 65001
#define FLX_TUI_ENCODING_CP437 437
#define FLX_TUI_DEFAULT_ENCODING FLX_TUI_ENCODING_UTF16

#ifndef FLX_TUI_ENCODING
#define FLX_TUI_ENCODING FLX_TUI_DEFAULT_ENCODING
#endif // !FLX_TUI_ENCODING

namespace flx
{
	namespace tui
	{
		namespace colors
		{
			enum color_flags : u8
			{
				FOREGROUND_BLUE			= 0x01,
				FOREGROUND_GREEN		= 0x02,
				FOREGROUND_RED			= 0x04,
				FOREGROUND_INTENSITY	= 0x08,
				BACKGROUND_BLUE			= 0x10,
				BACKGROUND_GREEN		= 0x20,
				BACKGROUND_RED			= 0x40,
				BACKGROUND_INTENSITY	= 0x80,

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

		namespace characters
		{
			enum struct box_flags : u8
			{
                NONE = 0,
                SINGLE = 1,
                THICK = 2,
                DOUBLE = 3
			};

#if FLX_TUI_ENCODING == FLX_TUI_ENCODING_CP437

#error "imp_flx_tui_encoding.hpp: Code page 437 is not supported. Set FLX_TUI_ENCODING to FLX_TUI_ENCODING_UTF16."

            //constexpr c16 box_drawing[64] =
            //{
            //    // lite
            //    '\x14', '\x14', '\x14', '\xB3', '\x14', '\xD9', '\xBF', '\xB4', '\x14', '\xC0', '\xDA', '\xC3', '\xC4', '\xC1', '\xC2', '\xC5',
            //    // double horizontal
            //    '\x14', '\x14', '\x14', '\xB3', '\x14', '\xBE', '\xB8', '\xB5', '\x14', '\xD4', '\xD5', '\xC6', '\xCD', '\xCF', '\xD1', '\xD8',
            //    // double vertical
            //    '\x14', '\x14', '\x14', '\xBA', '\x14', '\xBD', '\xB7', '\xB6', '\x14', '\xD3', '\xD6', '\xC7', '\xC4', '\xD0', '\xD2', '\xD7',
            //    // double
            //    '\x14', '\x14', '\x14', '\xBA', '\x14', '\xBC', '\xBB', '\xB9', '\x14', '\xC8', '\xC9', '\xCC', '\xCD', '\xB9', '\xCB', '\xCE'
            //};

            //constexpr c16 box_shadow[4] = { '\x20', '\xB0', '\xB1', '\xB2' };

#endif // FLX_TUI_ENCODING != FLX_TUI_ENCODING_CP437

            

#if FLX_TUI_ENCODING == FLX_TUI_ENCODING_UTF16

            /// <summary>
            /// This array stores all box drawing characters. They are constructed using bit logic.
            /// There are 4 possible values (2 bits) { NONE, SINGLE, THICK, DOUBLE } as described in 'box_drawing'.
            /// Symbol is constructed out of values specified in this order:
            /// U D L R. Concatenating these will result in desired symbol or u'\xFFFF' if it does not exist.
            /// </summary>
            constexpr c16 box_drawing[256] =
            {
                u'\x0020',  // 0
                u'\x2576',  // 1
                u'\x257A',  // 2
                u'\xFFFF',  // 3
                u'\x2574',  // 4
                u'\x2500',  // 5
                u'\x257C',  // 6
                u'\xFFFF',  // 7
                u'\x2578',  // 8
                u'\x257E',  // 9
                u'\x2501',  // A
                u'\xFFFF',  // B
                u'\xFFFF',  // C
                u'\xFFFF',  // D
                u'\xFFFF',  // E
                u'\x2550',  // F
                u'\x2577',  // 10
                u'\x250C',  // 11
                u'\x250D',  // 12
                u'\x2552',  // 13
                u'\x2510',  // 14
                u'\x252C',  // 15
                u'\x252E',  // 16
                u'\xFFFF',  // 17
                u'\x2511',  // 18
                u'\x252D',  // 19
                u'\x252F',  // 1A
                u'\xFFFF',  // 1B
                u'\x2555',  // 1C
                u'\xFFFF',  // 1D
                u'\xFFFF',  // 1E
                u'\x2564',  // 1F
                u'\x257B',  // 20
                u'\x250E',  // 21
                u'\x250F',  // 22
                u'\xFFFF',  // 23
                u'\x2512',  // 24
                u'\x2530',  // 25
                u'\x2532',  // 26
                u'\xFFFF',  // 27
                u'\x2513',  // 28
                u'\x2531',  // 29
                u'\x2533',  // 2A
                u'\xFFFF',  // 2B
                u'\xFFFF',  // 2C
                u'\xFFFF',  // 2D
                u'\xFFFF',  // 2E
                u'\xFFFF',  // 2F
                u'\xFFFF',  // 30
                u'\x2553',  // 31
                u'\xFFFF',  // 32
                u'\x2554',  // 33
                u'\x2556',  // 34
                u'\x2565',  // 35
                u'\xFFFF',  // 36
                u'\xFFFF',  // 37
                u'\xFFFF',  // 38
                u'\xFFFF',  // 39
                u'\xFFFF',  // 3A
                u'\xFFFF',  // 3B
                u'\x2557',  // 3C
                u'\xFFFF',  // 3D
                u'\xFFFF',  // 3E
                u'\x2566',  // 3F
                u'\x2575',  // 40
                u'\x2514',  // 41
                u'\x2515',  // 42
                u'\x2558',  // 43
                u'\x2518',  // 44
                u'\x2534',  // 45
                u'\x2536',  // 46
                u'\xFFFF',  // 47
                u'\x2519',  // 48
                u'\x2535',  // 49
                u'\x2537',  // 4A
                u'\xFFFF',  // 4B
                u'\x255B',  // 4C
                u'\xFFFF',  // 4D
                u'\xFFFF',  // 4E
                u'\x2567',  // 4F
                u'\x2502',  // 50
                u'\x251C',  // 51
                u'\x251D',  // 52
                u'\x255E',  // 53
                u'\x2524',  // 54
                u'\x253C',  // 55
                u'\x253E',  // 56
                u'\xFFFF',  // 57
                u'\x2525',  // 58
                u'\x253D',  // 59
                u'\x253F',  // 5A
                u'\xFFFF',  // 5B
                u'\x2561',  // 5C
                u'\xFFFF',  // 5D
                u'\xFFFF',  // 5E
                u'\x256A',  // 5F
                u'\x257D',  // 60
                u'\x251F',  // 61
                u'\x2522',  // 62
                u'\xFFFF',  // 63
                u'\x2527',  // 64
                u'\x2541',  // 65
                u'\x2546',  // 66
                u'\xFFFF',  // 67
                u'\x252A',  // 68
                u'\x2545',  // 69
                u'\x2548',  // 6A
                u'\xFFFF',  // 6B
                u'\xFFFF',  // 6C
                u'\xFFFF',  // 6D
                u'\xFFFF',  // 6E
                u'\xFFFF',  // 6F
                u'\xFFFF',  // 70
                u'\xFFFF',  // 71
                u'\xFFFF',  // 72
                u'\xFFFF',  // 73
                u'\xFFFF',  // 74
                u'\xFFFF',  // 75
                u'\xFFFF',  // 76
                u'\xFFFF',  // 77
                u'\xFFFF',  // 78
                u'\xFFFF',  // 79
                u'\xFFFF',  // 7A
                u'\xFFFF',  // 7B
                u'\xFFFF',  // 7C
                u'\xFFFF',  // 7D
                u'\xFFFF',  // 7E
                u'\xFFFF',  // 7F
                u'\x2579',  // 80
                u'\x2516',  // 81
                u'\x2517',  // 82
                u'\xFFFF',  // 83
                u'\x251A',  // 84
                u'\x2538',  // 85
                u'\x253A',  // 86
                u'\xFFFF',  // 87
                u'\x251B',  // 88
                u'\x2539',  // 89
                u'\x253B',  // 8A
                u'\xFFFF',  // 8B
                u'\xFFFF',  // 8C
                u'\xFFFF',  // 8D
                u'\xFFFF',  // 8E
                u'\xFFFF',  // 8F
                u'\x257F',  // 90
                u'\x251E',  // 91
                u'\x2521',  // 92
                u'\xFFFF',  // 93
                u'\x2526',  // 94
                u'\x2540',  // 95
                u'\x2544',  // 96
                u'\xFFFF',  // 97
                u'\x2529',  // 98
                u'\x2543',  // 99
                u'\x2547',  // 9A
                u'\xFFFF',  // 9B
                u'\xFFFF',  // 9C
                u'\xFFFF',  // 9D
                u'\xFFFF',  // 9E
                u'\xFFFF',  // 9F
                u'\x2503',  // A0
                u'\x2520',  // A1
                u'\x2523',  // A2
                u'\xFFFF',  // A3
                u'\x2528',  // A4
                u'\x2542',  // A5
                u'\x254A',  // A6
                u'\xFFFF',  // A7
                u'\x252B',  // A8
                u'\x2549',  // A9
                u'\x254B',  // AA
                u'\xFFFF',  // AB
                u'\xFFFF',  // AC
                u'\xFFFF',  // AD
                u'\xFFFF',  // AE
                u'\xFFFF',  // AF
                u'\xFFFF',  // B0
                u'\xFFFF',  // B1
                u'\xFFFF',  // B2
                u'\xFFFF',  // B3
                u'\xFFFF',  // B4
                u'\xFFFF',  // B5
                u'\xFFFF',  // B6
                u'\xFFFF',  // B7
                u'\xFFFF',  // B8
                u'\xFFFF',  // B9
                u'\xFFFF',  // BA
                u'\xFFFF',  // BB
                u'\xFFFF',  // BC
                u'\xFFFF',  // BD
                u'\xFFFF',  // BE
                u'\xFFFF',  // BF
                u'\xFFFF',  // C0
                u'\x2559',  // C1
                u'\xFFFF',  // C2
                u'\x255A',  // C3
                u'\x255C',  // C4
                u'\x2568',  // C5
                u'\xFFFF',  // C6
                u'\xFFFF',  // C7
                u'\xFFFF',  // C8
                u'\xFFFF',  // C9
                u'\xFFFF',  // CA
                u'\xFFFF',  // CB
                u'\x255D',  // CC
                u'\xFFFF',  // CD
                u'\xFFFF',  // CE
                u'\x2569',  // CF
                u'\xFFFF',  // D0
                u'\xFFFF',  // D1
                u'\xFFFF',  // D2
                u'\xFFFF',  // D3
                u'\xFFFF',  // D4
                u'\xFFFF',  // D5
                u'\xFFFF',  // D6
                u'\xFFFF',  // D7
                u'\xFFFF',  // D8
                u'\xFFFF',  // D9
                u'\xFFFF',  // DA
                u'\xFFFF',  // DB
                u'\xFFFF',  // DC
                u'\xFFFF',  // DD
                u'\xFFFF',  // DE
                u'\xFFFF',  // DF
                u'\xFFFF',  // E0
                u'\xFFFF',  // E1
                u'\xFFFF',  // E2
                u'\xFFFF',  // E3
                u'\xFFFF',  // E4
                u'\xFFFF',  // E5
                u'\xFFFF',  // E6
                u'\xFFFF',  // E7
                u'\xFFFF',  // E8
                u'\xFFFF',  // E9
                u'\xFFFF',  // EA
                u'\xFFFF',  // EB
                u'\xFFFF',  // EC
                u'\xFFFF',  // ED
                u'\xFFFF',  // EE
                u'\xFFFF',  // EF
                u'\x2551',  // F0
                u'\x2559',  // F1
                u'\xFFFF',  // F2
                u'\x2560',  // F3
                u'\x2562',  // F4
                u'\x256B',  // F5
                u'\xFFFF',  // F6
                u'\xFFFF',  // F7
                u'\xFFFF',  // F8
                u'\xFFFF',  // F9
                u'\xFFFF',  // FA
                u'\xFFFF',  // FB
                u'\x2563',  // FC
                u'\xFFFF',  // FD
                u'\xFFFF',  // FE
                u'\x256C'  // FF
            };

            constexpr c16 box_shadow[5] = { u'\x0020', u'\x2591', u'\x2592', u'\x2593', u'\x2588' };

#endif // FLX_TUI_ENCODING != FLX_TUI_ENCODING_UTF16

            constexpr c16 udlr_to_char(box_flags up, box_flags down, box_flags left, box_flags right) noexcept
            {
                return box_drawing
                    [
                        (static_cast<u8>(up)    << 6) |
                        (static_cast<u8>(down)  << 4) |
                        (static_cast<u8>(left)  << 2) |
                        (static_cast<u8>(right) << 0)
                    ];
            }

		} // namespace characters
	} // namespace tui
} // namespace flx

#endif // IMP_FLX_TUI_ENCODING_HPP