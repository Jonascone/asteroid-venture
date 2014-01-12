#pragma once

#include "Entity.h"
#include <ctime>

class Explosion : public Entity
{
protected:
    time_t disappear_time;
public:
    static const char GRAPHIC[];

    Explosion(const short, const short);
    ~Explosion();

    void think();
};