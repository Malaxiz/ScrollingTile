#include "CLevel.h"
#include <cstdlib>
#include "CGame.h"

CLevel::CLevel(CGame* Parent) :
Parent(Parent),
TILE_WIDTH(0), TILE_HEIGHT(0),
MAP_WIDTH(0), MAP_HEIGHT(0)
{
    srand(SDL_GetTicks());
}

CLevel::~CLevel()
{
    //dtor
}

void CLevel::OnCleanup()
{
    TileVector.clear();
}

void CLevel::RandomTiles(int TILE_WIDTH, int TILE_HEIGHT, int MAP_WIDTH, int MAP_HEIGHT)
{
    this->TILE_WIDTH = TILE_WIDTH;
    this->TILE_HEIGHT = TILE_HEIGHT;
    this->MAP_WIDTH = MAP_WIDTH;
    this->MAP_HEIGHT = MAP_HEIGHT;

    OnCleanup();

    int x = 0, y = 0;

    for(int t = 0; t < MAP_WIDTH * MAP_HEIGHT; t++)
    {
        int TileType = rand() % 4;

        CTile Tile(x, y, TILE_WIDTH, TILE_HEIGHT, TileType, Parent);

        TileVector.push_back(Tile);

        x += TILE_WIDTH;

        if(x >= MAP_WIDTH * TILE_WIDTH)
        {
            x = 0;

            y += TILE_HEIGHT;
        }
    }
}
