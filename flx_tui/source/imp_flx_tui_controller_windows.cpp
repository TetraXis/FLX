#if defined(_WIN32) || defined(_WIN64)

#include <string> // TODO: remove this

#include "imp_flx_tui_encoding.hpp"
#include "imp_flx_tui_controller_windows.hpp"

#include "flx_utility.hpp"

void flx::tui::tui_controller_windows::start() noexcept
{
    // Allocate a console for this program
    AllocConsole();

    // Get standard handles
    /*HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);*/

    console_input = GetStdHandle(STD_INPUT_HANDLE);
    console_output = GetStdHandle(STD_OUTPUT_HANDLE);

    // Set console mode - critical for mouse tracking
    //DWORD mode = 0;
    GetConsoleMode(console_input, &prev_console_mode);
    SetConsoleMode(console_input,
        ENABLE_EXTENDED_FLAGS |
        ENABLE_MOUSE_INPUT |
        (prev_console_mode & ~ENABLE_QUICK_EDIT_MODE));

    SetConsoleOutputCP(FLX_TUI_ENCODING);
    SetConsoleCP(FLX_TUI_ENCODING);

    // Simple message
    //const char welcomeMsg[] = "Click and drag in console (LMB/RMB) or press ESC to exit:\n";
    //WriteConsoleA(console_output, welcomeMsg, sizeof(welcomeMsg) - 1, NULL, NULL);

    // Main input loop

    //populate_buffer_debug();

    timer t;
    f64 fps;
    std::string text;

    constexpr u64 DELAYS_AMOUNT = 1024 * 64;

    flx::dynamic_array<u16> delays{ DELAYS_AMOUNT, 0 };
    u64 total_time = 0;

    populate_buffer();
    draw_buffer();

    while (true) 
    {
        t.start();
        process_input();
        tick(t.elapsed_milliseconds());
        //populate_buffer();
        //draw_buffer();
        ticks++;
        t.stop();




        total_time -= delays[ticks % DELAYS_AMOUNT];
        delays[ticks % DELAYS_AMOUNT] = t.elapsed_milliseconds();
        total_time += delays[ticks % DELAYS_AMOUNT];
        fps = min(ticks, DELAYS_AMOUNT) * 1000 / max(1, total_time);
        text = std::to_string(fps) + " fps";
        if (ticks < DELAYS_AMOUNT)
        {
            text += " (?)";
        }
        SetConsoleTitleA(text.c_str());
    }

    FreeConsole();
    return;
}

void flx::tui::tui_controller_windows::process_input() noexcept
{
    // Track mouse button states
    bool leftButtonDown = false;
    bool rightButtonDown = false;
    COORD lastMousePos = { 0,0 };

    // Buffer for reading input
    INPUT_RECORD irInBuf[128];
    DWORD cNumRead;

    // Wait for and read console input
    if (!PeekConsoleInputA(console_input, irInBuf, 128, &cNumRead) || cNumRead == 0)
    {
        ReadConsoleInputA(console_input, irInBuf, 128, &cNumRead);
    }

    // Process each input event
    for (DWORD i = 0; i < cNumRead; i++) {
        switch (irInBuf[i].EventType) {
        case KEY_EVENT: {
            if (irInBuf[i].Event.KeyEvent.bKeyDown &&
                irInBuf[i].Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE) {
                const char exitMsg[] = "\nExiting...\n";
                WriteConsoleA(console_output, exitMsg, sizeof(exitMsg) - 1, NULL, NULL);
                Sleep(1000);
                FreeConsole();
                return;
            }
            break;
        }
        case MOUSE_EVENT: {
            MOUSE_EVENT_RECORD mer = irInBuf[i].Event.MouseEvent;

            // Update button states
            if (mer.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) {
                leftButtonDown = true;
            }
            else if (leftButtonDown && !(mer.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)) {
                leftButtonDown = false;
            }

            if (mer.dwButtonState & RIGHTMOST_BUTTON_PRESSED) {
                rightButtonDown = true;
            }
            else if (rightButtonDown && !(mer.dwButtonState & RIGHTMOST_BUTTON_PRESSED)) {
                rightButtonDown = false;
            }

            // Only report when mouse is moving with button pressed
            if ((leftButtonDown || rightButtonDown) &&
                (mer.dwEventFlags & MOUSE_MOVED) &&
                (mer.dwMousePosition.X != lastMousePos.X ||
                    mer.dwMousePosition.Y != lastMousePos.Y)) {

                // Remember position
                lastMousePos = mer.dwMousePosition;

                // Determine which button is pressed
                const char* btn = leftButtonDown ? "LMB" : "RMB";

                // Format output without sprintf
                char msg[32] = { 0 };
                char* p = msg;

                // Add button prefix
                const char* prefix = btn;
                while (*prefix) *p++ = *prefix++;

                // Add position text
                const char* at = " at (";
                while (*at) *p++ = *at++;

                // Add X coordinate
                int x = mer.dwMousePosition.X;
                if (x == 0) {
                    *p++ = '0';
                }
                else {
                    int div = 1000;
                    while (div && !(x / div)) div /= 10;
                    while (div) {
                        *p++ = '0' + (x / div);
                        x %= div;
                        div /= 10;
                    }
                }

                *p++ = ',';

                // Add Y coordinate
                int y = mer.dwMousePosition.Y;
                if (y == 0) {
                    *p++ = '0';
                }
                else {
                    int div = 1000;
                    while (div && !(y / div)) div /= 10;
                    while (div) {
                        *p++ = '0' + (y / div);
                        y %= div;
                        div /= 10;
                    }
                }

                *p++ = ')';
                *p++ = '\r'; // Use carriage return to update position

                WriteConsoleA(console_output, msg, p - msg, NULL, NULL);
            }
            break;
        }
        case WINDOW_BUFFER_SIZE_EVENT: {
            // The console window size has changed
            update_buffer_size();
            break;
        }
        }
    }
}

void flx::tui::tui_controller_windows::redraw_window(flx::tui::window* window_to_redraw, const flx::vec2<flx::u16>& top_left, const flx::vec2<flx::u16>& bottom_right) noexcept
{
    auto it = windows.begin();

    while (&**it != window_to_redraw)
    {
        ++it;
    }

    while (it != windows.end())
    {
        for (u16 y = flx::max<u16>(top_left.y, (**it).pos.y); y < flx::min<u16>(bottom_right.y, (**it).pos.y + (**it).size.y); y++)
        {
            for (u16 x = flx::max<u16>(top_left.x, (**it).pos.x); x < flx::min<u16>(bottom_right.x, (**it).pos.x + (**it).size.x); x++)
            {
                buffer[xy_to_idx<u16>(x, y, buffer_size.x)].Char.AsciiChar = (**it).buffer[xy_to_idx<u16>(x - (**it).pos.x, y - (**it).pos.y, buffer_size.x)].character;
                buffer[xy_to_idx<u16>(x, y, buffer_size.x)].Attributes = (**it).buffer[xy_to_idx<u16>(x - (**it).pos.x, y - (**it).pos.y, buffer_size.x)].color;
            }
        }
    }
}

#include <iostream>

void flx::tui::tui_controller_windows::update_buffer_size() noexcept
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(console_output, &csbi);
    //buffer_size.x = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    //buffer_size.y = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    if (buffer_size.x < csbi.srWindow.Right - csbi.srWindow.Left + 1 || buffer_size.y < csbi.srWindow.Bottom - csbi.srWindow.Top + 1)
    {
        buffer_size.x = flx::max<u16>(buffer_size.x, csbi.srWindow.Right - csbi.srWindow.Left + 1);
        buffer_size.y = flx::max<u16>(buffer_size.y, csbi.srWindow.Bottom - csbi.srWindow.Top + 1);

        //std::cout << buffer_size.x << '\n';
        //std::cout << buffer_size.y << '\n';


        //system("pause");

        buffer.reset(new CHAR_INFO[buffer_size.x * buffer_size.y]);
    }

    SetConsoleScreenBufferSize(console_output, { (SHORT)(csbi.srWindow.Right - csbi.srWindow.Left + 1), (SHORT)(csbi.srWindow.Bottom - csbi.srWindow.Top + 1) });
    write_region = { 0, 0, (SHORT)(csbi.srWindow.Right - csbi.srWindow.Left + 1), (SHORT)(csbi.srWindow.Bottom - csbi.srWindow.Top + 1) };
}   

void flx::tui::tui_controller_windows::clear_buffer() noexcept
{
    for (u16 y = 0; y < buffer_size.y; y++)
    {
        for (u16 x = 0; x < buffer_size.x; x++)
        {
            buffer[xy_to_idx<u16>(x, y, buffer_size.x)].Attributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
            buffer[xy_to_idx<u16>(x, y, buffer_size.x)].Char.AsciiChar = ' ';
        }
    }
}

void flx::tui::tui_controller_windows::populate_buffer() noexcept
{
    cell* buff_ptr{};
    u16 pos_x{};
    u16 pos_y{};
    u16 size_x{};
    u16 size_y{};
    u16 end_y{};
    u16 end_x{};

    update_buffer_size();
    clear_buffer();

    for (u32 i = 0; i < windows.size(); i++)
    {
        buff_ptr = windows[i]->buffer.get();
        pos_x = windows[i]->pos.x;
        pos_y = windows[i]->pos.y;
        size_x = windows[i]->size.x;
        size_y = windows[i]->size.y;
        end_y = flx::min<u16>(buffer_size.y, pos_y + size_y);
        end_x = flx::min<u16>(buffer_size.x, pos_x + size_x);

        for (u16 y = pos_y; y < end_y; y++)
        {
            for (u16 x = pos_x; x < end_x; x++)
            {
                /*std::cout << "x           :" << x          << '\n';
                std::cout << "y           :" << y          << '\n';
                std::cout << "buff_ptr    :" << buff_ptr   << '\n';
                std::cout << "pos_x       :" << pos_x      << '\n';
                std::cout << "pos_y       :" << pos_y      << '\n';
                std::cout << "size_x      :" << size_x     << '\n';
                std::cout << "size_y      :" << size_y     << '\n';
                std::cout << "end_y       :" << end_y      << '\n';
                std::cout << "end_x       :" << end_x      << '\n';

                system("pause");*/

                buffer[xy_to_idx<u16>(x, y, buffer_size.x)].Char.AsciiChar = buff_ptr[xy_to_idx<u16>(x - pos_x, y - pos_y, size_x)].character;
                buffer[xy_to_idx<u16>(x, y, buffer_size.x)].Attributes = buff_ptr[xy_to_idx<u16>(x - pos_x, y - pos_y, size_x)].color;
            }
        }
    }
}

void flx::tui::tui_controller_windows::draw_buffer() noexcept
{
    WriteConsoleOutputA
    (
        console_output,
        buffer.get(),
        {(SHORT)buffer_size.x, (SHORT)buffer_size.y},
        {0,0},
        &write_region
    );
}


#ifndef NDEBUG

void flx::tui::tui_controller_windows::populate_buffer_debug() noexcept
{
    
    update_buffer_size();
    clear_buffer();

    for (u16 y = 0; y < buffer_size.y; y++)
    {
        for (u16 x = 0; x < buffer_size.x; x++)
        {
            buffer[xy_to_idx<u16>(x, y, buffer_size.x)].Char.AsciiChar = 'A' + i8(y);
        }
    }
}

#endif

#endif // Windows