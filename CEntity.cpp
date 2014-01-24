#include "CEntity.h"
#include "CSurface.h"
#include <algorithm>
#include "CGame.h"
#include "CTiles.h"

#include <iostream>

CEntity::CEntity(CGame* Parent) :
ID(-1), Parent(Parent), SkipFrame(false)
{
    GiveProperty(EntityProperty::COLLIDABLE);
}

CEntity::~CEntity()
{
}

void CEntity::ExecuteMisc()
{
}

void CEntity::OnLoop()
{
    // If he's going diagonally
    if(HasProperty(EntityProperty::SLOWED_HALF))
    {
        SkipFrame = !SkipFrame;
    }

    if(HasProperty(EntityProperty::PLAYERCONTROLLED))
    {
        Uint8* KeyState = SDL_GetKeyState(NULL);

        // For slowing down when going diagonal
        int GoingDiagonalRightUp = 0;
        int GoingDiagonalRightDown = 0;
        int GoingDiagonalLeftUp = 0;
        int GoingDiagonalLeftDown = 0;

        int TempVelX = 0, TempVelY = 0;

        if(KeyState['w'])
        {
            GoingDiagonalLeftUp += 1;
            GoingDiagonalRightUp += 1;
            TempVelY -= 5;
        }
        if(KeyState['s'])
        {
            GoingDiagonalLeftDown += 1;
            GoingDiagonalRightDown += 1;
            TempVelY += 5;
        }
        if(KeyState['d'])
        {
            GoingDiagonalRightDown += 1;
            GoingDiagonalRightUp += 1;
            TempVelX += 5;
        }
        if(KeyState['a'])
        {
            GoingDiagonalLeftDown += 1;
            GoingDiagonalLeftUp += 1;
            TempVelX -= 5;
        }

        Body.CollisionBox.x += TempVelX;

        if(HasProperty(EntityProperty::COLLIDABLE))
            if((CheckCol()))
                Body.CollisionBox.x -= TempVelX;

        if((Body.CollisionBox.x < 0) ||
           (Body.CollisionBox.x + Body.CollisionBox.w > Parent->WIDTH + Parent->Camera->CameraOffset.x))
                Body.CollisionBox.x -= TempVelX;

        Body.CollisionBox.y += TempVelY;

        if(HasProperty(EntityProperty::COLLIDABLE))
            if((CheckCol()))
                Body.CollisionBox.y -= TempVelY;

        if((Body.CollisionBox.y < 0) ||
           (Body.CollisionBox.y + Body.CollisionBox.h > Parent->HEIGHT + Parent->Camera->CameraOffset.y))
                Body.CollisionBox.y -= TempVelY;

        // I don't know why but it doesn't look good doing it like this

//        // Check if going diagonal
//        if((GoingDiagonalLeftDown == 2) ||
//           (GoingDiagonalLeftUp == 2) ||
//           (GoingDiagonalRightDown == 2) ||
//           (GoingDiagonalRightUp == 2))
//        {
//            GiveProperty(EntityProperty::SLOWED_HALF);
//        }
//        else
//        {
//            RemoveProperty(EntityProperty::SLOWED_HALF);
//        }

        delete KeyState;
    }

    if(HasProperty(EntityProperty::FOLLOWPLAYER))
    {
        int RelativeX, RelativeY;
        int TempVelX = 0, TempVelY = 0;

        RelativeX = Parent->Player->Body.CollisionBox.x - Body.CollisionBox.x;
        RelativeY = Parent->Player->Body.CollisionBox.y - Body.CollisionBox.y;

        if(RelativeX > 0)
            TempVelX += 1;
        else if(RelativeX < 0)
            TempVelX -= 1;

        if(RelativeY > 0)
            TempVelY += 1;
        else if(RelativeY < 0)
            TempVelY -= 1;

        Body.CollisionBox.x += TempVelX;

        if(HasProperty(EntityProperty::COLLIDABLE))
            if((CheckCol()))
                Body.CollisionBox.x -= TempVelX;

        if((Body.CollisionBox.x < 0) ||
           (Body.CollisionBox.x + Body.CollisionBox.w > Parent->WIDTH + Parent->Camera->CameraOffset.x))
                Body.CollisionBox.x -= TempVelX;

        Body.CollisionBox.y += TempVelY;

        if(HasProperty(EntityProperty::COLLIDABLE))
            if((CheckCol()))
                Body.CollisionBox.y -= TempVelY;

        if((Body.CollisionBox.y < 0) ||
           (Body.CollisionBox.y + Body.CollisionBox.h > Parent->HEIGHT + Parent->Camera->CameraOffset.y))
                Body.CollisionBox.y -= TempVelY;
    }

    if(!SkipFrame)
        ExecuteMisc();
}

void CEntity::OnRender(SDL_Surface* Surf_Destination)
{
    if(!HasProperty(EntityProperty::HIDDEN))
        CSurface::RenderRect(Body.CollisionBox.x - Parent->Camera->CameraOffset.x,
                             Body.CollisionBox.y - Parent->Camera->CameraOffset.y,
                             Body.CollisionBox.w, Body.CollisionBox.h,
                             Surf_Destination,
                             Body.ColorR,
                             Body.ColorG,
                             Body.ColorB);
}

bool CEntity::HasProperty(EntityProperty Property) const
{
    auto search = std::find(Properties.begin(), Properties.end(), Property);

    return search != Properties.end();
}

void CEntity::GiveProperty(EntityProperty Property)
{
    if(!HasProperty(Property))
    {
        Properties.push_back(Property);
    }
}

void CEntity::RemoveProperty(EntityProperty Property)
{
    auto search = std::find(Properties.begin(), Properties.end(), Property);

    if(search != Properties.end())
    {
        Properties.erase(search);
    }
}

void CEntity::ToggleProperty(EntityProperty Property)
{
    if(HasProperty(Property))
        RemoveProperty(Property);
    else
        GiveProperty(Property);
}

bool CEntity::CheckCol()
{
    int LeftA, LeftB;
    int RightA, RightB;
    int TopA, TopB;
    int BottomA, BottomB;

    LeftA = Body.CollisionBox.x;
    RightA = Body.CollisionBox.x + Body.CollisionBox.w;
    TopA = Body.CollisionBox.y;
    BottomA = Body.CollisionBox.y + Body.CollisionBox.h;

    for(auto it = Parent->Level->TileVector.begin();
        it != Parent->Level->TileVector.end();
        it++)
    {
        if((*it).Type >= Tiles::Tile_Center)
        {
            LeftB = (*it).Box.x;
            RightB = (*it).Box.x + (*it).Box.w;
            TopB = (*it).Box.y;
            BottomB = (*it).Box.y + (*it).Box.h;

            if(BottomA <= TopB)
                continue;
            if(TopA >= BottomB)
                continue;
            if(LeftA >= RightB)
                continue;
            if(RightA <= LeftB)
                continue;

            return true;
        }
    }

    for(auto it = Parent->EntityManager.EntityMap.begin();
        it != Parent->EntityManager.EntityMap.end();
        it++)
    {
        if(it->second->HasProperty(EntityProperty::COLLIDABLE))
        {
            if(it->second->ID == ID)
                continue;

            LeftB = it->second->Body.CollisionBox.x;
            RightB = it->second->Body.CollisionBox.x + it->second->Body.CollisionBox.w;
            TopB = it->second->Body.CollisionBox.y;
            BottomB = it->second->Body.CollisionBox.y + it->second->Body.CollisionBox.h;

            if(BottomA <= TopB)
                continue;
            if(TopA >= BottomB)
                continue;
            if(LeftA >= RightB)
                continue;
            if(RightA <= LeftB)
                continue;

            return true;
        }
    }

    return false;
}
