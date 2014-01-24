#ifndef CBODY_H
#define CBODY_H

#include <SDL.h>

class CBody
{
public:
    CBody();
    ~CBody();

    float VelX, VelY;

    // I could probably make a vector that hold rects
    SDL_Rect CollisionBox;

    int ColorR, ColorG, ColorB;

};

#endif // CBODY_H
