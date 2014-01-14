#pragma once
#include "Pickup.h"

class RapidFirePickup : public Pickup
{
protected:
    static const char GRAPHIC[GRAPHIC_SIZE * GRAPHIC_SIZE];

    void pickupFunc(Fighter *);
    const char* getGraphic();
public:
    RapidFirePickup(const short, const short);
    ~RapidFirePickup();
};