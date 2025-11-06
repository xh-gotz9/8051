#include <8051.h>

#include "seg.h"

void setup_timer();
void timer_start(void);

int main(void)
{
    number = 0;

    setup_timer();
    timer_start();

    set_seg_number(number);

    while (1)
    {
        seg_show();
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
    number++;
    set_seg_number(number);
}
