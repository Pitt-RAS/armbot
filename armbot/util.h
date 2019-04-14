#ifndef UTIL_H
#define UTIL_H

#include <stdint.h>

float normalize(float);

void I2C_read(uint8_t*, uint8_t, uint8_t, uint8_t);
void I2C_setByte(uint8_t, uint8_t, uint8_t);

#endif /* UTIL_H */
