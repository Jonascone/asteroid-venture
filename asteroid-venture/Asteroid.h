#pragma once

#include "Entity.h"

class Asteroid : public Entity
{
protected:
    const short vel;
    static const char GRAPHIC[];
public:
    Asteroid(const short, const short, const short);
    ~Asteroid();

    void think();
};