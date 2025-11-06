#include <8051.h>

#include <stdint.h>

#define SMG_A_DP_PORT P0

int16_t number = 0;


uint8_t current_slot = 0;
uint8_t seg_slots[4] = {0x0, 0x0, 0x0, 0x0};

enum gsmg_code {
    GSMG_EMPTY = 0x0,
    GSMG_0 = 0x3F,
    GSMG_1 = 0x06,
    GSMG_2 = 0x5B,
    GSMG_3 = 0x4F,
    GSMG_4 = 0x66,
    GSMG_5 = 0x6D,
    GSMG_6 = 0x7D,
    GSMG_7 = 0x07,
    GSMG_8 = 0x7F,
    GSMG_9 = 0x6F,
    GSMG_A = 0x77,
    GSMG_B = 0x7C,
    GSMG_C = 0x39,
    GSMG_D = 0x5E,
    GSMG_E = 0x79,
    GSMG_F = 0x71
};

uint8_t gsmg_code[] = {
    0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07,
    0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71
};

__sbit __at(0xA2) SLOT_NUM_BIT_0;
__sbit __at(0xA3) SLOT_NUM_BIT_1;
__sbit __at(0xA4) SLOT_NUM_BIT_2;

void set_seg_number(uint16_t value)
{
    if (value > 9999)
    {
        // ERROR
        return;
    }

    uint16_t v = value;

    for (int i = 0; i < 4; i++)
    {
        if(v == 0)
        {
            seg_slots[i] = GSMG_EMPTY;
            continue;
        }

        seg_slots[i] = gsmg_code[v % 10];
        v = v / 10;
    }    
}

void set_slot(uint8_t i)
{
    SLOT_NUM_BIT_0 = i & 0x1;
    SLOT_NUM_BIT_1 = i>>1 & 0x1;
    SLOT_NUM_BIT_2 = i>>2 & 0x1;
}

void seg_show()
{
    SMG_A_DP_PORT = GSMG_EMPTY;

    // set slot selection
    set_slot(current_slot);

    SMG_A_DP_PORT = seg_slots[current_slot];

    current_slot = (current_slot + 1) % 4;
}
