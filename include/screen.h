#ifndef screen_h
#define screen_h

#include "Adafruit_NeoPixel.h"
#include <limits.h>

class Screen
{
private:
    // The LED strip itself
    Adafruit_NeoPixel *strip;

    // Total number of pixels, cannot be more than 65535
    unsigned short int ledCount;

    // Expect lower number or columns, max is 255 
    unsigned char columns;

    // Contains the location of each LED on the screen
    unsigned short int *ledMap;

    // Builds de the LED map
    unsigned short int *buildLedMap();

public:
    // Constructor
    Screen(unsigned short int ledCount, unsigned short nColumns, unsigned char outputPin);
    Screen();

    // Sets the desired pixel to the specified RGB color
    void setPixel(unsigned short int pixel, unsigned char r, unsigned char g, unsigned char b);

    // Commits the color changes to actually ligth the LEDs
    void refresh();

    // Clears the screen
    void clear();

    //Gets the total LEDS present in the screen
    unsigned short int getLedCount();

    //Gets the total columns in the screen
    unsigned short int getColumns();

    // Fills the screen with one color
    void fill(unsigned char r, unsigned char g, unsigned char b);
};

#endif