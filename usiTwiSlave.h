/********************************************************************************

Header file for the USI TWI Slave driver.

Created by Donald R. Blake
donblake at worldnet.att.net

---------------------------------------------------------------------------------

Created from Atmel source files for Application Note AVR312: Using the USI Module
as an I2C slave.

This program is free software; you can redistribute it and/or modify it under the
terms of the GNU General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE.  See the GNU General Public License for more details.

---------------------------------------------------------------------------------

Change Activity:

    Date       Description
   ------      -------------
  15 Mar 2007  Created.

********************************************************************************/



#ifndef _USI_TWI_SLAVE_H_
#define _USI_TWI_SLAVE_H_



/********************************************************************************

                                    includes

********************************************************************************/

#include <stdbool.h>
#include <stdint.h>

#include <avr/io.h>
#include <avr/interrupt.h>


/********************************************************************************

                                   prototypes

********************************************************************************/

void     usiTwiSlaveInit( uint8_t );
void     usiTwiSetRegister(uint8_t reg, uint8_t value);
uint8_t  usiTwiReadRegister(uint8_t reg);


/********************************************************************************

                           driver buffer definitions

********************************************************************************/

// permitted RX buffer sizes: 1, 2, 4, 8, 16, 32, 64, 128 or 256

#define TWI_REG_BUFFER_SIZE  ( 16 )
#define TWI_REG_BUFFER_MASK  ( TWI_REG_BUFFER_SIZE - 1 )

#if ( TWI_REG_BUFFER_SIZE & TWI_REG_BUFFER_MASK )
#  error TWI RX buffer size is not a power of 2
#endif


/****************************************
 * debug defs
 * **************************************/

#define PORT_DBG  PORTB
#define P_DBG1    PB3
#define P_DBG2    PB4
#define P_DBG0    PB1
#define DDR_DBG_SET()   do {DDRB |= (1<<P_DBG0)|(1<<P_DBG1)|(1<<P_DBG2);} while(0)
#define DBG_SET0() do{PORT_DBG |= (1<<P_DBG0);}while(0)
#define DBG_CLEAR0() do{PORT_DBG &= ~(1<<P_DBG0);} while(0)
#define DBG_SET1() do{PORT_DBG |= (1<<P_DBG1);}while(0)
#define DBG_CLEAR1() do{PORT_DBG &= ~(1<<P_DBG1);}while(0)
#define DBG_SET2() do{PORT_DBG |= (1<<P_DBG2);}while(0)
#define DBG_CLEAR2() do{PORT_DBG &= ~(1<<P_DBG2);}while(0)
#define DBG_WRITE3BIT(x) do{ \
  if((x)&0x01){DBG_SET0();}else{DBG_CLEAR0();} \
  if((x)&(0x02)){DBG_SET1();}else{DBG_CLEAR1();} \
  if((x)&(0x04)){DBG_SET2();}else{DBG_CLEAR2();} }while(0)



#endif  // ifndef _USI_TWI_SLAVE_H_

