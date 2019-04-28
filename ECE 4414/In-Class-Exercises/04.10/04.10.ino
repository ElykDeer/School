//Serial
void UART_Setup()
{
    // 9600 Baud, N, 8, 1
    // Baud Selects
    UBRR0 = 0x0067;

    UCSR0A = 0x00;
    UCSR0B = 0x18;
    // 000-1-1-0-0-0
    // int t r 8 9 t
    // no interupts, enable transmit, receive, high bit select for 9-bit, ninth bit, transmit ninth bit
    UCSR0C = 0x06;
    // 00-00-0-11-0
    // AS Pa S CS ?
    // Asyncronus uart, parity disabled, one Stop bit, Character size Select (8 bits)
}

void UART_run()
{
    char send = 'A';
    while (1)
    {
        UDR0 = send; // "A"
        send += 1;
        delay(10);
        UDR0 = 0x0a; // "\n"
        delay(1000);
    }
}