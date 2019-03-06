// Input  = 2 - High=OutPut_Off
// Output = 3

short *MyADC = 0x78;

void setup()
{
  ADMUX = 0x40;
  // 01-00-0000
  // 5V RJ ADC0
  // Five volt reference, right justified result, use the 0th pin

  ADCSRA = 0xe6;
  // 1-1-1-00-110
  // E S A NI PS64
  // Enable hardware, Start read, Auto trigger, No interrupts, Prescale 64

  ADCSRB = 0x00;
  //00000-000
  //      FrR
  // Something, enable free run

  Serial.begin(115200);
}

void loop()
{
  Serial.println(*MyADC);
  delay(1000);
}