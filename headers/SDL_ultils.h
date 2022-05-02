#ifndef SDL_UTILS_H
#define SDL_UTILS_H
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include "asteroids.h"
#include <SDL_mixer.h>

#define MAIN_BUTTON 1
#define GAME_BUTTON 2

enum SCENE
{
    menu, game, helpscene
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
const int TITLE_HEIGHT = 496;
const int MAIN_BUTTON_WIDTH = 248;
const int MAIN_BUTTON_HEIGHT = 90;
const int PAUSE_BUTTON_WIDTH = 54;
const int PAUSE_BUTTON_HEIGHT = 54;
const int GAME_BUTTON_WIDTH = 97;
const int GAME_BUTTON_HEIGHT = 85;
const int OVER_WIDTH =  684;
const int OVER_HEIGHT = 137;

const int TITLE_POSX = 0;
const int TITLE_POSY = 0;
const int PLAY_BUTTON_POSX = 275;
const int PLAY_BUTTON_POSY = 385;
const int EXIT_BUTTON_POSX = 275;
const int EXIT_BUTTON_POSY = 655;
const int HELP_BUTTON_POSX = 275;
const int HELP_BUTTON_POSY = 520;
const int BACK_BUTTON_POSX = 0;
const int BACK_BUTTON_POSY = 0;
const int PAUSE_BUTTON_POSX = 0;
const int PAUSE_BUTTON_POSY = 715;
const int HIGH_SCORE_MENUPX = 121;
const int HIGH_SCORE_MENUPY = 739;
const int HIGH_SCORE_TEXTPX = 0;
const int HIGH_SCORE_TEXTPY = 7;
const int HIGH_SCORE_GAMEPX = 165;
const int HIGH_SCORE_GAMEPY = 5;
const int SCORE_GAMEPX = 91;
const int SCORE_GAMEPY = 32;
const int HEALTH_POSX = 650;
const int HEALTH_POSY = 0;
const int OVER_POSX = 57;
const int OVER_POSY = 612;


void Game_Over();

void renderHealth(SDL_Renderer* renderer, SDL_Texture* texture, int& health);

void RenderNumber(SDL_Renderer* renderer, SDL_Texture* texture, int kind, const int & score);

std::string GetHighScoreFromFile(std::string path);

void UpdateHighScore(std::string path, const int& score, const std::string& old_high_score);

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);

void logSDLError(std::ostream& os, const std::string &msg, bool fatal = false);

void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

SDL_Texture* loadTexture(std::string path, SDL_Renderer* renderer);

bool CheckCollision(SDL_FRect& a, SDL_FRect& b);

#endif // SDL_UTILS_H
