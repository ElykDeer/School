byte waveform[] = {127, 134, 142, 150, 158, 166, 173, 181, 188, 195, 201, 207, 213, 219, 224,
229, 234, 238, 241, 245, 247, 250, 251, 252, 253, 254, 253, 252, 251, 250, 247, 245, 241, 238,
234, 229, 224, 219, 213, 207, 201, 195, 188, 181, 173, 166, 158, 150, 142, 134, 127, 119, 111,
103, 95, 87, 80, 72, 65, 58, 52, 46, 40, 34, 29, 24, 19, 15, 12, 8, 6, 3, 2, 1, 0, 0, 0, 1, 2, 3, 6, 8, 12,
15, 19, 24, 29, 34, 40, 46, 52, 58, 65, 72, 80, 87, 95, 103, 111, 119};

void log(int expected)
{
  unsigned short *ADCData = (unsigned short *)0x78;
  unsigned short ADCVal = (*ADCData & 0x3FF);
  float fADCVal = ((float)ADCVal)/1023 * 5.0;

  Serial.print(expected);
  Serial.print(" ");
  Serial.println(fADCVal); //Analog voltage measured from ADC
}

void setup()
{
  DDRD = 0xff;  // All output

  // Part 3
  Serial.begin(115200);
  DDRC   = 0;  // Set Pin 0 to be input
  ADMUX  = 0x40;
  ADCSRA = 0xe6;
  ADCSRB = 0x00; // Enable free run
  DIDR0 = 1;  // Disable pin 0
}

void loop()
{
  // Constant 2.5 volts
  PORTD = 127;
  delay(50);
  log(127);
  delay(5000);

  // Waveform
  int i = 0;
  while (1)
  {
    PORTD = waveform[i];
    log(waveform[i]);
    delay(1);
    i = (i+1)%100;
  }
}
