#include "wrist.h"
#include "util.h"
#include <Wire.h>

Wrist::Wrist()
{

}

Wrist::~Wrist()
{
    
}

void Wrist::attach(int c, int d)
{
    clk = c;
    data = d;
    
    I2C_setByte(0x06,29,0x68);
    I2C_setByte(0x06,26,0x68);
    I2C_setByte(0x10,27,0x68);
    I2C_setByte(0x08,28,0x68);
    I2C_setByte(0x02,0x37,0x68);
    I2C_setByte(0x16,0x0A,0x0C);
}

void Wrist::poll()
{
    Serial.print("poll: ");
    uint8_t buf[20];
    I2C_read(buf,0x3B,14,0x68);

    int16_t ax = -(buf[0] << 8 | buf[1]);
    int16_t ay = -(buf[2] << 8 | buf[3]);
    int16_t az =  (buf[4] << 8 | buf[5]);

    int16_t gx = -(buf[8] << 8 | buf[9]);
    int16_t gy = -(buf[10] << 8 | buf[11]);
    int16_t gz =  (buf[12] << 8 | buf[13]);

    //Serial.print("ax: ");
    //Serial.print(ax);
    Serial.print("\tay: ");
    Serial.print(ay);
    //Serial.print("\taz: ");
    //Serial.print(az);
    //Serial.print("\t\tgx: ");
    //Serial.print(gx);
    //Serial.print("\t\tgy: ");
    //Serial.print(gy);
    //Serial.print("\t\tgz: ");
    //Serial.print(gz);

    Serial.println();

    delay(10);    
}
