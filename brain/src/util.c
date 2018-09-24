#include "util.h"

float normalize(uint8_t b)
{
    return (float)b / 255.0f;
}

float normalize(uint8_t b, float min, float max)
{
    return ((float)b - min) / (max - min);
}
