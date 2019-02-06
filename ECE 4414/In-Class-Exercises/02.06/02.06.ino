// unsigned char* DReg=0x24;
// unsigned char* PReg=0x25;

void setup()
{
//   *DReg |= 0x20;  // 0b0010-0000
  DDRB |= (1<<PORTB5);  // 0b0010-0000
}

void loop()
{
//   *PReg ^= 0x20;
  PORTB &= ~(1<<PORTB5);  // On
  delay(900);
  PORTB |= (1<<PORTB5);  // Off
  delay(100);
}