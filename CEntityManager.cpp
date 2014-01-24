#include "CEntityManager.h"
#include "CEntityProperties.h"

CEntityManager::CEntityManager() :
CurrentID(0)
{
    //ctor
}

CEntityManager::~CEntityManager()
{
    //dtor
}

void CEntityManager::AddEntity(CGame* Parent)
{
    EntityMap[CurrentID] = std::make_shared<CEntity>(Parent);

    // Give default properties
    EntityMap[CurrentID]->GiveProperty(EntityProperty::COLLIDABLE);

    EntityMap[CurrentID]->ID = CurrentID;

    CurrentID++;
}

void CEntityManager::AddEntity(std::shared_ptr<CEntity> Entity)
{
    EntityMap[CurrentID] = Entity;

    // Give default properties
    EntityMap[CurrentID]->GiveProperty(EntityProperty::COLLIDABLE);

    EntityMap[CurrentID]->ID = CurrentID;

    CurrentID++;
}
