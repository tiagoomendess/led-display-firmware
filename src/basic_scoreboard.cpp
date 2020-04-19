#include "basic_scoreboard.h"
#include "Arduino.h"

#define IR_READ_TICKS 750

#define REMOTE_LONG_PRESS 4294967295
#define REMOTE_PLAY_PAYSE_BTN 16720605
#define REMOTE_BACK_BTN 16712445
#define REMOTE_FWD_BTN 16761405
#define REMOTE_MINUS_BTN 16754775
#define REMOTE_PLUS_BTN 16748655

BasicScoreboard::BasicScoreboard(Screen *screen)
{
    this->screen = screen;
    this->irrecv = new IRrecv(IR_INPUT_PIN);
    this->irrecv->enableIRIn();

    this->homeScore = 0;
    this->awayScore = 0;
    this->seconds = 0;
    this->remoteTick = 0;
    this->timeTick = 0;
    this->timeCounting = false;
    this->pressedPrevious = 0;

    this->screen->fill(255, 255, 255);
}

void BasicScoreboard::handle(int delay)
{
    this->handleReadRemote(delay);
    this->handleTime(delay);

    if (this->timeTick * delay >= 1000) {

        int minutes = this->seconds / 60;
        int localSeconds = minutes < 1 ? this->seconds : this->seconds % 60;

        Serial.print(minutes);
        Serial.print(":");
        Serial.print(localSeconds);
        Serial.print(" | ");
        Serial.print(this->homeScore);
        Serial.print(" - ");
        Serial.print(this->awayScore);
        Serial.println();
    }
}

void BasicScoreboard::handleReadRemote(int delay)
{
    if (this->remoteTick * delay < IR_READ_TICKS)
    {
        this->remoteTick++;
        return;
    }

    decode_results results;

    if (this->irrecv->decode(&results))
    {
        switch (results.value)
        {
        case REMOTE_PLAY_PAYSE_BTN:
            this->timeCounting ? this->timeCounting = false : this->timeCounting = true;
            break;
        case REMOTE_MINUS_BTN:
            this->handleMinusBtn();
            break;
        case REMOTE_PLUS_BTN:
            this->handlePlusBtn();
            break;
        case REMOTE_LONG_PRESS:
            this->handleLongPress();
            break;
        default:
            break;
        }

        this->pressedPrevious = results.value;
        this->irrecv->resume();
    }

    this->remoteTick = 0;
}

void BasicScoreboard::handleTime(int delay)
{
    if (this->timeTick * delay < 1000)
    {
        this->timeTick++;
        return;
    }

    if (this->timeCounting) {
        this->seconds++;
    }
        
    this->timeTick = 0;
}

void BasicScoreboard::handleMinusBtn()
{
    switch (this->pressedPrevious)
    {
    case REMOTE_BACK_BTN:
        this->homeScore > 0 ? this->homeScore-- : this->homeScore;
        break;
    case REMOTE_FWD_BTN:
        this->awayScore > 0 ? this->awayScore-- : this->homeScore;
        break;

    default:
        break;
    }
}

void BasicScoreboard::handlePlusBtn()
{
    switch (this->pressedPrevious)
    {
    case REMOTE_BACK_BTN:
        this->homeScore++;
        break;
    case REMOTE_FWD_BTN:
        this->awayScore++;
        break;
    default:
        break;
    }
}

void BasicScoreboard::handleLongPress()
{
    switch (this->pressedPrevious)
    {
    case REMOTE_PLAY_PAYSE_BTN:
        this->timeCounting = false;
        this->seconds = 0;
        break;
    
    default:
        break;
    }
}
