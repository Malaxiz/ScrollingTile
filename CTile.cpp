#include "CTile.h"
#include "CGame.h"
#include "CSurface.h"
#include "CResourceManager.h"

CTile::CTile(int x, int y, int WIDTH, int HEIGHT, int TileType, CGame* Parent) :
Box{(Sint16)x, (Sint16)y, (Uint16)WIDTH, (Uint16)HEIGHT},
Type(TileType), Parent(Parent)
{
    //ctor
}

CTile::~CTile()
{
    //dtor
}

void CTile::OnRender(SDL_Surface* Surf_Destination)
{
    if(CheckCameraCol())
    {
        SDL_Rect Offset;

        Offset.x = Box.x - Parent->Camera->CameraOffset.x;
        Offset.y = Box.y - Parent->Camera->CameraOffset.y;
        Offset.w = Box.w;
        Offset.h = Box.h;

        CSurface::RenderRect(&Offset, Surf_Destination, Parent->ResourceManager->TileTypes[Type]);
    }
}

bool CTile::CheckCameraCol()
{
    int LeftA, LeftB;
    int RightA, RightB;
    int TopA, TopB;
    int BottomA, BottomB;

    LeftA = Box.x;
    RightA = Box.x + Box.w;
    TopA = Box.y;
    BottomA = Box.y + Box.h;

    LeftB = Parent->Camera->CameraOffset.x;
    RightB = Parent->Camera->CameraOffset.x + Parent->Camera->CameraOffset.w;
    TopB = Parent->Camera->CameraOffset.y;
    BottomB = Parent->Camera->CameraOffset.y + Parent->Camera->CameraOffset.h;

    // Use this if you want to see how it looks outside the camera..
    // .. by making the camera collision box smaller

//    LeftB = Parent->Camera->CameraOffset.x + 40;
//    RightB = Parent->Camera->CameraOffset.x + Parent->Camera->CameraOffset.w  - 40;
//    TopB = Parent->Camera->CameraOffset.y  + 40;
//    BottomB = Parent->Camera->CameraOffset.y + Parent->Camera->CameraOffset.h  - 40;

    if(BottomA <= TopB)
        return false;
    if(TopA >= BottomB)
        return false;
    if(LeftA >= RightB)
        return false;
    if(RightA <= LeftB)
        return false;

    return true;
}
