#include <Wire.h>

void setup()
{
  // Question 1.a: Get the values 
  Serial.begin(115200);
  // Wire.begin();

  // Serial.print("UCSR0A: "); Serial.println(UCSR0A, BIN);
  // Serial.print("UCSR0B: "); Serial.println(UCSR0B, BIN);
  // Serial.print("UCSR0C: "); Serial.println(UCSR0C, BIN);
  // Serial.print("UBRR0: ");  Serial.println((int)UBRR0, BIN);
  
  // Serial.print("TWBR: ");   Serial.println(TWBR, BIN);
  // Serial.print("TWCR: ");   Serial.println(TWCR, BIN);
  // Serial.print("TWSR: ");   Serial.println(TWSR, BIN);
  // Serial.print("TWAR: ");   Serial.println(TWAR, BIN);
  
  // Question 1.b: Explain what they mean
  // UCSR0A: 00000010
    // Bit 7 (0): RXC0  - 
    // Bit 6 (0): TXC0  - 
    // Bit 5 (0): UDREO - 
    // Bit 4 (0): FEO   - Frame Error - Set when things go bad (out of sync)
    // Bit 3 (0): DORO  - Data over run - also set when things go bad (not processing data quick enough)
    // Bit 2 (0): UPEO  - Parity error - also set when things go bad (parity is calculated to be different than what was received)
    // Bit 1 (1): U2XO  - Double transmission speed (enabled - asyncronus operation/divides baud rate by 8 instead of 16)
    // Bit 0 (0): MPCMO - MPCMO Multi-processor communication mode (disabled - transmit mode unaffected, does not ignore incoming bytes that don't have address info)

  // UCSR0B: 10111000
    // Bit 7 (1): RXCIEO - 
    // Bit 6 (0): TXCIEO - 
    // Bit 5 (1): UDRIEO - 
    // Bit 4 (1): RXENO  - Receiver enable (enabled)
    // Bit 3 (1): TXENO  - Transmitter enable (enabled)
    // Bit 2 (0): UCSZO2 - Character size
    // Bit 1 (0): RXB8O  - Receive data bit 8 (disabled)
    // Bit 0 (0): TXB8O  - Transmit data bit 8 (disabled)

  // UCSR0C: 00000110
    // Bit 7/6 (00): UMSEL01/UMSEL00 - Async USART
    // Bit 5/4 (00): UPM01/UPM00     - Parity Disabled
    // Bit 3 (0):    USBS0           - 
    // Bit 2/1 (11): UCSZ01/UCSZ00   - Combined with UCSZ02: 011 (8-bit characters) 
    // Bit 0 (0):    UCPOLO          - Clock polarity (transmit on rising edge, receive on falling edge)
  
  // UBRR0:  00010000
    // Baud rate bites - baud rate is 115200

  // TWBR:   01001000
  // TWI Bit Rate : It sets the bitrate to 16+2(TWI)(PRESCALER) where here TWI is 0x48

  // TWCR:   01000101
  // TWI Control Register :
    // Bit 7 (1): TWINT
    // Bit 6 (1): TWEA  - Awk bit enabled
    // Bit 5 (0): TWSTA - Start Condition Bit (Disabled)
    // Bit 4 (0): TWSTO - Stop Condition Bit (Disabled)
    // Bit 3 (0): TWWC  - Write collision flag (set writing to TWDR when TWINT is low)
    // Bit 2 (1): TWEN  - Enables the interface (enabled)
    // Bit 1 (0): -------
    // Bit 0 (1): TWIE  - 

  // TWSR:   11111000
    // Bit 7 (1): TWS7  - Status bit 4
    // Bit 6 (1): TWS6  - Status bit 3
    // Bit 5 (1): TWS5  - Status bit 2
    // Bit 4 (1): TWS4  - Status bit 1
    // Bit 3 (1): TWS3  - Status bit 0
    // Bit 2 (0): ------- 
    // Bit 1 (0): TWPS1 - Pre-Scaler Bit 1
    // Bit 0 (0): TWPS0 - Pre-Scaler Bit 0 (Total prescale = 0)

  // TWAR:   11111110 - Slave address (0xef)
    // Bit 0 (0): TWGCE - General Call Recognition Bit (whether it responds to addess 0, disabled)
}

void setupUART()
{
  // Question 2/3:
  UCSR0A = 0b00000000;
  UCSR0B = 0b10110000;
  UCSR0C = 0b00000110;
  UBRR0  = 0b00001000;
}

void problem4()
{
  if (UCSR0A & 0x80)
    Serial.print((char)UDR0);
}

void loop()
{
  problem4();
}
