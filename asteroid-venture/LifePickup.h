#pragma once
#include "Pickup.h"

class LifePickup : public Pickup
{
protected:
    static const char GRAPHIC[GRAPHIC_SIZE * GRAPHIC_SIZE];
    
    void pickupFunc(Fighter *);
    const char* getGraphic();
public:
    LifePickup(const short, const short);
    ~LifePickup();
};