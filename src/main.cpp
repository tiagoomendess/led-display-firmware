#include <Arduino.h>
#include "screen_config.h"
#include "screen.h"
#include "screen_diagnostic.h"
#include "basic_scoreboard.h"

// Manipulate the Screen
Screen *screen;

// To check the screen
ScreenDiagnostic *screenDiagnostic;

// Simple scoreboard
BasicScoreboard *basicScoreboard;

void setup()
{
  Serial.begin(9600);
  delay(2000);
  Serial.println("Setup");
  
  screen = new Screen(LED_COUNT, LED_COLUMNS, LED_DATA_OUT_PIN);
  screenDiagnostic = new ScreenDiagnostic(screen);
  basicScoreboard = new BasicScoreboard(screen);
  //screenDiagnostic->test();
}

void loop()
{
  basicScoreboard->handle(DELAY);
  delay(DELAY);
}
