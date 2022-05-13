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
#include "headers/asteroids.h"
#include "headers/SDL_ultils.h"
#include "headers/ui.h"

#define f first
#define s second

using namespace std;


int main(int argc, char* argv[])
{
    srand(time(NULL));
    SCENE display = menu;
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);

    //Initialize things
    //Game
    Planet* Earth = new Planet;
    Ship* Nova = new Ship;
    vector<asteroid> asteroids;
    sizeAsset aster;
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

    //Game custom
    Button skinShip1(82,192);
    Button skinShip2(182,192);
    Button skinShip3(270,192);
    Button skinPlanet1(468,192);
    Button skinPlanet2(565,192);
    Button skinPlanet3(661,192);
    Button skinBullet1(282,459);
    Button skinBullet2(358,459);
    Button skinBullet3(438,459);
    SDL_Texture* planetS[4];
    SDL_Texture* shipS[4];
    SDL_Texture* bulletS[4];
    shipS[1] = loadTexture("images/ship/ship1.png",renderer);
    shipS[2] = loadTexture("images/ship/ship2.png",renderer);
    shipS[3] = loadTexture("images/ship/ship3.png",renderer);
    planetS[1] = loadTexture("images/planet/planet1.png",renderer);
    planetS[2] = loadTexture("images/planet/planet2.png",renderer);
    planetS[3] = loadTexture("images/planet/planet3.png",renderer);
    bulletS[1] = loadTexture("images/bullet/bullet1.png",renderer);
    bulletS[2] = loadTexture("images/bullet/bullet2.png",renderer);
    bulletS[3] = loadTexture("images/bullet/bullet3.png",renderer);
    TTF_Font* font = NULL;
    font = TTF_OpenFont("Pixeboy.ttf",30);

    //Texture size
    Nova->shipWidth = SHIP_SIZE; Nova->shipHeight = SHIP_SIZE;
    Nova->BulletHeight = BULLET_SIZE; Nova->BulletWidth = BULLET_SIZE;
    Earth->Width = PLANET_SIZE; Earth->Height = PLANET_SIZE;
    Earth->node.Width = NODE_SIZE; Earth->node.Height = NODE_SIZE;
    aster.Width = ASTER_SIZE; aster.Height = ASTER_SIZE;
    //Game texture
    vector<int> LoadedSetting = LoadSetting("settings.txt");
    Nova->shipTexture = shipS[LoadedSetting[0]];initSkin(&skinShip1, &skinShip2, &skinShip3, LoadedSetting[0]);
    if(LoadedSetting[0]==1) Nova->shipHeight/=1.66;if(LoadedSetting[0]==2)Nova->shipWidth /=2;if(LoadedSetting[0]==3)Nova->shipWidth /=1.8,Nova->shipHeight/=1.5;
    Nova->BulletTexture = bulletS[LoadedSetting[1]];initSkin(&skinBullet1, &skinBullet2, &skinBullet3, LoadedSetting[1]);
    Earth->Texture = planetS[LoadedSetting[2]];initSkin(&skinPlanet1, &skinPlanet2, &skinPlanet3, LoadedSetting[2]);
    Nova->shipHealthTexture = loadTexture("images/health.png",renderer);
    Earth->node.Texture = loadTexture("images/node.png",renderer);
    SDL_Texture* asterTexture = loadTexture("images/asteroid.png",renderer);

        //UI
    SDL_Texture* backgroundMenu = loadTexture("images/bgMenu.png",renderer);
    SDL_Texture* backgroundGame = loadTexture("images/backgroundGame.png",renderer);
    SDL_Texture* pickedSkin = loadTexture("images/picked.png",renderer);
    SDL_Texture* ButtonTexture = loadTexture("images/Button.png",renderer);
    SDL_Texture* number = loadTexture("images/Number.png",renderer);
    SDL_Texture* gOver = loadTexture("images/game_over.png",renderer);
    SDL_Texture* score_gameTexture = loadTexture("images/score_game.png",renderer);
    SDL_Texture* PauseTexture = loadTexture("images/pausebutton.png",renderer);
    SDL_Texture* HelpTexture = loadTexture("images/help.png",renderer);
    SDL_Texture* customTexture = loadTexture("images/customize.png",renderer);
    SDL_Texture* backTexture = loadTexture("images/backbutton.png",renderer);

    SDL_Rect score_game = {HIGH_SCORE_TEXTPX,HIGH_SCORE_TEXTPY,161,45};
    SDL_Rect renderbgRect = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
    SDL_Rect RectPlayButton[BUTTON_MOUSE_TOTAL];
    SDL_Rect RectExitButton[BUTTON_MOUSE_TOTAL];
    SDL_Rect RectHelpButton[BUTTON_MOUSE_TOTAL];
    SDL_Rect RectOptiButton[BUTTON_MOUSE_TOTAL];
    SDL_Rect RectPauseButton[BUTTON_MOUSE_TOTAL];
    SDL_Rect RectBackButton[BUTTON_MOUSE_TOTAL];
    SDL_Rect RectPickedButton[BUTTON_MOUSE_TOTAL];

    Button playButton(PLAY_BUTTON_POSX,PLAY_BUTTON_POSY);
    Button exitButton(EXIT_BUTTON_POSX,EXIT_BUTTON_POSY);
    Button helpButton(HELP_BUTTON_POSX,HELP_BUTTON_POSY);
    Button optiButton(OPTION_BUTTON_POSX,OPTION_BUTTON_POSY);
    Button backButton(BACK_BUTTON_POSX,BACK_BUTTON_POSY);
    Button pauseButton(PAUSE_BUTTON_POSX,PAUSE_BUTTON_POSY);
    playButton.setRect(RectPlayButton,0,MAIN_BUTTON);
    exitButton.setRect(RectExitButton,1,MAIN_BUTTON);
    helpButton.setRect(RectHelpButton,2,MAIN_BUTTON);
    optiButton.setRect(RectOptiButton,3,MAIN_BUTTON); //vi cung 1 sprite nen type la 2
    backButton.setRect(RectBackButton,0,GAME_BUTTON);
    pauseButton.setRect(RectPauseButton,0,GAME_BUTTON);
    skinShip1.setRect(RectPickedButton,0,SKIN_PICKED);

    //Game manager
    bool quit = false,playagain = false, gameover = false, pause = false;
    int lastscore = 0;
    Uint32 speedTimer = 0;
    Uint32 lastShootTime = SDL_GetTicks();
    Uint32 lastspawnAster = lastShootTime;
    Uint32 lastDeath = 0;
    Uint32 GameTime = 0;
    SDL_Event e;
    Mix_PlayMusic(menuMusic,-1);
        //GAME
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
                        if(optiButton.handleEventInside(&e,1)) optiButton.currentSprite = BUTTON_MOUSE_OVER;
                        else optiButton.currentSprite = BUTTON_MOUSE_OUT;

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
                        if(optiButton.handleEventInside(&e,1)&&e.type == SDL_MOUSEBUTTONDOWN) {
                            display = custom;
                            Mix_PlayChannel(-1,Click,0);
                        }

                    }
                    RenderNumber(renderer, number, MAIN_BUTTON, Nova->score);
                    playButton.render(renderer, &RectPlayButton[playButton.currentSprite], ButtonTexture,MAIN_BUTTON);
                    exitButton.render(renderer, &RectExitButton[exitButton.currentSprite], ButtonTexture,MAIN_BUTTON);
                    helpButton.render(renderer, &RectHelpButton[helpButton.currentSprite], ButtonTexture,MAIN_BUTTON);
                    optiButton.render(renderer, &RectOptiButton[optiButton.currentSprite], ButtonTexture,MAIN_BUTTON);
                    speedTimer = SDL_GetTicks();
                    break;
                }
            case game:
                {
                    SDL_RenderCopy(renderer,backgroundGame,&renderbgRect,NULL);
                    GameTime = SDL_GetTicks();
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
                        UpdateHighScore("high_score.txt",Nova->score,highscore);
                        gameover = 0;
                    }
                    if(playagain) {
                        lastscore = 0;
                        Nova->score = 0;
                        Nova->health = 5;
                        Nova->rotation = rand()%361;
                        speedTimer = 0;
                        Earth->speed = 0.5;
                        playagain = 0;
                        asteroids.clear();
                        Nova->radius = 290;
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
                                if(pauseButton.handleEventInside(&e,GAME_BUTTON)) pauseButton.currentSprite = BUTTON_MOUSE_OVER;
                                else pauseButton.currentSprite = BUTTON_MOUSE_OUT;
                                if(pauseButton.handleEventInside(&e,GAME_BUTTON)&&e.type == SDL_MOUSEBUTTONDOWN)
                                {
                                    pause = 0;
                                    Mix_PlayChannel(-1,Click,0);
                                    pauseButton.setRect(RectPauseButton,0,2);
                                    Mix_ResumeMusic();
                                }
                                pauseButton.render(renderer, &RectPauseButton[pauseButton.currentSprite], PauseTexture, GAME_BUTTON);
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
                            Nova->Move(-1);
                        }
                    else if( states[SDL_SCANCODE_D] || states[SDL_SCANCODE_RIGHT])
                        {
                            Nova->Move(1);
                        }
                    else if( states[SDL_SCANCODE_W] || states[SDL_SCANCODE_UP])
                        {
                            Nova->Move(2);
                        }
                    else if( states[SDL_SCANCODE_S] || states[SDL_SCANCODE_DOWN])
                        {
                            Nova->Move(-2);
                        }
                    else if(states[SDL_SCANCODE_SPACE]&&(GameTime-lastShootTime) > 500)
                        {
                            Nova->Shoot();
                            lastShootTime = GameTime;
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
                    if(GameTime > lastspawnAster + 5000)
                        {
                        lastspawnAster = GameTime;
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

                        if(checkCollision2(asteroids[i].asterCir,Earth->planetCir))
                            asteroids.erase(asteroids.begin()+i);

                        //if(checkCollision1(asteroids[i].asterCir,Nova->shipQuad,Nova->rotation))
                        if(checkCollision2(asteroids[i].asterCir,Nova->shipCir))
                        {
                            asteroids.erase(asteroids.begin()+i);
                            if(lastDeath + 1000 < GameTime) {
                                //Nova->health--;
                                Mix_PlayChannel(-1,get_hit,0);
                                lastDeath = GameTime;
                            }
                            cout << "wtf" << endl;
                        }

                        if((asteroids[i].pos.f > 800 || asteroids[i].pos.f < 0) && (asteroids[i].pos.s < 0 || asteroids[i].pos.s > 800))
                        {
                            asteroids.erase(asteroids.begin() + i);
                        }
                    }
                    pauseButton.render(renderer, &RectPauseButton[pauseButton.currentSprite], PauseTexture, 2);
                    SDL_RenderCopy(renderer, score_gameTexture, NULL, &score_game);
                    renderHealth(renderer,Nova->shipHealthTexture, Nova->health);
                    Nova->render(renderer,&Earth->node.nodeCir,&Earth->planetCir,Shoot,bulletExplode);
                    RenderNumber(renderer,number,GAME_BUTTON,Nova->score);
                    Earth->SetRotation(speedTimer);
                    if(lastscore + 1 == Nova->score) {//Cong diem thi restart node
                        Earth->node.Restart(),lastscore = Nova->score;
                        Mix_PlayChannel(-1,point,0);
                    }
                    Earth->render(renderer);

                    if(speedTimer + 9000 < SDL_GetTicks()) Earth->speed+=0.1f,speedTimer = SDL_GetTicks();//Tang dan toc do quay cho Planet
                    if(Nova->health == 0) { //Khi ma game over thi cho vao vong lap
                        Mix_PauseMusic();
                        Mix_PlayChannel(-1,Over,0);
                        gameover = 1;
                        Nova->health++;
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
                        if(backButton.handleEventInside(&e,GAME_BUTTON)) backButton.currentSprite = BUTTON_MOUSE_OVER;
                        else backButton.currentSprite = BUTTON_MOUSE_OUT;
                        if(backButton.handleEventInside(&e,GAME_BUTTON)&&e.type == SDL_MOUSEBUTTONDOWN) {
                            display = menu;
                            Mix_PlayChannel(-1,Click,0);
                        }

                    }
                    backButton.render(renderer, &RectBackButton[backButton.currentSprite], backTexture, GAME_BUTTON);
                    break;
                }
            case custom:
                {
                    int highScore; stringstream ConverToInt(highscore);ConverToInt >> highScore;
                    SDL_RenderCopy(renderer,customTexture,NULL,NULL);
                    backButton.render(renderer, &RectBackButton[backButton.currentSprite], backTexture, GAME_BUTTON);
                    RenderNumber(renderer, number, MAIN_BUTTON, Nova->score);

                    while(SDL_PollEvent(&e)!=0) {
                        if(e.type==SDL_QUIT)    quit = true;

                        if(e.type==SDL_KEYDOWN&&e.key.keysym.sym==SDLK_ESCAPE) quit = true;

                        if(backButton.handleEventInside(&e,GAME_BUTTON)) backButton.currentSprite = BUTTON_MOUSE_OVER;
                        else backButton.currentSprite = BUTTON_MOUSE_OUT;
                        if(backButton.handleEventInside(&e,GAME_BUTTON)&&e.type == SDL_MOUSEBUTTONDOWN) {
                            display = menu;
                            Mix_PlayChannel(-1,Click,0);
                        }

                        setSkin(&skinShip1, &skinShip2, &skinShip3, e, Click, highScore, font, renderer);

                        setSkin(&skinPlanet1,&skinPlanet2,&skinPlanet3, e, Click, highScore, font, renderer);

                        setSkin(&skinBullet1,&skinBullet2,&skinBullet3, e, Click, highScore, font, renderer);
                    }
                    LoadedSetting = LoadSetting("settings.txt");
                    if(skinShip1.picked) {Nova->shipTexture = shipS[1];Nova->shipWidth = SHIP_SIZE;Nova->shipHeight = SHIP_SIZE/1.66;UpdateSetting("settings.txt", 1, LoadedSetting[1], LoadedSetting[2]);}
                    if(skinShip2.picked) {Nova->shipTexture = shipS[2];Nova->shipWidth = SHIP_SIZE/2;Nova->shipHeight = SHIP_SIZE;UpdateSetting("settings.txt", 2, LoadedSetting[1], LoadedSetting[2]);}
                    if(skinShip3.picked) {Nova->shipTexture = shipS[3];Nova->shipWidth = SHIP_SIZE/1.8;Nova->shipHeight/1.5;UpdateSetting("settings.txt", 3, LoadedSetting[1], LoadedSetting[2]);}
                    LoadedSetting = LoadSetting("settings.txt");
                    if(skinBullet1.picked) Nova->BulletTexture = bulletS[1],UpdateSetting("settings.txt", LoadedSetting[0], 1, LoadedSetting[2]);
                    if(skinBullet2.picked) Nova->BulletTexture = bulletS[2],UpdateSetting("settings.txt", LoadedSetting[0], 2, LoadedSetting[2]);
                    if(skinBullet3.picked) Nova->BulletTexture = bulletS[3],UpdateSetting("settings.txt", LoadedSetting[0], 3, LoadedSetting[2]);
                    LoadedSetting = LoadSetting("settings.txt");
                    if(skinPlanet1.picked) Earth->Texture = planetS[1],UpdateSetting("settings.txt", LoadedSetting[0], LoadedSetting[1], 1);
                    if(skinPlanet2.picked) Earth->Texture = planetS[2],UpdateSetting("settings.txt", LoadedSetting[0], LoadedSetting[1], 2);
                    if(skinPlanet3.picked) Earth->Texture = planetS[3],UpdateSetting("settings.txt", LoadedSetting[0], LoadedSetting[1], 3);
                    skinShip1.render(renderer,&RectPickedButton[skinShip1.currentSprite], pickedSkin, SKIN_PICKED);
                    skinShip2.render(renderer,&RectPickedButton[skinShip2.currentSprite], pickedSkin, SKIN_PICKED);
                    skinShip3.render(renderer,&RectPickedButton[skinShip3.currentSprite], pickedSkin, SKIN_PICKED);
                    skinBullet1.render(renderer,&RectPickedButton[skinBullet1.currentSprite], pickedSkin, SKIN_PICKED);
                    skinBullet2.render(renderer,&RectPickedButton[skinBullet2.currentSprite], pickedSkin, SKIN_PICKED);
                    skinBullet3.render(renderer,&RectPickedButton[skinBullet3.currentSprite], pickedSkin, SKIN_PICKED);
                    skinPlanet1.render(renderer,&RectPickedButton[skinPlanet1.currentSprite], pickedSkin, SKIN_PICKED);
                    skinPlanet2.render(renderer,&RectPickedButton[skinPlanet2.currentSprite], pickedSkin, SKIN_PICKED);
                    skinPlanet3.render(renderer,&RectPickedButton[skinPlanet3.currentSprite], pickedSkin, SKIN_PICKED);
                    if(highScore < 20 && skinShip2.currentSprite == BUTTON_MOUSE_OVER) renderText("NEED 20 POINTS HIGHSCORE TO UNLOCK", font, renderer);
                    if(highScore < 20 && skinBullet2.currentSprite == BUTTON_MOUSE_OVER) renderText("NEED 20 POINTS HIGHSCORE TO UNLOCK", font, renderer);
                    if(highScore < 20 && skinPlanet2.currentSprite == BUTTON_MOUSE_OVER) renderText("NEED 20 POINTS HIGHSCORE TO UNLOCK", font, renderer);
                    if(highScore < 30 && skinShip3.currentSprite == BUTTON_MOUSE_OVER) renderText("NEED 30 POINTS HIGHSCORE TO UNLOCK", font, renderer);
                    if(highScore < 30 && skinBullet3.currentSprite == BUTTON_MOUSE_OVER) renderText("NEED 30 POINTS HIGHSCORE TO UNLOCK", font, renderer);
                    if(highScore < 30 && skinPlanet3.currentSprite == BUTTON_MOUSE_OVER) renderText("NEED 30 POINTS HIGHSCORE TO UNLOCK", font, renderer);
                    break;
                }
            }
        SDL_RenderPresent( renderer );
        }
    //FREE
    delete Earth;
    delete Nova;
    asteroids.clear();
    freeTexture(asterTexture);
    freeTexture(backgroundMenu);
    freeTexture(backgroundGame);
    freeTexture(pickedSkin);
    freeTexture(ButtonTexture);
    freeTexture(number);
    freeTexture(gOver);
    freeTexture(score_gameTexture);
    freeTexture(PauseTexture);
    freeTexture(HelpTexture);
    freeTexture(customTexture);
    freeTexture(backTexture);
    //for(int i = 0; i <= 3; i++) {freeTexture(shipS[i]);freeTexture(planetS[i]);freeTexture(bulletS[i]);}
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
