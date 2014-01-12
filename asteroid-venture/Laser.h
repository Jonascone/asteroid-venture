#pragma once

#include "Entity.h"

class Laser : public Entity
{
protected:
    const short vel;
public:
    static const char GRAPHIC[];

    Laser(const short, const short, const short);
    ~Laser();

    void think();
};