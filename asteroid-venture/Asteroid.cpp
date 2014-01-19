#pragma once

#include "Asteroid.h"
#include <math.h>

const char* Asteroid::GetGraphic(short radius) {
	auto diameter = radius * 2;
	auto graphic = new char[diameter*diameter];
	for (short i = 0; i < diameter; i++) {
		for (short j = 0; j < diameter; j++) {
			short xdist = i - radius;
			short ydist = j - radius;

			if (xdist*xdist + ydist*ydist < radius*radius) {
				graphic[j*diameter + i] = '0';
			} else {
				graphic[j*diameter + i] = ' ';
			}
		}
	}
	return graphic;
}

Asteroid::Asteroid(const short _x, const short _y, const short _r, const short _vel)
: Entity(ASTEROID, _x, _y, _r*2, _r*2, Asteroid::GetGraphic(_r), 0x08), vel(_vel)
{}
Asteroid::~Asteroid()
{}

void Asteroid::think()
{
    position.X += vel;
}