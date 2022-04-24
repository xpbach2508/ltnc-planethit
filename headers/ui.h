#ifndef U_I_H
#define U_I_H
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "SDL_ultils.h"
using namespace std;

class Button
{
public:
    ButtonSprite currentSprite;
    Button(int x, int y);
    Button();
    void free(SDL_Texture* ButtonTexture);
    //335,144-11,22;362,117-18,212;307,193-29,371;316,179-45,623;374,160-424,23
    void setRect(SDL_Rect* re,int type);
    bool handleEventInside(SDL_Event* e,int sizeB);
    void render(SDL_Renderer* renderer,SDL_Rect* currentClip, SDL_Texture* texture);
private:
    SDL_Point pPosition;

};

#endif // U_I_H
