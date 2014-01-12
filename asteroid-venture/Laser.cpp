#pragma once

#include "Laser.h"

const char Laser::GRAPHIC[4] = { 'O', 'O', 'O', 'O' };

Laser::Laser(const short _x, const short _y, const short _vel)
: Entity(LASER, _x, _y, 4, 1, GRAPHIC, 0x0C), vel(_vel)
{}
Laser::~Laser() {}

void Laser::think()
{
    position.X += vel;
}