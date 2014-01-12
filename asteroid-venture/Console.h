#pragma once

#include "graphic.h"
#include <list>

class Console : public Graphic
{
private:
    HANDLE out, in;
    CONSOLE_CURSOR_INFO cursor_info;
    SMALL_RECT sr_dimensions;
    void clear();
protected:
    std::list<const Graphic*> graphics;
public:
    Console(const char *, const short, const short);
    ~Console();

    BOOL *keys;
    void pushGraphic(const Graphic *, const bool = true);
    void eraseGraphic(const Graphic *);
    void clearGraphics();
    void readInput();
    void render();
};