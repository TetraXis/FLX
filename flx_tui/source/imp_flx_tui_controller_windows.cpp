#if defined(_WIN32) || defined(_WIN64)

#include "imp_flx_tui_encoding.hpp"
#include "imp_flx_tui_controller_windows.hpp"

void flx::tui::tui_controller_windows::start() noexcept
{
    // below is AI generated
    // throw it out after testing

    // Allocate a console for this program
    AllocConsole();

    // Get standard handles
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    // Set console mode - critical for mouse tracking
    DWORD mode = 0;
    GetConsoleMode(hStdin, &mode);
    SetConsoleMode(hStdin,
        ENABLE_EXTENDED_FLAGS |
        ENABLE_MOUSE_INPUT |
        (mode & ~ENABLE_QUICK_EDIT_MODE));

    // Track mouse button states
    bool leftButtonDown = false;
    bool rightButtonDown = false;
    COORD lastMousePos = { 0,0 };

    // Buffer for reading input
    INPUT_RECORD irInBuf[128];
    DWORD cNumRead;

    // Simple message
    const char welcomeMsg[] = "Click and drag in console (LMB/RMB) or press ESC to exit:\n";
    WriteConsoleA(hStdout, welcomeMsg, sizeof(welcomeMsg) - 1, NULL, NULL);

    // Main input loop
    while (true) {
        // Wait for and read console input
        ReadConsoleInputA(hStdin, irInBuf, 128, &cNumRead);

        // Process each input event
        for (DWORD i = 0; i < cNumRead; i++) {
            switch (irInBuf[i].EventType) {
            case KEY_EVENT: {
                if (irInBuf[i].Event.KeyEvent.bKeyDown &&
                    irInBuf[i].Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE) {
                    const char exitMsg[] = "\nExiting...\n";
                    WriteConsoleA(hStdout, exitMsg, sizeof(exitMsg) - 1, NULL, NULL);
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

                    WriteConsoleA(hStdout, msg, p - msg, NULL, NULL);
                }
                break;
            }
            }
        }
    }

    FreeConsole();
    return;
}

#endif // Windows