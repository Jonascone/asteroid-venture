#include "RapidFirePickup.h"

const char RapidFirePickup::GRAPHIC[] =
{
    ' ', 'P', ' ',
    'P', 'R', 'P',
    ' ', 'P', ' '
};

RapidFirePickup::RapidFirePickup(const short _x, const short _y)
: Pickup(5, _x, _y, GRAPHIC, 0x0D)
{}
RapidFirePickup::~RapidFirePickup() {}

void RapidFirePickup::pickupFunc(Fighter *_player)
{
    _player->setRapidFire(5);
}
const char* RapidFirePickup::getGraphic()
{
    return GRAPHIC;
}