#include "CResourceManager.h"
#include "CTiles.h"

CResourceManager::CResourceManager(SDL_PixelFormat* const Format) :
Format(Format)
{
    TileTypes[Tiles::Tile_Red] = SDL_MapRGB(Format, 0xFF, 0, 0);
    TileTypes[Tiles::Tile_Green] = SDL_MapRGB(Format, 0, 0xFF, 0);
    TileTypes[Tiles::Tile_Blue] = SDL_MapRGB(Format, 0, 0, 0xFF);
    TileTypes[Tiles::Tile_Center] = SDL_MapRGB(Format, 0, 0, 0);
}

CResourceManager::~CResourceManager()
{
    //dtor
}
