#ifndef CENTITY_H
#define CENTITY_H

#include <SDL.h>
#include "CBody.h"
#include <vector>
#include "CEntityProperties.h"

class CGame;

class CEntity
{
public:
    CEntity(CGame* Parent);
    virtual ~CEntity();

    int ID;

    CBody Body;

    CGame* Parent;

    std::vector<EntityProperty> Properties;

    bool HasProperty(EntityProperty Property) const;

    void GiveProperty(EntityProperty Property);

    void RemoveProperty(EntityProperty Property);

    void ToggleProperty(EntityProperty Property);

    void OnLoop();

    virtual void ExecuteMisc();

    void OnRender(SDL_Surface* Surf_Destination);

    bool CheckCol();

    bool SkipFrame;

};

#endif // CENTITY_H
