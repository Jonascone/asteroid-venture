#pragma once
#include "Pickup.h"

class NukePickup : public Pickup
{
protected:
    static const char GRAPHIC[GRAPHIC_SIZE * GRAPHIC_SIZE];

    void pickupFunc(Fighter *);
    const char* getGraphic();
public:
    NukePickup(const short, const short);
    ~NukePickup();
};