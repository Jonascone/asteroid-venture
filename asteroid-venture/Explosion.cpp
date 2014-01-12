#include "Explosion.h"

const char Explosion::GRAPHIC[4 * 5] =
{
    ' ', '*', '*', ' ',
    '*', '*', '*', '*',
    '*', '*', '*', '*',
    '*', '*', '*', '*',
    ' ', '*', '*', ' ',
};

Explosion::Explosion(const short _x, const short _y)
: Entity(EXPLOSION, _x - 2, _y - 2, 4, 5, GRAPHIC, 0x0C), disappear_time(time(nullptr) + 1)
{}
Explosion::~Explosion() {}

void Explosion::think()
{
    if (time(nullptr) >= disappear_time) {
        should_delete = true;
    }
}