#include "CBody.h"

CBody::CBody() :
VelX(0), VelY(0),
CollisionBox{0, 0, 20, 20}, // Temporary
ColorR(0), ColorG(0), ColorB(0)
{
    //ctor
}

CBody::~CBody()
{
    //dtor
}
