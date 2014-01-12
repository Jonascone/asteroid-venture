#pragma once

#include "Asteroid.h"

const char Asteroid::GRAPHIC[6 * 5] =
{
    ' ', ' ', '0', '0', ' ', ' ',
    ' ', '0', '0', ' ', '0', ' ',
    '0', ' ', '0', '0', '0', '0',
    ' ', '0', ' ', '0', '0', ' ',
    ' ', ' ', '0', '0', ' ', ' '
};

Asteroid::Asteroid(const short _x, const short _y, const short _vel)
: Entity(ASTEROID, _x, _y, 6, 5, GRAPHIC, 0x08), vel(_vel)
{}
Asteroid::~Asteroid()
{}

void Asteroid::think()
{
    position.X += vel;
}