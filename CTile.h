#ifndef CTILE_H
#define CTILE_H

#include <SDL.h>

class CGame;

class CTile
{
public:
    CTile(int x, int y, int WIDTH, int HEIGHT, int TileType, CGame* Parent);
    virtual ~CTile();

    SDL_Rect Box;

    int Type;

    void OnRender(SDL_Surface* Surf_Destination);

    // I guess I'll need this
//    SDL_Rect GetBox();

    bool CheckCameraCol();

    CGame* Parent;

};

#endif // CTILE_H
