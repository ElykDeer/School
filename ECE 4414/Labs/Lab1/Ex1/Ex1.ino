void MyDelay(unsigned long mSecondsApx);

void blink()
{
  static unsigned char* portB = 0x25;
  *portB |= 0x20;
  MyDelay(50);
  *portB &= 0xdf;
  MyDelay(50);
}

void setup() {
  unsigned char* portDDRB;
  portDDRB = (unsigned char*) 0x24;

  *portDDRB |= 0x20;
}

// the loop routine runs over and over again forever:
void loop() {
  blink();
  MyDelay(900);

  blink();
  blink();
  MyDelay(1800);

  blink();
  blink();
  blink();
  MyDelay(2700);
}

void MyDelay(unsigned long mSecondsApx)
{
  volatile unsigned long i;
  unsigned long endTime = 1000 * mSecondsApx;

  for (i = 0; i < endTime; ++i)
  {   }
}