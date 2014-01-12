#pragma once

#include "Entity.h"

class Asteroid : public Entity
{
protected:
    const short vel;
public:
    static const char GRAPHIC[];

    Asteroid(const short, const short, const short);
    ~Asteroid();

    void think();
};