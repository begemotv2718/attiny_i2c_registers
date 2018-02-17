
#include "usiTwiSlave.h"
#include <util/delay.h>
#include "softuart.h"

uint8_t data;

int main(void)
{
    softuart_init();
    _delay_ms(1);
    softuart_send('a');
    _delay_ms(1);
    softuart_send('b');
    usiTwiSlaveInit(0x33);

    while(1)
    {
    }
}
