#include <8051.h>

#include <stdint.h>

void delay_ms(unsigned int ms);

// trigger blink by set this flag
int flag_blink_g = 0;

void init_interrupt();

void main(void)
{
    init_interrupt();

    P2 = 0xCC;

    while (1)
    {
        delay_ms(500);

        if (flag_blink_g)
        {
            flag_blink_g = 0;
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


void init_interrupt()
{
    // falling edge triggered
    IT0 = 1;

    // allow INT0
    EX0 = 1;

    // allow interrupt
    EA = 1;
}

#ifdef __SDCC_mcs51
void int0() __interrupt(0)
{
    flag_blink_g = 1;
}
#endif
