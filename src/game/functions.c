#include "game/functions.h"

float lerp(float k0, float k1, float t)
{
    return k0 + t * (k1 - k0);
}

float lerp_precise(int k0, int k1, float t)
{
    return (1 - t) * k0 + t * k1;
}