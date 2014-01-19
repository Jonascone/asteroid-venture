#pragma once

#include "Asteroid.h"
#include <cmath>

const char* Asteroid::GetGraphic(const short radius) {
	auto diameter = radius * 2 + 1;
	auto graphic = new char[diameter*diameter]();
	for (short i = 0; i < diameter; i++) {
		for (short j = 0; j < diameter; j++) {
			short xdist = i - radius;
			short ydist = j - radius;

			if (xdist*xdist + ydist*ydist <= radius*radius) {
				graphic[j*diameter + i] = '0';
			} else {
				graphic[j*diameter + i] = ' ';
			}
		}
	}
	return graphic;
}

Asteroid::Asteroid(const short _x, const short _y, const short _r, const short _vel)
: Entity(ASTEROID, _x, _y, _r*2 + 1, _r*2 + 1, graphic = Asteroid::GetGraphic(_r), 0x08), radius(_r), vel(_vel)
{}
Asteroid::~Asteroid()
{
	delete[] graphic;
}

short Asteroid::getRadius() const
{
	return radius;
}

void Asteroid::think()
{
    position.X += vel;
}