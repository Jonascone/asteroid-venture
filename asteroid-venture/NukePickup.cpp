#include "NukePickup.h"

const char NukePickup::GRAPHIC[] = 
{
    ' ', 'P', ' ',
    'P', 'N', 'P',
    ' ', 'P', ' '
};

NukePickup::NukePickup(const short _x, const short _y)
: Pickup(5, _x, _y, GRAPHIC, 0x0E)
{}
NukePickup::~NukePickup() {}

void NukePickup::pickupFunc(Fighter *_player)
{
    _player->setNuke(true);
    PlaySoundA("audio/bew.wav", 0, SND_ASYNC | SND_NODEFAULT);
}
const char* NukePickup::getGraphic()
{
    return GRAPHIC;
}