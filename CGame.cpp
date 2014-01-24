#include "CGame.h"
#include <iostream>
#include "CSurface.h"
#include "CPlayer.h"
#include "CEntityProperties.h"

CGame::CGame() :
Running(true),
WIDTH(640), HEIGHT(480), BPP(32),
Display_Rect{0, 0, WIDTH, HEIGHT},
LastTime(SDL_GetTicks()), Timer(SDL_GetTicks()),
NS(1000.0f/60.0f), Delta(0), Frames(0), Updates(0)
{
    //ctor
}

CGame::~CGame()
{
    //dtor
}

int CGame::OnExecute()
{
    switch(OnInit())
    {
    case -1: // SDL_Init() error
        std::cerr   << "There was an error initializing SDL: "
                    << SDL_GetError()
                    << "\n";
        return -1;
        break;

    case -2: // Video context error
        std::cerr   << "There was an error creating video context: "
                    << SDL_GetError()
                    << "\n";
        return -1;
        break;
    }

    SDL_Event Event;

    while(Running)
    {
        while(SDL_PollEvent(&Event))
        {
            OnEvent(&Event);
        }

        float Now = SDL_GetTicks();
        Delta += (Now - LastTime) / NS;
        LastTime = Now;

        // This garantees that the gameloop will run at 60hz
        while(Delta >= 0)
        {
            OnLoop();

            Updates++;
            Delta--;
        }

        OnRender();

        Frames++;

        if(SDL_GetTicks() - Timer > 1000)
        {
            Timer += 1000;
            Title.str("");
            Title << "SDL_App | " << Updates << " ups, " << Frames << " frames";
            SDL_WM_SetCaption(Title.str().c_str(), nullptr);
            Updates = 0;
            Frames = 0;
        }

        // Limits fps to 200 fps
        SDL_Delay(5);
    }

    OnCleanup();

    return 0;
}

int CGame::OnInit()
{
    if((SDL_Init(SDL_INIT_EVERYTHING)) == -1)
        return -1;

    if((Surf_Display = SDL_SetVideoMode(WIDTH, HEIGHT, BPP, SDL_HWSURFACE | SDL_DOUBLEBUF)) == nullptr)
        return -2;

    //==

    Player = std::make_shared<CPlayer>(this);
    Player->Body.ColorR = 0xFF;
    Player->Body.ColorG = 0xFF;
    Player->Body.ColorB = 0;

    EntityManager.AddEntity(Player);

    // Test enemys
    EntityManager.AddEntity(this);
    EntityManager.AddEntity(this);
    EntityManager.AddEntity(this);
    EntityManager.AddEntity(this);

    // 0 is player
    // TODO: add a enemy class with FOLLOWPLAYER flag automatically on
    EntityManager.EntityMap[1]->GiveProperty(EntityProperty::FOLLOWPLAYER);
    EntityManager.EntityMap[2]->GiveProperty(EntityProperty::FOLLOWPLAYER);
    EntityManager.EntityMap[3]->GiveProperty(EntityProperty::FOLLOWPLAYER);
    EntityManager.EntityMap[4]->GiveProperty(EntityProperty::FOLLOWPLAYER);

    // TODO: maybe in the level file you can place enemys
    EntityManager.EntityMap[1]->Body.CollisionBox.x = 0;
    EntityManager.EntityMap[2]->Body.CollisionBox.x = 50;
    EntityManager.EntityMap[3]->Body.CollisionBox.x = 100;
    EntityManager.EntityMap[4]->Body.CollisionBox.x = 150;

    //==

    Camera = std::make_shared<CCamera>(this, Player);
    ResourceManager = std::make_shared<CResourceManager>(Surf_Display->format);
    Level = std::make_shared<CLevel>(this);

    Level->RandomTiles(80, 80, 16, 12);

    return 0;
}

void CGame::OnLoop()
{
    for(auto it = EntityManager.EntityMap.begin();
        it != EntityManager.EntityMap.end();
        it++)
    {
        it->second->OnLoop();
    }

    Camera->OnLoop();
}

void CGame::OnRender()
{
    CSurface::RenderRect(&Display_Rect, Surf_Display, 0, 0, 0xFF);

    for(auto it = Level->TileVector.begin();
        it != Level->TileVector.end();
        it++)
    {
        (*it).OnRender(Surf_Display);
    }

    for(auto it = EntityManager.EntityMap.begin();
        it != EntityManager.EntityMap.end();
        it++)
    {
        it->second->OnRender(Surf_Display);
    }

    SDL_Flip(Surf_Display);
}

void CGame::OnCleanup()
{
    SDL_Quit();
}

void CGame::OnEvent(SDL_Event* Event)
{
    switch(Event->type)
    {
    case SDL_KEYDOWN:
        switch(Event->key.keysym.sym)
        {
        case SDLK_ESCAPE:
            Running = false;
            break;

        case SDLK_f:
            Level->RandomTiles(80, 80, 16, 12);
            break;

        case SDLK_n:
            Player->ToggleProperty(EntityProperty::COLLIDABLE);
            break;

        case SDLK_m:
            Player->ToggleProperty(EntityProperty::HIDDEN);
            break;

        default:;
        }
        break;

    case SDL_KEYUP:
        break;

    case SDL_MOUSEMOTION:
        break;

    case SDL_MOUSEBUTTONDOWN:
        break;

    case SDL_MOUSEBUTTONUP:
        break;

    case SDL_QUIT:
        Running = false;
        break;

    default:;
    }
}
