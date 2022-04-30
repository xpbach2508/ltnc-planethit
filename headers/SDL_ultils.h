#ifndef SDL_UTILS_H
#define SDL_UTILS_H
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include "asteroids.h"

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
const int TITLE_HEIGHT = 437;
const int MAIN_BUTTON_WIDTH = 248;
const int MAIN_BUTTON_HEIGHT = 90;
const int HIGH_SCORE_MENU_WIDTH = 0;
const int HIGH_SCORE_MENU_HEIGHT = 0;

const int TITLE_POSX = 0;
const int TITLE_POSY = 0;
const int PLAY_BUTTON_POSX = 272;
const int PLAY_BUTTON_POSY = 439;
const int EXIT_BUTTON_POSX = 275;
const int EXIT_BUTTON_POSY = 591;
const int HIGH_SCORE_MENUPX = 130;
const int HIGH_SCORE_MENUPY = 429;
const int HIGH_SCORE_TEXTPX = 0;
const int HIGH_SCORE_TEXTPY = 0;
const int HIGH_SCORE_GAMEPX = 0;
const int HIGH_SCORE_GAMEPY = 0;
const int SCORE_GAMEPX = 0;
const int SCORE_GAMEPY = 20;
const int HEALTH_POSX = 650;
const int HEALTH_POSY = 0;


void Game_Over();

void RenderNumber(SDL_Renderer* renderer, SDL_Texture* texture, int kind, const int & score);

std::string GetHighScoreFromFile(std::string path);

void UpdateHighScore(std::string path, const int& score, const std::string& old_high_score);

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);

void logSDLError(std::ostream& os, const std::string &msg, bool fatal = false);

void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

SDL_Texture* loadTexture(std::string path, SDL_Renderer* renderer);

bool CheckCollision(SDL_FRect& a, SDL_FRect& b);

#endif // SDL_UTILS_H
