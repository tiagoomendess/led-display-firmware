#include "screen_diagnostic.h"
#include "Arduino.h"

ScreenDiagnostic::ScreenDiagnostic(Screen *screen)
{
    this->screen = screen;
    this->ledCount = screen->getLedCount();
}

void ScreenDiagnostic::test()
{
    // Fill in Red
    for (unsigned short int i = 0; i < this->ledCount; i++)
    {
        this->screen->setPixel(i, 255, 0, 0);
        this->screen->refresh();
        delay(1);
    }

    // Fill in Green
    for (unsigned short int i = 0; i < this->ledCount; i++)
    {
        this->screen->setPixel(i, 0, 255, 0);
        this->screen->refresh();
        delay(1);
    }

    // Fill in Blue
    for (unsigned short int i = 0; i < this->ledCount; i++)
    {
        this->screen->setPixel(i, 0, 0, 255);
        this->screen->refresh();
        delay(1);
    }
    
    // Clear
    this->screen->clear();

    delay(500);
}
