#include "Entity.h"

void Entity::fillBuffer(const char *_data, const WORD _colour)
{
    for (int j = 0; j < dimensions.Y; ++j) {
        for (int i = 0; i < dimensions.X; ++i) {
            buffer[i + j * dimensions.X].Attributes = _colour;
            buffer[i + j * dimensions.X].Char.AsciiChar = _data[i + j * dimensions.X];
        }
    }
}
WORD Entity::getColour() const
{
    return colour;
}

Entity::Entity(const int _type, const short _x, const short _y, const short _w, const short _h, const char *_data, const WORD _colour)
: Graphic(_x, _y, _w, _h), type(_type), colour(_colour)
{
    fillBuffer(_data, _colour);
}
Entity::~Entity() {}

int Entity::getType() const
{
    return type;
}
void Entity::kill()
{
    should_delete = true;
    should_draw = false;
}