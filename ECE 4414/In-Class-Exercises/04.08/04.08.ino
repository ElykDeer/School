unsigned long timer_start = 0;
bool running = false;


void setup()
{
  Serial.begin(115200);
  
  EICRA = 0b1010;  // Falling Edge
  EIMSK = 0x03;  // Enable Both Pins

  DDRD  = 0x00;  // All inputs
  PORTD = 0xff;  // Pins 2 and 3 pulled high

}


// Button 1
ISR(INT0_vect)
{
  if ((!running) && (timer_start == 0))
  {
    Serial.println("My stopwatch is started!");
    timer_start = millis();
    running = true;
  }
  else
  {
    Serial.print("My stopwatch is paused, current elapsed time is: ");
    Serial.println(millis() - timer_start);
    running = false;
  }
}


// Button 2
ISR(INT1_vect)
{
  Serial.print("My stopwatch is reset. Final elapsed time is: ");
  Serial.println(millis() - timer_start);
  running = false;
}


void loop()
{
  if ((!running) && (timer_start == 0))
    timer_start += millis() - timer_start;
}
