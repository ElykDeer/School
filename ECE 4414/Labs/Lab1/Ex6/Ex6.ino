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
    unsigned char j = 0;
    unsigned long endTime = 1000 * mSecondsApx;  // Need to lengthen time

    i = 0;
    while (j == 0)  // Needs to be check not assignment (was "=")
    {
        i++;
        if (i == endTime)  // Also needs to be check
        {
           j = 1;
        }
    }
}
