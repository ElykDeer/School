// Arduino/My Inports
#include "Player.h"


Player* player;


void setup()
{
  Serial.begin(115200);

  Serial.println("Initializing new player.");
  player = new Player();

  Serial.print("Loading Sound...");
  if (player->play("00000001WAV"))
    Serial.println("loaded");
  else
    Serial.println("failed");
}


void loop()
{
  if (player->has_error())
  {
    while (1)
    {
      Serial.println("Encountered Error That Cannot Be Recovered From");
      delay(1000);
    }
  }
}