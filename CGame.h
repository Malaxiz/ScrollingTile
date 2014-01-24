#ifndef CGAME_H
#define CGAME_H

#include <SDL.h>
#include <sstream>
#include "CEntityManager.h"
#include "CResourceManager.h"
#include "CCamera.h"
#include "CLevel.h"

class CEntity;

class CGame
{
public:
    CGame();
    ~CGame();

    std::shared_ptr<CEntity> Player;

    CEntityManager EntityManager;
    std::shared_ptr<CResourceManager> ResourceManager;
    std::shared_ptr<CCamera> Camera;
    std::shared_ptr<CLevel> Level;

    bool Running;

    const int WIDTH;
    const int HEIGHT;
    const int BPP;

    SDL_Surface* Surf_Display;
    SDL_Rect Display_Rect;

    int OnExecute();
    int OnInit();
    void OnEvent(SDL_Event* Event);
    void OnLoop();
    void OnRender();
    void OnCleanup();

    //==



    //==

    float LastTime;
    float Timer;
    const float NS;
    float Delta;
    int Frames;
    int Updates;

    std::stringstream Title;
    std::string Intro;
};

#endif // CGAME_H
