#include "Explosion.h"

const char Explosion::GRAPHIC[4 * 5] =
{
    ' ', '*', '*', ' ',
    '*', '*', '*', '*',
    '*', '*', '*', '*',
    '*', '*', '*', '*',
    ' ', '*', '*', ' ',
};

Explosion::Explosion(const short _x, const short _y, const bool _sound)
: Entity(EXPLOSION, _x - 2, _y - 2, 4, 5, GRAPHIC, 0x0C), disappear_time(time(nullptr) + 1)
{
    if (_sound) PlaySoundA("audio/mew.wav", 0, SND_ASYNC | SND_NODEFAULT); // A little cheeky but meh.
}
Explosion::~Explosion() {}

void Explosion::think()
{
    if (time(nullptr) >= disappear_time) {
        should_delete = true;
    }
}