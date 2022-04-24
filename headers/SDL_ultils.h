#ifndef SDL_UTILS_H
#define SDL_UTILS_H
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#define MAIN_BUTTON 1
#define GAME_BUTTON 2

enum SCENE
{
    menu, game
};
enum ButtonSprite
{
    BUTTON_MOUSE_OUT = 0,
    BUTTON_MOUSE_OVER = 1,
    BUTTON_MOUSE_TOTAL = 2
};
struct sizeAsset
{
    float Width,Height;
};
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;
const std::string WINDOW_TITLE = "Planet Hit";

const int TITLE_WIDTH = 800;
const int TITLE_HEIGHT = 375;
const int MAIN_BUTTON_WIDTH = 248;
const int MAIN_BUTTON_HEIGHT = 90;

const int TITLE_POSX = 0;
const int TITLE_POSY = 0;
const int PLAY_BUTTON_POSX = 272;
const int PLAY_BUTTON_POSY = 439;
const int EXIT_BUTTON_POSX = 275;
const int EXIT_BUTTON_POSY = 591;



void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);

void logSDLError(std::ostream& os, const std::string &msg, bool fatal = false);

void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

SDL_Texture* loadTexture(std::string path, SDL_Renderer* renderer,float& Width,float &Height);

bool CheckCollision(SDL_FRect& a, SDL_FRect& b);

#endif // SDL_UTILS_H
