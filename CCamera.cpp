#include "CCamera.h"
#include "CGame.h"
#include "CEntity.h"

CCamera::CCamera(CGame* Parent, std::shared_ptr<CEntity> Target) :
Parent(Parent), Target(Target),
CameraOffset{0, 0, (Uint16)Parent->WIDTH, (Uint16)Parent->HEIGHT} // Using (Uint16) to remove warnings
{
}

CCamera::~CCamera()
{
}

void CCamera::OnLoop()
{
    CameraOffset.x = (Target->Body.CollisionBox.x + Target->Body.CollisionBox.w / 2) - Parent->WIDTH / 2;
    CameraOffset.y = (Target->Body.CollisionBox.y + Target->Body.CollisionBox.h / 2) - Parent->HEIGHT / 2;

    if(CameraOffset.x < 0)
    {
        CameraOffset.x = 0;
    }
    if(CameraOffset.y < 0)
    {
        CameraOffset.y = 0;
    }
    if(CameraOffset.x > Parent->Level->MAP_WIDTH * Parent->Level->TILE_WIDTH - CameraOffset.w)
    {
        CameraOffset.x = Parent->Level->MAP_WIDTH * Parent->Level->TILE_WIDTH - CameraOffset.w;
    }
    if(CameraOffset.y > Parent->Level->MAP_HEIGHT * Parent->Level->TILE_HEIGHT - CameraOffset.h)
    {
        CameraOffset.y = Parent->Level->MAP_HEIGHT * Parent->Level->TILE_HEIGHT - CameraOffset.h;
    }
}
