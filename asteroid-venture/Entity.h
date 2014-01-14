#pragma once

#include "Graphic.h"

#include <mmsystem.h> // PlaySound
#pragma comment (lib, "winmm.lib")

class Entity : public Graphic
{
protected:
    const int type;
    const WORD colour;

    void fillBuffer(const char *, const WORD);
    WORD getColour() const;
public:
    enum Types { FIGHTER, ASTEROID, LASER, EXPLOSION, PICKUP };

    Entity(const int, const short, const short, const short, const short, const char *, const WORD);
    ~Entity();

    virtual void think() = 0;
    virtual void kill();

    int getType() const;
};