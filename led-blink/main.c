#include <8051.h>

#include <stdint.h>

void delay_ms(unsigned int ms);

void main(void)
{
    P2 = 0xCC;

    while (1)
    {
        delay_ms(500);

        // press and hold K1 to stop LED blink
        if (P3 & 0b10)
        {
            P2 = ~P2;
        }
    }
}

void delay_ms(unsigned int ms)
{
    unsigned int i, j;

    for (i = 0; i < ms; i++)
        for (j = 0; j < 100; j++);

}
