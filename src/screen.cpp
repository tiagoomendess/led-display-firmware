#include "screen.h"
#include "Arduino.h"

Screen::Screen(unsigned short int ledCount, unsigned short columns, unsigned char outputPin)
{
    this->strip = new Adafruit_NeoPixel(ledCount, outputPin, NEO_GRB + NEO_KHZ800);
    this->strip->clear();
    this->strip->begin();
    this->strip->show();
    this->strip->setBrightness(10);
    this->ledCount = ledCount;
    this->columns = columns;
    this->ledMap = buildLedMap();
}

Screen::Screen()
{
    Serial.println("Default Screen constructor");
}

void Screen::setPixel(unsigned short int pixel, unsigned char r, unsigned char g, unsigned char b)
{
    // Yep for some reason rgb becomes grb in my LED's
    this->strip->setPixelColor(this->ledMap[pixel], this->strip->Color(g, r, b));
}

void Screen::refresh()
{
    this->strip->show();
}

void Screen::clear()
{
    this->strip->clear();
}

unsigned short int Screen::getLedCount()
{
    return this->ledCount;
}

unsigned short int Screen::getColumns()
{
    return this->columns;
}

void Screen::fill(unsigned char r, unsigned char g, unsigned char b)
{
    this->strip->fill(this->strip->Color(g, r, b));
}

unsigned short int *Screen::buildLedMap()
{
    unsigned short int map[this->ledCount] = {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59,
        19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60,
        20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
        39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 89, 88, 87, 86, 85, 84, 83, 82, 81, 80,
        40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99,

        150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109,
        169, 168, 167, 166, 165, 164, 163, 162, 161, 160, 119, 118, 117, 116, 115, 114, 113, 112, 111, 110,
        170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129,
        189, 188, 187, 186, 185, 184, 183, 182, 181, 180, 139, 138, 137, 136, 135, 134, 133, 132, 131, 130,
        190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149};

    unsigned short int *ledMap = (unsigned short int *)malloc(this->ledCount * sizeof(unsigned short int));

    for (unsigned short int i = 0; i < this->ledCount || i >= USHRT_MAX; i++)
    {
        ledMap[i] = map[i];
    }

    return ledMap;
}
