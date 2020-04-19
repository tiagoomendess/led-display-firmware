#ifndef basic_scoreboard_h
#define basic_scoreboard_h

#define IR_INPUT_PIN 7

#include "screen.h"
#include <IRremote.h>
#include <limits.h>

class BasicScoreboard
{
private:
    Screen *screen;
    IRrecv *irrecv;
    unsigned char homeScore;
    unsigned char awayScore;
    unsigned short int seconds;
    int remoteTick;
    int timeTick;
    bool timeCounting;
    void handleReadRemote(int delay);
    void handleTime(int delay);
    void handleMinusBtn();
    void handlePlusBtn();
    void handleLongPress();
    long pressedPrevious;
public:
    // Constructor
    BasicScoreboard(Screen *screen);
    BasicScoreboard() = default;

    // To be called each tick of the loop
    void handle(int delay);
};
#endif
