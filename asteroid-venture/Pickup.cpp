#include "Pickup.h"

Pickup::Pickup(const int _disappear_delay, const short _x, const short _y, const char *_data, const WORD _colour)
: Entity(PICKUP, _x, _y, GRAPHIC_SIZE, GRAPHIC_SIZE, _data, _colour), disappear_delay(time(nullptr) + _disappear_delay),
flashing(false), flash_delay(0)
{}
Pickup::~Pickup() {}

void Pickup::think() // Handles the flashing behaviour.
{
    if (time(nullptr) >= disappear_delay) {
        should_delete = true;
    }
    else {
        const time_t curtick = clock();
        if (curtick >= flash_delay) {
            flash_delay = curtick + 250;
            flashing = !flashing;
            fillBuffer(getGraphic(), flashing ? 0x0F : getColour()); // Fill buffer with the appropriate graphic and switch between white and its colour.
        }
    }
}
void Pickup::pickup(Fighter * _player) // Calls abstract pickup function defined by a child then marks itself for deletion.
{
    if (inScreen(*_player)) {
        pickupFunc(_player);
        should_delete = true;
    }
}