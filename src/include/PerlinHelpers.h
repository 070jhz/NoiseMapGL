#ifndef PERLINHELPERS_H
#define PERLINHELPERS_H

#include "MathTypes.h"
#include <math.h>

inline vec2 randomGradient(int ix, int iy, float seed) {
    // No precomputed gradients mean this works for any number of grid coordinates
    const unsigned w = 8 * sizeof(unsigned);
    const unsigned s = w / 2;
    unsigned a = ix + static_cast<int>(seed), b = iy + static_cast<int>(seed);
    a *= 3284157443;

    b ^= a << s | a >> w - s;
    b *= 1911520717;

    a ^= b << s | b >> w - s;
    a *= 2048419325;
    float random = a * (3.14159265 / ~(~0u >> 1)); // in [0, 2*Pi]

    // Create the vector from the angle
    vec2 v;
    v.x = sin(random);
    v.y = cos(random);

    return v;
}

inline float interpolate(float a0, float a1, float w) {
    // cubic curve
    return (a1 - a0) * (3.0f - w*2.0f)*w*w + a0;
}

inline float dotGridGradient(int ix, int iy, float x, float y, float seed) {
    // pseudo-random gradient vector at grid corner
    vec2 grad = randomGradient(ix, iy, seed);

    // distance vector
    float dx = x - (float)ix;
    float dy = y - (float)iy;

    return dx*grad.x + dy*grad.y;
}

inline float perlin(float x, float y, float seed) {
    // grid cell corners
    int x0 = (int)x;
    int y0 = (int)y;
    int x1 = x0 + 1;
    int y1 = y0 + 1;

    // interpolation weights
    float lx = x - static_cast<float>(x0);
    float ly = y - static_cast<float>(y0);

    float n0 = dotGridGradient(x0, y0, x, y, seed);
    float n1 = dotGridGradient(x1, y0, x, y, seed);
    float lx0 = interpolate(n0, n1, lx);

    n0 = dotGridGradient(x0, y1, x, y, seed);
    n1 = dotGridGradient(x1, y1, x, y,seed);
    float lx1= interpolate(n0, n1, lx);

    return interpolate(lx0, lx1, ly);

}


#endif //PERLINHELPERS_H
