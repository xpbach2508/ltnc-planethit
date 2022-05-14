#ifndef U_I_H
#define U_I_H
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "GAME_ultils.h"
using namespace std;

class Button
{
public:
    ButtonSprite currentSprite;
    Button(int x, int y);
    Button();
    int picked = 0;
    void setRect(SDL_Rect* re,int type,int kind);
    bool handleEventInside(SDL_Event* e,int sizeB);
    void render(SDL_Renderer* renderer,SDL_Rect* currentClip, SDL_Texture* texture, int kind);
private:
    SDL_Point pPosition;

};
void setSkin(Button* b1, Button* b2, Button* b3, SDL_Event e, Mix_Chunk* sound, int& _highscore, TTF_Font* font, SDL_Renderer* renderer);

void initSkin(Button* b1, Button* b2, Button* b3, int& loaded);

#endif // U_I_H
