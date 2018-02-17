
#include "usiTwiSlave.h"
#include <util/delay.h>
#include "softuart.h"
#include "adc.h"
#include <avr/wdt.h>

inline void send_hex_digit(uint8_t data)
{
  data = data&0x0f;
  if(data>0x9)
  {
    softuart_send(data-0xa+'a');
  }
  else
  {
    softuart_send(data+'0');
  }
}


int main(void)
{
    uint8_t save_mcusr=MCUSR; 
    wdt_reset();
    MCUSR = 0x00;
    WDTCR |= (1<<WDCE)|(1<<WDE);// watchdog change enable
    WDTCR = 0x00;//watchdog disable
    //wdt_disable();
    
    softuart_init();
    _delay_ms(1);
    softuart_send(' ');

    send_hex_digit(save_mcusr>>4);
    send_hex_digit(save_mcusr&(0x0f));
    softuart_send('h');
    
    
    usiTwiSlaveInit(0x33);
    sei();
    initADC();


    while(1)
    {
      _delay_ms(1);
      //softuart_send('x');
    }
}
