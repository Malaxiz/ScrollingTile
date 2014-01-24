#ifndef CRESOURCEMANAGER_H
#define CRESOURCEMANAGER_H

#include <map>
#include <SDL.h>

class CResourceManager
{
public:
    CResourceManager(SDL_PixelFormat* const Format);
    virtual ~CResourceManager();

    SDL_PixelFormat* const Format;

    std::map<int, Uint32> TileTypes;
};

#endif // CRESOURCEMANAGER_H
