#include "Text.h"
#include <cstdio>

void Text::nullText() // Nullify string.
{
    for (int i = 0; i < LENGTH; ++i) {
        text[i] = '\0';
    }
}
void Text::newBuffer(const int _len) // Write a new buffer with given string length.
{
    len = _len;
    delete[] buffer;
    buffer = new CHAR_INFO[len]();
    dimensions.X = len, dimensions.Y = 1;
}
void Text::deleteBuffer()
{
    len = 0;
    delete[] buffer;
    dimensions.X = dimensions.Y = 0;
}
void Text::updateText()
{
    for (int i = 0; i < len; ++i) {
        buffer[i].Attributes = colour;
        buffer[i].Char.AsciiChar = text[i];
    }
}

Text::Text(const short _x, const short _y, WORD _colour, const char *_text)
: Graphic(_x, _y), len(0), colour(_colour), text(new char[LENGTH]())
{
    setText(_text);
}
Text::~Text()
{
    delete[] text;
}
void Text::setText(const char *_text, ...) // Set text according to argument list.
{
    if (!_text) {
        deleteBuffer();
        return;
    }
    nullText();

    va_list vl;
    va_start(vl, _text);
    vsnprintf(text, LENGTH, _text, vl);
    va_end(vl);

    newBuffer(strlen(text));
    updateText();
}
void Text::setColour(const WORD _colour)
{
    colour = _colour;
    updateText();
}
