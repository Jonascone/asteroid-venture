#include "LifePickup.h"

const char LifePickup::GRAPHIC[] = // 3 * 3
{
    ' ', 'P', ' ',
    'P', 'L', 'P',
    ' ', 'P', ' '
};

LifePickup::LifePickup(const short _x, const short _y)
: Pickup(5, _x, _y, GRAPHIC, 0x0A)
{}
LifePickup::~LifePickup() {}

void LifePickup::pickupFunc(Fighter *_player)
{
    _player->updateLives(1);
    PlaySoundA("audio/hfe.wav", 0, SND_ASYNC | SND_NODEFAULT);
}
const char* LifePickup::getGraphic()
{
    return GRAPHIC;
}