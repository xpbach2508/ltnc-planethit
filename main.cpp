#include <iostream>
#include <time.h>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>


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
    sizeAsset aster, sHealth;
    //Sounds
    Mix_Music* gameMusic = nullptr;
    Mix_Music* menuMusic = nullptr;
    Mix_Chunk* Click = nullptr;
    Mix_Chunk* Shoot = nullptr;
    Mix_Chunk* Over = nullptr;
    Mix_Chunk* get_hit = nullptr;
    Mix_Chunk* Start = nullptr;
    Mix_Chunk* point = nullptr;
    Mix_Chunk* bulletExplode = nullptr;

    gameMusic = Mix_LoadMUS("sounds/background_game.wav");
    menuMusic = Mix_LoadMUS("sounds/background_menu.wav");
    Click = Mix_LoadWAV("sounds/click.wav");
    Shoot = Mix_LoadWAV("sounds/shoot.wav");
    Over = Mix_LoadWAV("sounds/game_over.wav");
    get_hit = Mix_LoadWAV("sounds/get_hit.wav");
    Start = Mix_LoadWAV("sounds/start.wav");
    point = Mix_LoadWAV("sounds/point.wav");
    bulletExplode = Mix_LoadWAV("sounds/explode.wav");

    Earth.node.Texture = loadTexture("images/node.png",renderer);
    Earth.Texture = loadTexture("images/earth.png",renderer);
    Nova.shipTexture = loadTexture("images/ship.png",renderer);
    Nova.shipHealthTexture = loadTexture("images/health.png",renderer);
    Nova.BulletTexture = loadTexture("images/bullet.png",renderer);
    SDL_Texture* asterTexture = loadTexture("images/asteroid.png",renderer);

//    Nova.shipWidth /= 1.7f;Nova.shipHeight /= 1.7f;
//    Nova.BulletHeight /= 8.0f;Nova.BulletWidth /= 8.0f;
//    Earth.Width *= 1.5f;Earth.Height *= 1.5f;
//    Earth.node.Width /= 2.38f;Earth.node.Height /= 2.38f;
//    cout << Earth.Width << " " << Earth.Height << endl;
//    cout << Earth.node.Width << " " << Earth.node.Height << endl;
//    cout << Nova.shipWidth << " " << Nova.shipHeight << endl;
//    cout << Nova.BulletWidth << " " << Nova.BulletHeight << endl;
    Nova.shipWidth = 115;Nova.shipHeight = 115;
    Nova.BulletHeight = 30;Nova.BulletWidth = 30;
    Earth.Width = 305;Earth.Height = 305;
    Earth.node.Width = 58;Earth.node.Height = 58;
    aster.Width = 50;aster.Height = 50;
    sHealth.Width = 30;sHealth.Height = 30;

        //UI
    SDL_Texture* backgroundMenu = loadTexture("images/bgMenu.png",renderer);
    SDL_Texture* backgroundGame = loadTexture("images/backgroundGame.png",renderer);
    SDL_Texture* ButtonTexture = loadTexture("images/Button.png",renderer);
    SDL_Texture* number = loadTexture("images/Number.png",renderer);
    SDL_Texture* gOver = loadTexture("images/game_over.png",renderer);
    SDL_Texture* score_gameTexture = loadTexture("images/score_game.png",renderer);
    SDL_Texture* PauseTexture = loadTexture("images/pausebutton.png",renderer);
    SDL_Texture* HelpTexture = loadTexture("images/help.png",renderer);
    SDL_Texture* backTexture = loadTexture("images/backbutton.png",renderer);

    SDL_Rect score_game = {HIGH_SCORE_TEXTPX,HIGH_SCORE_TEXTPY,161,45};
    SDL_Rect renderbgRect = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
    SDL_Rect RectPlayButton[BUTTON_MOUSE_TOTAL];
    SDL_Rect RectExitButton[BUTTON_MOUSE_TOTAL];
    SDL_Rect RectHelpButton[BUTTON_MOUSE_TOTAL];
    SDL_Rect RectPauseButton[BUTTON_MOUSE_TOTAL];
    SDL_Rect RectBackButton[BUTTON_MOUSE_TOTAL];

    Button playButton(PLAY_BUTTON_POSX,PLAY_BUTTON_POSY);
    Button exitButton(EXIT_BUTTON_POSX,EXIT_BUTTON_POSY);
    Button helpButton(HELP_BUTTON_POSX,HELP_BUTTON_POSY);
    Button backButton(BACK_BUTTON_POSX,BACK_BUTTON_POSY);
    Button pauseButton(PAUSE_BUTTON_POSX,PAUSE_BUTTON_POSY);
    playButton.setRect(RectPlayButton,0,1);
    exitButton.setRect(RectExitButton,1,1);
    helpButton.setRect(RectHelpButton,2,1);
    backButton.setRect(RectBackButton,0,2);
    pauseButton.setRect(RectPauseButton,0,2);

    //Game manager
    bool quit = false,playagain = false, gameover = false, pause = false;
    int lastscore = 0;
    Uint32 speedTimer = 0;
    Uint32 lastShootTime = SDL_GetTicks();
    Uint32 lastspawnAster = lastShootTime;
    SDL_Event e;
    Mix_PlayMusic(menuMusic,-1);
        while(!quit)
        {
            SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
            SDL_RenderClear( renderer );
            string highscore = GetHighScoreFromFile("high_score.txt");
            switch (display)
            {
            case menu:
                {
                    SDL_RenderCopy(renderer,backgroundMenu,NULL,NULL);
                    while(SDL_PollEvent(&e)!=0)
                    {
                        if(e.type==SDL_QUIT)    quit = true;

                        if(e.type==SDL_KEYDOWN&&e.key.keysym.sym==SDLK_ESCAPE) quit = true;
                        if(playButton.handleEventInside(&e,1)) playButton.currentSprite = BUTTON_MOUSE_OVER;
                        else playButton.currentSprite = BUTTON_MOUSE_OUT;
                        if(exitButton.handleEventInside(&e,1)) exitButton.currentSprite = BUTTON_MOUSE_OVER;
                        else exitButton.currentSprite = BUTTON_MOUSE_OUT;
                        if(helpButton.handleEventInside(&e,1)) helpButton.currentSprite = BUTTON_MOUSE_OVER;
                        else helpButton.currentSprite = BUTTON_MOUSE_OUT;
                        if(playButton.handleEventInside(&e,1)&&e.type == SDL_MOUSEBUTTONDOWN) {
                            playagain = 1;
                            display = game;
                            Mix_PlayChannel(-1,Click,0);
                            Mix_HaltMusic();
                            Mix_PlayMusic(gameMusic,-1);
                        }
                        if(exitButton.handleEventInside(&e,1)&&e.type == SDL_MOUSEBUTTONDOWN) {
                            quit = true;
                            Mix_PlayChannel(-1,Click,0);
                        }
                        if(helpButton.handleEventInside(&e,1)&&e.type == SDL_MOUSEBUTTONDOWN) {
                            display = helpscene;
                            Mix_PlayChannel(-1,Click,0);
                        }

                    }
                    RenderNumber(renderer, number, 1, Nova.score);
                    playButton.render(renderer, &RectPlayButton[playButton.currentSprite], ButtonTexture,1);
                    exitButton.render(renderer, &RectExitButton[exitButton.currentSprite], ButtonTexture,1);
                    helpButton.render(renderer, &RectHelpButton[helpButton.currentSprite], ButtonTexture,1);
                    speedTimer = SDL_GetTicks();
                    break;
                }
            case game:
                {
                    SDL_RenderCopy(renderer,backgroundGame,&renderbgRect,NULL);
                    if(gameover) {
                        while(!quit) {
                            while(SDL_PollEvent(&e)!=0) if(e.type==SDL_QUIT) quit = true;
                            const Uint8 *states = SDL_GetKeyboardState(NULL);
                            if(states[SDL_SCANCODE_ESCAPE]){
                            display = menu;
                            Mix_HaltMusic();
                            Mix_PlayMusic(menuMusic,-1);
                            break;
                            }
                            else if(states[SDL_SCANCODE_RETURN]) {
                            Mix_PlayMusic(gameMusic,-1);
                            playagain = 1;
                            break;
                            }
                        }
                        UpdateHighScore("high_score.txt",Nova.score,highscore);
                        gameover = 0;
                    }
                    if(playagain) {
                        lastscore = 0;
                        Nova.score = 0;
                        Nova.health = 2;
                        Nova.rotation = rand()%361;
                        speedTimer = 0;
                        Earth.speed = 0.5;
                        playagain = 0;
                        asteroids.clear();
                        Nova.radius = 290;
                        Mix_PlayChannel(-1,Start,0);
                    }
                    while(pause&&!quit) {
                            while(SDL_PollEvent(&e)!=0)
                            {
                                if(e.type==SDL_QUIT) quit = true;
                                if(e.type==SDL_KEYDOWN&&e.key.keysym.sym==SDLK_ESCAPE) {
                                        display = menu;
                                        pause = 0;
                                        Mix_PlayMusic(menuMusic,-1);
                                }
                                if(pauseButton.handleEventInside(&e,2)) pauseButton.currentSprite = BUTTON_MOUSE_OVER;
                                else pauseButton.currentSprite = BUTTON_MOUSE_OUT;
                                if(pauseButton.handleEventInside(&e,2)&&e.type == SDL_MOUSEBUTTONDOWN)
                                {
                                    pause = 0;
                                    Mix_PlayChannel(-1,Click,0);
                                    pauseButton.setRect(RectPauseButton,0,2);
                                    Mix_ResumeMusic();
                                }
                                pauseButton.render(renderer, &RectPauseButton[pauseButton.currentSprite], PauseTexture, 2);
                            }

                    }
                    while(SDL_PollEvent(&e)!=0)
                    {
                            if(e.type==SDL_QUIT) quit = true;
                            if(pauseButton.handleEventInside(&e,2)) pauseButton.currentSprite = BUTTON_MOUSE_OVER;
                            else pauseButton.currentSprite = BUTTON_MOUSE_OUT;
                            if(pauseButton.handleEventInside(&e,2)&&e.type == SDL_MOUSEBUTTONDOWN)
                            {
                                pause = 1;
                                Mix_PauseMusic();
                                Mix_PlayChannel(-1,Click,0);
                                pauseButton.setRect(RectPauseButton,1,2);
                            }
                    }
                    const Uint8 *states = SDL_GetKeyboardState(NULL);
                    if( states[SDL_SCANCODE_A] || states[SDL_SCANCODE_LEFT])
                        {
                            Nova.Move(-1);
                        }
                    else if( states[SDL_SCANCODE_D] || states[SDL_SCANCODE_RIGHT])
                        {
                            Nova.Move(1);
                        }
                    else if( states[SDL_SCANCODE_W] || states[SDL_SCANCODE_UP])
                        {
                            Nova.Move(2);
                        }
                    else if( states[SDL_SCANCODE_S] || states[SDL_SCANCODE_DOWN])
                        {
                            Nova.Move(-2);
                        }
                    else if(states[SDL_SCANCODE_SPACE]&&SDL_GetTicks()-lastShootTime > 500)
                        {
                            Nova.Shoot();
                            lastShootTime = SDL_GetTicks();
                            Mix_PlayChannel(-1,Shoot,0);
                        }
                    else if(states[SDL_SCANCODE_ESCAPE])
                        {
                            display = menu;
                            Mix_HaltMusic();
                            Mix_PlayMusic(menuMusic,-1);
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
                            Nova.health--;
                            Mix_PlayChannel(-1,get_hit,0);
                        }

                        if((asteroids[i].pos.f > 800 || asteroids[i].pos.f < 0) && (asteroids[i].pos.s < 0 || asteroids[i].pos.s > 800))
                        {
                            asteroids.erase(asteroids.begin() + i);
                        }
                    }
                    pauseButton.render(renderer, &RectPauseButton[pauseButton.currentSprite], PauseTexture, 2);
                    SDL_RenderCopy(renderer, score_gameTexture, NULL, &score_game);
                    renderHealth(renderer,Nova.shipHealthTexture, Nova.health);
                    Nova.render(renderer,Earth.node.renderQuad,Earth.planetQuad,Shoot,bulletExplode);
                    RenderNumber(renderer,number,2,Nova.score);
                    Earth.SetRotation(speedTimer);
                    if(lastscore + 1 == Nova.score) {
                        Earth.node.Restart(),lastscore = Nova.score;
                        Mix_PlayChannel(-1,point,0);
                }
                    if(speedTimer + 9000 < SDL_GetTicks()) Earth.speed+=0.1f,speedTimer = SDL_GetTicks();
                    Earth.render(renderer);
                    if(Nova.health == 0) {
                    Mix_PauseMusic();
                    Mix_PlayChannel(-1,Over,0);
                    gameover = 1;
                    Nova.health++;
                    SDL_Rect dRect = {OVER_POSX,OVER_POSY,OVER_WIDTH,OVER_HEIGHT};
                    SDL_RenderCopy(renderer,gOver,NULL,&dRect);
                }
                    break;
                }
            case helpscene:
                {
                    SDL_RenderCopy(renderer,HelpTexture,NULL,NULL);
                    while(SDL_PollEvent(&e)!=0)
                    {
                        if(e.type==SDL_QUIT)    quit = true;
                        if(e.type==SDL_KEYDOWN&&e.key.keysym.sym==SDLK_ESCAPE) display = menu;
                        if(backButton.handleEventInside(&e,2)) backButton.currentSprite = BUTTON_MOUSE_OVER;
                        else backButton.currentSprite = BUTTON_MOUSE_OUT;
                        if(backButton.handleEventInside(&e,2)&&e.type == SDL_MOUSEBUTTONDOWN) {
                            display = menu;
                            Mix_PlayChannel(-1,Click,0);
                        }

                    }
                    backButton.render(renderer, &RectBackButton[backButton.currentSprite], backTexture, 2);
                }
        }
        SDL_RenderPresent( renderer );
        }
    Mix_FreeMusic(gameMusic);
    Mix_FreeMusic(menuMusic);
    Mix_FreeChunk(Click);
    Mix_FreeChunk(bulletExplode);
    Mix_FreeChunk(Over);
    Mix_FreeChunk(get_hit);
    Mix_FreeChunk(point);
    Mix_FreeChunk(Shoot);
    Mix_FreeChunk(Start);
     gameMusic = nullptr;
     menuMusic = nullptr;
     Click = nullptr;
     Shoot = nullptr;
     Over = nullptr;
     get_hit = nullptr;
     Start = nullptr;
     point = nullptr;
     bulletExplode = nullptr;
    quitSDL(window, renderer);
    return 0;
}
