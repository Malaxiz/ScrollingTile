#ifndef CENTITYMANAGER_H
#define CENTITYMANAGER_H

#include <map>
#include <memory>
#include "CEntity.h"

class CGame;

class CEntityManager
{
public:
    CEntityManager();
    ~CEntityManager();

    std::map<int, std::shared_ptr<CEntity>> EntityMap;

    int CurrentID;

    void AddEntity(CGame* Parent);
    void AddEntity(std::shared_ptr<CEntity> Entity);
};

#endif // CENTITYMANAGER_H
