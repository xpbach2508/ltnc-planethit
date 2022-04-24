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
#include "headers/ui.h"

#define f first
#define s second

using namespace std;


int main(int argc, char* argv[])
{
    SCENE display = menu;
    srand(time(NULL));
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);

    //Initialize things
        //Game
    Planet Earth;
    Ship Nova;
    vector<asteroid> asteroids;
    sizeAsset aster,bgMenu,bgGame,sizeMainButton,titleGame;

    Earth.node.Texture = loadTexture("images/node.png",renderer,Earth.node.Width,Earth.node.Height);
    Earth.Texture = loadTexture("images/earth.png",renderer,Earth.Width,Earth.Height);
    Nova.shipTexture = loadTexture("images/ship.png",renderer,Nova.shipWidth,Nova.shipHeight);
    Nova.BulletTexture = loadTexture("images/bullet.png",renderer,Nova.BulletWidth,Nova.BulletHeight);
    SDL_Texture* asterTexture = loadTexture("images/asteroid.png",renderer,aster.Width,aster.Height);
    Nova.shipWidth /= 1.7f;Nova.shipHeight /= 1.7f;
    Nova.BulletHeight /= 8.0f;Nova.BulletWidth /= 8.0f;

        //UI
    SDL_Texture* backgroundMenu = loadTexture("images/bgMenu.png",renderer,bgMenu.Width,bgMenu.Height);
    SDL_Texture* backgroundGame = loadTexture("images/backgroundGame.png",renderer,bgGame.Width,bgGame.Height);
    SDL_Texture* ButtonTexture = loadTexture("images/Button.png",renderer,sizeMainButton.Width,sizeMainButton.Height);
    SDL_Texture* titleTexture = loadTexture("images/title.png",renderer,titleGame.Width,titleGame.Height);
    SDL_Rect rendertitleRect = {TITLE_POSX,TITLE_POSY,TITLE_WIDTH,TITLE_HEIGHT};
    SDL_Rect renderbgRect = {0,0,bgGame.Width,bgGame.Height};
    SDL_Rect RectPlayButton[BUTTON_MOUSE_TOTAL];
    SDL_Rect RectExitButton[BUTTON_MOUSE_TOTAL];
    Button playButton(PLAY_BUTTON_POSX,PLAY_BUTTON_POSY);
    Button exitButton(EXIT_BUTTON_POSX,EXIT_BUTTON_POSY);
    playButton.setRect(RectPlayButton,0);
    exitButton.setRect(RectExitButton,1);

    //Game manager
    bool quit = false;
    int lastscore = 0;
    Uint32 speedTimer;
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
                        if(playButton.handleEventInside(&e,0)) playButton.currentSprite = BUTTON_MOUSE_OVER;
                        else playButton.currentSprite = BUTTON_MOUSE_OUT;
                        if(exitButton.handleEventInside(&e,0)) exitButton.currentSprite = BUTTON_MOUSE_OVER;
                        else exitButton.currentSprite = BUTTON_MOUSE_OUT;
                        if(playButton.handleEventInside(&e,0)&&e.type == SDL_MOUSEBUTTONDOWN) display = game;
                        if(exitButton.handleEventInside(&e,0)&&e.type == SDL_MOUSEBUTTONDOWN) quit = true;

                    }
                    playButton.render(renderer, &RectPlayButton[playButton.currentSprite], ButtonTexture);
                    exitButton.render(renderer, &RectExitButton[exitButton.currentSprite], ButtonTexture);
                    SDL_RenderCopy(renderer,titleTexture,NULL,&rendertitleRect);
                    speedTimer = SDL_GetTicks();
                    break;
            case game:

                    SDL_RenderCopy(renderer,backgroundGame,&renderbgRect,NULL);
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
                        (asteroids)[i].render(renderer,asterTexture,aster.Width,aster.Height);
                        (asteroids)[i].moving();

                        if(CheckCollision(asteroids[i].asterQuad,Earth.planetQuad))
                            asteroids.erase(asteroids.begin()+i);

                        if(CheckCollision(asteroids[i].asterQuad,Nova.shipQuad))
                        {
                            asteroids.erase(asteroids.begin()+i);
                            //display = menu;
                        }

                        if((asteroids[i].pos.f > 800 || asteroids[i].pos.f < 0) && (asteroids[i].pos.s < 0 || asteroids[i].pos.s > 800))
                        {
                            asteroids.erase(asteroids.begin() + i);
                        }
                    }

                if(lastscore + 1 == Nova.score) Earth.node.Restart(),lastscore = Nova.score;
                Nova.render(renderer,Earth.node.renderQuad,Earth.planetQuad);
                Earth.SetRotation(SDL_GetTicks());
                if(speedTimer + 9000 < SDL_GetTicks()) Earth.speed+=0.0f,speedTimer = SDL_GetTicks();
                Earth.render(renderer);
                break;
        }
        SDL_RenderPresent( renderer );
        }
    quitSDL(window, renderer);
    return 0;
}
