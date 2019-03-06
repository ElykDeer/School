
void setup()
{
  DDRD   = (1<<5);  // Set pin 5 for output

  TCCR0A = 0x23;  //Disconnect pin A, Channel B Fast PWM, Clear On Match
    // 00-10   00-11
    //OFF ON   XX-Fast PWM
  TCCR0B = 0x0b;
    // 00000 - 1        - 011
    // Junk  - Fast PWM - /64 Prescale
  OCR0A  = 250;  // Timer TOP
//   OCR0B  = 0;   // Duty Cycle
  
  Serial.begin(115200);
}

void loop()
{
  float aval;
  long x;
  x = millis();
  aval = abs(3 * sin(2 * 3.141592654 * x / 1000));
  delay(1);
  Serial.println(aval);
  
  OCR0B = 255 * (aval/3);
}

// Low Pass Filter:
// 1/RC:
// 1/10k*.000001 = 
//                 1/0.01 = 100

// PWM Frequency:
//   16MHz/64 Prescale = 250KHz
//   250KHz/250 ticks  = 1KHz
// Overall signal = ??

// About 1Hz decoded output frequency?