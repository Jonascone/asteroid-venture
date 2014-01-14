#include "Console.h"

void Console::clear() // Clear the screen.
{
    for (short i = 0; i < dimensions.X * dimensions.Y; ++i) {
        buffer[i].Attributes = 0x0F;
        buffer[i].Char.AsciiChar = ' ';
    }
}

Console::Console(const char *_title, const short _w, const short _h)
: Graphic(0, 0, _w, _h), keys(new BOOL[256]())
{ // Initialise the window.
    out = GetStdHandle(STD_OUTPUT_HANDLE), in = GetStdHandle(STD_INPUT_HANDLE);

    SetConsoleTitleA(_title);
    
    sr_dimensions.Top = sr_dimensions.Left = 0;
    sr_dimensions.Bottom = _h - 1, sr_dimensions.Right = _w - 1;

    cursor_info.bVisible = FALSE;
    cursor_info.dwSize = 1;

    SetConsoleScreenBufferSize(out, dimensions);
    SetConsoleCursorInfo(out, &cursor_info);
    SetConsoleWindowInfo(out, TRUE, &sr_dimensions);
}
Console::~Console() 
{
    clearGraphics();
    delete[] keys;
}

void Console::clearGraphics()
{
    for (auto it = graphics.begin(); it != graphics.end(); ++it) {
        delete (*it);
    }
    graphics.clear();
}

void Console::pushGraphic(const Graphic *_graphic, const bool _push_back) // Push a graphic onto the screen.
{
    if (!_graphic) return;
    else if (_push_back) {
        graphics.push_back(_graphic);
        return;
    }
    graphics.push_front(_graphic);
}
void Console::readInput() // Check for input and stuff.
{
    DWORD num_events, num_events_read;
    GetNumberOfConsoleInputEvents(in, &num_events);
    if (num_events) {
        INPUT_RECORD *events = new INPUT_RECORD[num_events];
        ReadConsoleInputA(in, events, num_events, &num_events_read);

        for (DWORD i = 0; i < num_events_read; ++i) {
            INPUT_RECORD &i_event = events[i];
            switch (i_event.EventType) {
            case KEY_EVENT:
                keys[i_event.Event.KeyEvent.wVirtualKeyCode] = i_event.Event.KeyEvent.bKeyDown;
                break;
            default:
                continue;
                break;
            }

        }
        delete[] events;
    }
}
void Console::eraseGraphic(const Graphic *_graphic) // Erase a graphic given by pointer.
{
    for (auto it = graphics.begin(); it != graphics.end(); ++it) {
        if (*it == _graphic) {
            graphics.erase(it);
            return;
        }
    }
}
void Console::render() // Render the screen.
{
    clear();
    for (auto it = graphics.begin(); it != graphics.end(); ++it) {
        drawGraphic(**it);
    }
    const COORD write_pos = { 0, 0 };
    WriteConsoleOutputA(out, buffer, dimensions, write_pos, &sr_dimensions);
    readInput();
}