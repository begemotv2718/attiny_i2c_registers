//See https://www.marcelpost.com/wiki/index.php/ATtiny85_ADC
//ISR???
#include <avr/io.h>
#include "usiTwiSlave.h"
#include "adc.h"
#include "softuart.h"

void initADC(void)
{
  ADMUX =
            (1 << ADLAR) |     // left shift result
            (0 << REFS1) |     // Sets ref. voltage to VCC
            (0 << REFS0) |     // REFS[1:0]=00
            (0 << MUX3)  |     // use ADC2 for input (PB4)
            (0 << MUX2)  |     // MUX[3:0]=0010
            (1 << MUX1)  |     //
            (0 << MUX0);       // 

  ADCSRA = 
            (1 << ADEN)  |     // Enable ADC 
            (1 << ADATE) |     // Enable auto trigger
            (1 << ADSC)  |     // Start conversion
            (1 << ADIE)  |     // Enable interrupt
            (1 << ADPS2) |     // Clock division factor  
            (0 << ADPS1) |     // is 2^(ADPS[2:0]) 
            (0 << ADPS0) ;      // 
  ADCSRB =
            (0 << ADTS2) |     // Free running triggering
            (0 << ADTS1) |
            (0 << ADTS0) ;
}

volatile uint8_t int_count=0;
ISR(ADC_vect)
{
  cli();
  usiTwiSetRegister(0x03,ADCH);
  usiTwiSetRegister(0x04,ADCL);
  if(int_count>128){
    //softuart_send('D');
    int_count=0;
  }
  else
  {
    int_count++;
  }
  sei();
}
