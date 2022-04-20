#include <iostream>
#include <time.h>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <cmath>


#include "headers/planet.h"
#include "headers/ship.h"
#include "headers/SDL_ultils.h"
#include "headers/asteroids.h"

#define f first
#define s second

using namespace std;
enum SCENE
{
    menu, game
};
SCENE display = menu;
int main(int argc, char* argv[])
{
    srand(time(NULL));
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);

    //Initialize things
    Planet Earth;
    Ship Nova;
    vector<asteroid> asteroids;
    float asterWidth,asterHeight,menuWidth,menuHeight;
    Earth.node.mTexture = loadTexture("images/node.png",renderer,Earth.node.mWidth,Earth.node.mHeight);
    Earth.mTexture = loadTexture("images/earth.png",renderer,Earth.mWidth,Earth.mHeight);
    Nova.shipTexture = loadTexture("images/ship.png",renderer,Nova.shipWidth,Nova.shipHeight);
    Nova.BulletTexture = loadTexture("images/bullet.png",renderer,Nova.BulletWidth,Nova.BulletHeight);
    SDL_Texture* asterTexture = loadTexture("images/asteroid.png",renderer,asterWidth,asterHeight);

    SDL_Texture* backgroundMenu = loadTexture("images/us.png",renderer,menuWidth,menuHeight);

    //Game manager
    bool quit = false;
    int lastscore = 0;
    float speedTimer;
    float speed;
    Uint32 lastShootTime = SDL_GetTicks();
    Uint32 lastspawnAster = lastShootTime;
    SDL_Event e;

        while(!quit)
        {
            SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
            SDL_RenderClear( renderer );
            switch (display)
            {
            case menu:
                    SDL_RenderCopy(renderer,backgroundMenu,NULL,NULL);
                    while(SDL_PollEvent(&e)!=0)
                    {
                        if(e.type==SDL_QUIT)    quit = true;

                        if(e.type==SDL_KEYDOWN&&e.key.keysym.sym==SDLK_ESCAPE) quit = true;

                        if(e.type==SDL_MOUSEBUTTONDOWN||e.type==SDL_MOUSEBUTTONUP) display = game;
                    }
                    break;
            case game:
                    while(SDL_PollEvent(&e)!=0) if(e.type==SDL_QUIT) quit = true;
                    const Uint8 *states = SDL_GetKeyboardState(NULL);
                    if( states[SDL_SCANCODE_A] )
                        {
                            Nova.Move(-1);
                        }
                    else if( states[SDL_SCANCODE_D])
                        {
                            Nova.Move(1);
                        }
                    else if( states[SDL_SCANCODE_W])
                        {
                            Nova.Move(2);
                        }
                    else if( states[SDL_SCANCODE_S])
                        {
                            Nova.Move(-2);
                        }
                    else if(states[SDL_SCANCODE_SPACE]&&SDL_GetTicks()-lastShootTime > 500)
                        {
                            Nova.Shoot();
                            lastShootTime = SDL_GetTicks();
                        }
                    else if(states[SDL_SCANCODE_ESCAPE])
                        {
                            display = menu;
                        }
                    else ;
                //asteroid
                if(SDL_GetTicks() > lastspawnAster + 5000)
                    {
                        lastspawnAster = SDL_GetTicks();
                        int asterAmount = rand()%5;
                        for(int i = 0; i < asterAmount; i++)
                        {
                            asteroid a;
                            (asteroids).push_back(a);
                        }
                    }
                for(int i = 0; i < (asteroids).size(); i++)
                    {
                        (asteroids)[i].render(renderer,asterTexture,asterWidth,asterHeight);
                        (asteroids)[i].moving();

                        if(CheckCollision(asteroids[i].asterQuad,Earth.planetQuad))
                            asteroids.erase(asteroids.begin()+i);

                        if(CheckCollision(asteroids[i].asterQuad,Nova.shipQuad))
                        {
                            asteroids.erase(asteroids.begin()+i);
                            display = menu;
                        }

                        if((asteroids[i].pos.f > 800 || asteroids[i].pos.f < 0) && (asteroids[i].pos.s < 0 || asteroids[i].pos.s > 800))
                        {
                            asteroids.erase(asteroids.begin() + i);
                        }
                    }

                if(lastscore + 1 == Nova.score) Earth.node.Restart(),lastscore = Nova.score;
                Nova.render(renderer,Earth.node.renderQuad,Earth.planetQuad);
                Earth.SetRotation(SDL_GetTicks());
                Earth.render(renderer);
                break;
        }
        SDL_RenderPresent( renderer );
        }
    quitSDL(window, renderer);
    return 0;
}
