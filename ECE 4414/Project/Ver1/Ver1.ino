// Arduino/My Inports
#include <Player.h>

#define DRUM
#include "ButtonDefs.h"


Player* player;
bool button_pressed_bounce_a = false;
bool button_pressed_bounce_b = false;


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
  if (button_pressed() & BUTTON_HH)
  {
    if (!button_pressed_bounce_a)
    {
      player->play("00000002WAV");
      player->play("00000006WAV");
      player->play("00000011WAV");
    }
    button_pressed_bounce_a = true;
  }
  else
    button_pressed_bounce_a = false;
  
  if(button_pressed() & BUTTON_SNARE)
  {
    if (!button_pressed_bounce_b)
    {
      player->play("00000009WAV");
    }
    button_pressed_bounce_b = true;
  }
  else
    button_pressed_bounce_b = false;

  if (player->has_error())
  {
    Serial.println("Error, re-initializing...");
    delete player;
    player = new Player();
    Serial.println("Done");
  }
}