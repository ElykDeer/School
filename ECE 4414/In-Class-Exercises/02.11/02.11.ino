// Input  = 2 - High=OutPut_Off
// Output = 3

void setup()
{
  DDRD  &= ~(1<<PORTD2);  // Direction=Input
  PORTD |=  (1<<PORTD2);  // Hold-High
  DDRD  |=  (1<<PORTD3);  // Direction=Output

  // DDRD  = 0x08;
  // PORTD = 0x04;
}

void loop()
{
  if ((PIND & (1<<PORTD2)) == 0)
  {
    PORTD |= (1<<PORTD3);  // Turn Led On
  }
  else
  {
    PORTD &= ~(1<<PORTD3);  // Turn Led Off
  }
  delay(100);
}