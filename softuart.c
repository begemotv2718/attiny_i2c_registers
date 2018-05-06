#include <avr/io.h>
#include "softuart.h"

//#define delay_half_bit()  delay_us(1000000/(115200*2))
#define PORT_UART PORTB
#define PIN_UART  1
#define DDR_UART DDRB




#define delay_bit() do{asm volatile("nop\nnop\nnop\nnop");}while(0)

  
#define set_on_bit()  do{ PORT_UART &=~(1<<PIN_UART); }while(0) 
#define set_off_bit() do{ PORT_UART |=(1<<PIN_UART);}while(0)

void softuart_init(void){
  DDR_UART |= (1<<PIN_UART);
  set_off_bit();
}

void softuart_send(uint8_t data){
  uint8_t i;
  set_on_bit();
  delay_bit();
  for(i=0;i<8;i++)
  {
    if(data&0x01)
    {
      set_off_bit();
    }
    else
    {
      set_on_bit();
    }
    delay_bit();
    data>>=1;
  }
  set_off_bit();
  delay_bit();
}
