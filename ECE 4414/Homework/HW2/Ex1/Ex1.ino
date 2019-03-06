bool partOne(float in)
{
  if (in > 1)
    return false;

  OCR2B = OCR2A * in;
  return true;
}

void setup()
{
  // Part 2
  DDRD  |= (1<<5);  // Set pin 5 for output
  TCCR2A = 0x23;  //Disconnect pin A, Channel B Fast PWM, Clear On Match
  TCCR2B = 0x0b;
    // 00000 - 1        - 011
    // Junk  - Fast PWM - /64 Prescale
  OCR2A  = 125;   // Timer TOP  <- this makes it 2kHz...combined with the 
  OCR2B  = 128;   // Duty Cycle
}

void loop()
{
  // Part 3...not done
}

void Part45()
{
  ADCSRA = 0xe4;
  ADCSRB = 0x00;
  ADMUX  = 0x45;
  DIDR0  = 0x10;
}