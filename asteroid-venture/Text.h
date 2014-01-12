#pragma once

#include "graphic.h"

class Text : public Graphic
{
private:
    static const int LENGTH = 128;
    void nullText();
    void newBuffer(const int);
    void deleteBuffer();
    void updateText();
protected:
    WORD colour;
    int len;
    char *text;
public:
    Text(const short, const short, WORD _colour = 0x0F, const char * = nullptr);
    ~Text();
    void setText(const char *, ...);
    void setColour(const WORD);
};