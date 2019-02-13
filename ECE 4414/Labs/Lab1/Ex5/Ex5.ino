void NewDelay (unsigned long mSecondsApx);

void setup()
{
    unsigned char *portDDRB;
    portDDRB = (unsigned char *) 0x24;
    *portDDRB |= 0x20;
}

void loop ()
{
    unsigned char *portB;
    portB = (unsigned char *) 0x25;
    *portB |= 0x20;
    NewDelay (100);
    *portB &= 0xDF;
    NewDelay (100);
}

void NewDelay (unsigned long mSecondsApx)
{
    volatile unsigned long i;
    // unsigned char j;
    // unsigned long k;

    unsigned long endTime = 1000 * mSecondsApx;  // Need to lengthen time

    for (i = 0; i < endTime; i++)
    {
        // Makes no sense why you would want to impliment this
        // j = 10;
        // do
        // {
        //     j = j - i;
        //     k = i/j;
        // }
        
        // while (k>0);
    }
}
