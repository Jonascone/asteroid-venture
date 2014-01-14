#pragma once

#include "Entity.h"
#include <ctime>

class Explosion : public Entity
{
protected:
    const time_t disappear_time;
    static const char GRAPHIC[];
public:
    Explosion(const short, const short);
    ~Explosion();

    void think();
};