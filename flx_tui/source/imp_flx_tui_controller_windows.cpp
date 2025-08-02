#if defined(_WIN32) || defined(_WIN64)

#include "imp_flx_tui_encoding.hpp"
#include "imp_flx_tui_controller_windows.hpp"

#include "flx_utility.hpp"

void flx::tui::tui_controller_windows::start() noexcept
{
    // below is AI generated
    // throw it out after testing

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

    

    // Simple message
    //const char welcomeMsg[] = "Click and drag in console (LMB/RMB) or press ESC to exit:\n";
    //WriteConsoleA(console_output, welcomeMsg, sizeof(welcomeMsg) - 1, NULL, NULL);

    // Main input loop

    //populate_buffer_debug();

    while (true) 
    {
        populate_buffer();
        process_input();
        draw_buffer();
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
    ReadConsoleInputA(console_input, irInBuf, 128, &cNumRead);

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
        }
    }
}

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
        buffer.reset(new CHAR_INFO[buffer_size.x * buffer_size.y]);
        write_region = { 0, 0, (SHORT)(buffer_size.x - 1), (SHORT)(buffer_size.y - 1) };
    }
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
    i8* buff_ptr{};
    u16 pos_x{};
    u16 pos_y{};
    u16 size_x{};
    u16 size_y{};

    update_buffer_size();
    clear_buffer();

    for (u32 i = 0; i < widgets.size(); i++)
    {
        buff_ptr = widgets[i]->buffer.get();
        pos_x = widgets[i]->coord.x;
        pos_y = widgets[i]->coord.y;
        size_x = widgets[i]->size.x;
        size_y = widgets[i]->size.y;

        for (u16 y = 0; y < size_y && y < buffer_size.y; y++)
        {
            for (u16 x = 0; x < size_x && x < buffer_size.x; x++)
            {
                buffer[xy_to_idx<u16>(pos_x + x, pos_y + y, buffer_size.x)].Char.AsciiChar = buff_ptr[xy_to_idx(x, y, size_x)];
            }
        }
    }
}

void flx::tui::tui_controller_windows::draw_buffer() noexcept
{
    WriteConsoleOutputA(
        console_output,          // Console handle
        buffer.get(),            // Buffer to draw
        {(SHORT)buffer_size.x, (SHORT)buffer_size.y},        // Size of buffer (cols x rows)
        {0,0},       // Where to start copying (usually 0,0)
        &write_region       // Screen area to update
    );
}


#ifndef NDEBUG

void flx::tui::tui_controller_windows::start_debug_console() noexcept
{ 
    // Create a new console process
    STARTUPINFOA si = { sizeof(si) };
    PROCESS_INFORMATION pi;

    // Create the child process with its own console
    if (CreateProcessA(
        NULL,
        (char*)"cmd.exe",  // Start with cmd.exe
        NULL,
        NULL,
        FALSE,      // Don't inherit handles
        CREATE_NEW_CONSOLE,
        NULL,
        NULL,
        &si,
        &pi))
    {
        debug_console_process = pi.hProcess;

        // Wait for console to initialize
        Sleep(100);

        // Attach to the new console
        if (AttachConsole(pi.dwProcessId))
        {
            // Get console handles
            debug_console_output = GetStdHandle(STD_OUTPUT_HANDLE);
            debug_console_input = GetStdHandle(STD_INPUT_HANDLE);

            // Save original console mode
            GetConsoleMode(debug_console_input, &debug_prev_console_mode);

            // Set up console properties
            SetConsoleTitleA("Debug Console");
            CONSOLE_SCREEN_BUFFER_INFO csbi;
            GetConsoleScreenBufferInfo(debug_console_output, &csbi);
            debug_write_region = csbi.srWindow;

            // Detach from console to restore original state
            FreeConsole();
        }

        // Close thread handle (we keep process handle)
        CloseHandle(pi.hThread);
    }
}

void flx::tui::tui_controller_windows::debug_log(const char* message)
{
    if (!debug_console_process) return;

    // Attach to the debug console
    if (AttachConsole(debug_console_process ? GetProcessId(debug_console_process) : 0))
    {
        // Get output handle
        HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);

        // Write the message
        DWORD charsWritten;
        WriteConsoleA(hOutput, message, strlen(message), &charsWritten, NULL);
        WriteConsoleA(hOutput, "\n", 1, &charsWritten, NULL);

        // Detach from console
        FreeConsole();
    }
}

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