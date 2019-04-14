#include "util.h"
#include <Wire.h>

float normalize(float val)
{
	return val / 1023.0f;
}

void I2C_read(uint8_t* buf, uint8_t reg, uint8_t len, uint8_t addr)
{
    Wire.beginTransmission(addr);
    Wire.write(reg);
    Wire.endTransmission();
    
    Wire.requestFrom(addr, len);
    uint8_t index = 0;
    while (Wire.available())
    {
        buf[index++] = Wire.read();
    }
}

void I2C_setByte(uint8_t data, uint8_t reg, uint8_t addr)
{
    Wire.beginTransmission(addr);
    Wire.write(reg);
    Wire.write(data);
    Wire.endTransmission();
}
