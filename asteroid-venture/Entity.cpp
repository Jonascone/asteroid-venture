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

Entity::Entity(const int _type, const short _x, const short _y, const short _w, const short _h, const char *_data, const WORD _colour)
: Graphic(_x, _y, _w, _h), type(_type)
{
    fillBuffer(_data, _colour);
}
Entity::~Entity() {}

int Entity::getType()
{
    return type;
}