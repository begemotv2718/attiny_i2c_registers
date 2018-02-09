
#include "usiTwiSlave.h"
#include <util/delay.h>

uint8_t data;

int main(void)
{
    usiTwiSlaveInit(0x33);

    _delay_ms(2);
    DBG_SET2();
    _delay_ms(2);
    DBG_CLEAR2();
    _delay_ms(2);
    DBG_SET2();
    _delay_ms(2);
    DBG_CLEAR2();
    DBG_CLEAR1();
    while(1)
    {
    }
}
