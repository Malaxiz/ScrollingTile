#ifndef CCAMERA_H
#define CCAMERA_H

#include <SDL.h>
#include <memory>

class CEntity;
class CGame;

class CCamera
{
public:
    CCamera(CGame* Parent, std::shared_ptr<CEntity> Target);
    virtual ~CCamera();

    CGame* Parent;
    std::shared_ptr<CEntity> Target;

    SDL_Rect CameraOffset;

    void OnLoop();
};

#endif // CCAMERA_H
