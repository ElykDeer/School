
void init()
{
    DDRD   = 0xf0;  // Set PORT d 0-3 as inputs, 4-7 as outputs
    TCCR0A = 0x23;//Disconnect pin A, Channel B Fast PWM, Clear On Match
    // 00-10   00-11
    //CHA CHB  XX Wave Gen

    TCCR0B = 0x0b; // Clcok prescale to /64, PWM setup stuff
    OCR0A  = 250;  // Sets top of timer
    OCR0B  = 62;   // 
}

