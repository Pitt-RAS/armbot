#include "util.h"

/*float normalize(uint8_t b)
{
    return (float)b / 255.0f;
}*/

float normalize(short b, float min, float max)
{
    return ((float)b - min) / (max - min);
}

float lerp(float a, float b, float f)
{
    return a + f * (b - a);
}