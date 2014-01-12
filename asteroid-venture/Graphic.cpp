#include "Graphic.h"

void Graphic::drawGraphic(const Graphic &_graphic) // Draw a graphic.
{
    CHAR_INFO *g_buffer = _graphic.buffer;
    if (!g_buffer || !_graphic.shouldDraw()) return;

    const COORD &g_dimensions = _graphic.dimensions;
    const COORD &g_position = _graphic.position;

    const short min_y = min(g_dimensions.Y, dimensions.Y); // Prevent access violations in case graphic is smaller than target.
    const short min_x = min(g_dimensions.X, dimensions.X);

    short j = 0, i = 0;
    for (j = 0; j < min_y; ++j) {
        const short new_y = g_position.Y + j;
        if (new_y >= dimensions.Y || new_y <= -g_dimensions.Y) break;

        for (i = 0; i < min_x; ++i) {
            const short new_x = g_position.X + i;
            if (new_x >= dimensions.X || new_x <= -g_dimensions.X) break;
            else if (new_x < 0) continue;
            const CHAR_INFO &g_cell = g_buffer[i + j * g_dimensions.X];
            if (g_cell.Char.AsciiChar == ' ') continue; // If the cell is a space, we'll keep the data thanks!
            buffer[new_x + new_y * dimensions.X] = g_buffer[i + j * g_dimensions.X];
        }
    }
}
bool Graphic::inScreen(const Graphic &_graphic) // Check whether the graphics are overlapping.
{
    const COORD &g_dimensions = _graphic.dimensions;
    const COORD &g_position = _graphic.position;
    if (g_position.X >= position.X - g_dimensions.X && g_position.X < position.X + dimensions.X && g_position.Y >= position.Y - g_dimensions.Y && g_position.Y < position.Y + dimensions.Y) {
        return true;
    }
    return false;
}

Graphic::Graphic(const short _x, const short _y, const short _w, const short _h) // Predefined graphic.
: buffer(new CHAR_INFO[_w * _h]()), should_draw(true), should_delete(false)
{
    position.X = _x, position.Y = _y;
    dimensions.X = _w, dimensions.Y = _h;
}
Graphic::Graphic(const short _x, const short _y) // Undefined graphic.
: buffer(nullptr), should_draw(true), should_delete(false)
{
    position.X = _x, position.Y = _y;
    dimensions.X = 0, dimensions.Y = 0;
}
Graphic::~Graphic()
{
    delete[] buffer;
}

// Self-explanatory.
bool Graphic::shouldDelete() const
{
    return should_delete;
}
void Graphic::setDelete(const bool _delete)
{
    should_delete = _delete;
}
bool Graphic::shouldDraw() const
{
    return should_draw;
}
void Graphic::setDraw(const bool _draw)
{
    should_draw = _draw;
}
COORD Graphic::getCentre() const
{
    return { position.X + dimensions.X / 2, position.Y + dimensions.Y / 2 };
}
