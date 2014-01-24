#ifndef CPLAYER_H
#define CPLAYER_H

#include "CEntity.h"

class CPlayer : public CEntity
{
public:
    CPlayer(CGame* Parent);
    virtual ~CPlayer();

};

#endif // CPLAYER_H
