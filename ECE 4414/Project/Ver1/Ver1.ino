// Arduino/My Inports
#include <Player.h>

#define DRUM
#include "ButtonDefs.h"


Player* player;
bool button_pressed_bounce = false;


void setup()
{
  Serial.begin(115200);

  Serial.print("Initializing new player...");
  player = new Player();
  Serial.println("Done");

  DDRC  = 0x00;  // All input
  PORTC = 0xff;  // Hold high
}


uint8_t button_pressed()
{
  return (~PINC & 0b00011111);
}


void loop()
{
  switch (button_pressed())
  {

  case BUTTON_HH:
    if (!button_pressed_bounce)
    {
      Serial.println(BUTTON_HH_NAME);
      player->play(BUTTON_HH_NAME);
    }
    button_pressed_bounce = true;
    break;

  case BUTTON_SNARE:
    if (!button_pressed_bounce)
    {
      Serial.println(BUTTON_SNARE_NAME);
      player->play(BUTTON_SNARE_NAME);
    }
    button_pressed_bounce = true;
    break;

  case BUTTON_INVALID:
  default:
    // Serial.println("Doing nothing");
    button_pressed_bounce = false;
    // delay(100);
    break;

  }

  if (player->has_error())
  {
    while (1)
    {
      Serial.println("Encountered Error That Cannot Be Recovered From");
      delay(1000);
    }
  }
}