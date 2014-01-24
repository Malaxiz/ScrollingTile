#include "CPlayer.h"
#include "CGame.h"

CPlayer::CPlayer(CGame* Parent) :
CEntity(Parent)
{
    GiveProperty(EntityProperty::PLAYERCONTROLLED);
}

CPlayer::~CPlayer()
{
    //dtor
}
