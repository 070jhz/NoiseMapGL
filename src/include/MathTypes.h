#ifndef MATHTYPES_H
#define MATHTYPES_H
#include <cmath>

typedef struct {
    float x, y;
} vec2;

typedef struct {
    float x, y, z;
} vec3;

typedef struct {
    vec3 position;
    vec3 normal;
    vec2 texCoords;
} vertex;


#endif //MATHTYPES_H
