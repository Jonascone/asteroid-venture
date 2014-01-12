#pragma once

#include "Graphic.h"

class Entity : public Graphic
{
protected:
    const int type;
    void fillBuffer(const char *, const WORD);
public:
    enum Types { FIGHTER, ASTEROID, LASER, EXPLOSION };

    Entity(const int, const short, const short, const short, const short, const char *, const WORD);
    ~Entity();

    virtual void think() = 0;

    int getType();
};