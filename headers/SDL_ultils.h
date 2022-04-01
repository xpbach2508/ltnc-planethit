#ifndef SDL_UTILS_H
#define SDL_UTILS_H
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);

void logSDLError(std::ostream& os, const std::string &msg, bool fatal = false);

void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

SDL_Texture* loadTexture(string path, SDL_Renderer* renderer,float& Width,float &Height);

bool CheckCollision(SDL_FRect& a, SDL_FRect& b);

#endif // SDL_UTILS_H
