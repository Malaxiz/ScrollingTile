#ifndef CLEVEL_H
#define CLEVEL_H

#include <vector>
#include <string>
#include "CTile.h"

class CGame;

class CLevel
{
public:
    CLevel(CGame* Parent);
    virtual ~CLevel();

    CGame* Parent;

    int TILE_WIDTH, TILE_HEIGHT;
    int MAP_WIDTH, MAP_HEIGHT;

    std::vector<CTile> TileVector;

    // Todo implement
//    bool LoadTiles(std::string Path);

    void RandomTiles(int TILE_WIDTH, int TILE_HEIGHT, int MAP_WIDTH, int MAP_HEIGHT);

    void OnCleanup();
};

#endif // CLEVEL_H
