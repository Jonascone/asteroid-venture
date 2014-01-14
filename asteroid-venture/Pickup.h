#pragma once
#include "Fighter.h"

class Pickup : public Entity
{
protected:
    bool flashing;
    const time_t disappear_delay;
    time_t flash_delay;

    virtual void pickupFunc(Fighter *) = 0;
    virtual const char* getGraphic() = 0;
public:
    static const int GRAPHIC_SIZE = 3;

    Pickup(const int, const short, const short, const char *, const WORD);
    ~Pickup();
    void think();
    void pickup(Fighter *);
};