
void setup()
{
  DDRD  |= (1<<5);  // Set pin 5 for output

  TCCR0A = 0x23;  //Disconnect pin A, Channel B Fast PWM, Clear On Match
    // 00-10   00-11
    //OFF ON   XX-Fast PWM
  TCCR0B = 0x0b;
    // 00000 - 1        - 011
    // Junk  - Fast PWM - /64 Prescale
  OCR0A  = 250;  // Timer TOP
//   OCR0B  = 0;   // Duty Cycle
  
  Serial.begin(115200);

  // Part 6 stuff:
  DDRC   = 0;  // Set Pin 0 to be input

  ADMUX  = 0x40;
  // 01  - 0             - 0 - 0000
  // VCC - Right Justify - X - ADC0

  ADCSRA = 0xe6;
  // 1-1-1-00-110
  // E S A NI PS64
  // Enable hardware, Start read, Auto trigger, No interrupts, Prescale 64

  ADCSRB = 0x00; // Enable free run

  DIDR0 = 1;  // Disable pin 0
}

void loop()
{
  float aval;
  long x;
  x = millis();
  aval = abs(3 * sin(2 * 3.141592654 * x / 1000));
  OCR0B = 255 * (aval/3.0);

  delay(1);

  unsigned short *ADCData;
  unsigned short ADCVal;
  ADCData=(unsigned short *)0x78;
  ADCVal=(*ADCData & 0x3FF);

  float fADCVal;
  fADCVal=((float)ADCVal)/1023 * 3;

  Serial.print(aval);
  Serial.print(" ");
  Serial.println(fADCVal); //Analog voltage measured from ADC
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