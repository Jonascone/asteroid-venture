#pragma once

#include "Entity.h"

class Asteroid : public Entity
{
protected:
	const short radius;
    const short vel;
	const char* graphic;
public:
	static const char* GetGraphic(short radius);
    Asteroid(const short, const short, const short, const short);
    ~Asteroid();

    void think();

	short getRadius() const;
};