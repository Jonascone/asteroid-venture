#pragma once

#include "Entity.h"

class Asteroid : public Entity
{
protected:
    const short vel;
    static const char GRAPHIC[];
public:
	static const char* GetGraphic(short radius);
    Asteroid(const short, const short, const short, const short);
    ~Asteroid();

    void think();
};