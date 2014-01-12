#pragma once

#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>

class Graphic
{
protected:
    COORD position, dimensions;
    CHAR_INFO *buffer;
    bool should_delete, should_draw;

    void drawGraphic(const Graphic &);
public:
    Graphic(const short, const short, const short, const short);
    Graphic(const short, const short);
    virtual ~Graphic();
    bool shouldDelete() const;
    bool shouldDraw() const;
    void setDelete(const bool);
    void setDraw(const bool);
    bool inScreen(const Graphic &_graphic);
    COORD getCentre() const;
    void setPos(const short, const short);
};