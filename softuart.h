#ifndef SOFTUART_H
#define SOFTUART_H
#include <stdint.h>
void softuart_init(void);
void softuart_send(uint8_t data);
#endif
