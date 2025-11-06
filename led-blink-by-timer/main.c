#include <stdint.h>

#include <8051.h>

void timer_start(void);
void setup_timer();

uint8_t flag = 0;

void main(void)
{
    setup_timer();
    timer_start();

    P2 = 0xCC;

    while (1)
    {
        if (flag)
        {
            flag -= 1;

            P2 = ~P2;
        }
    }
}

void setup_timer()
{
    // enable timer
    TMOD |= 0x01 ;

    TH0 = 0xFC;
    TL0 = 0x18;
}

void timer_start(void)
{
    EA = 1;     // allow interrupt
    ET0 = 1;    // allow timer0 interrupt
    TR0 = 1;    // enable timer0
}

void timer0() __interrupt(1)
{
    static uint16_t timer_count = 0;

    // 1. restart timer
    setup_timer();

    // 2. set flag
    timer_count++;
    
    if (timer_count > 1000)
    {
        flag += 1;
        timer_count = 0;
    }
}
