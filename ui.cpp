#include "headers/ui.h"
using namespace std;

Button::Button()
{
    pPosition.x = 0;
    pPosition.y = 0;
    currentSprite = BUTTON_MOUSE_OUT;
};
Button::Button(int x, int y)
{
	pPosition.x = x;
	pPosition.y = y;

	currentSprite = BUTTON_MOUSE_OUT;
}
void Button::setRect(SDL_Rect* re,int type,int kind)
{
    int width = 0,height = 0;
    switch(kind)
    {
        case MAIN_BUTTON:
    {
         width = MAIN_BUTTON_WIDTH;
         height = MAIN_BUTTON_HEIGHT;
         break;
    }
        case GAME_BUTTON:
    {
        width = GAME_BUTTON_WIDTH;
        height = GAME_BUTTON_HEIGHT;
        break;
    }
        case SKIN_PICKED:
    {
        width = SKIN_PICKED_WIDTH;
        height = SKIN_PICKED_HEIGHT;
        break;
    }
    }
    for(int i = 0; i < BUTTON_MOUSE_TOTAL; i++)
    {
        re[i].x = width*i;
        re[i].y = height*type;
        re[i].w = width;
        re[i].h = height;
    }
}
bool Button::handleEventInside(SDL_Event* e,int sizeB)
{
    if(e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
    {
        int x,y;
        SDL_GetMouseState(&x,&y);
        bool inside = true;
        int button_width = 0,button_height = 0;
        switch(sizeB) {
case MAIN_BUTTON:
    {
         button_width = MAIN_BUTTON_WIDTH;
         button_height = MAIN_BUTTON_HEIGHT;
         break;
    }
case GAME_BUTTON:
    {
        button_width = GAME_BUTTON_WIDTH;
        button_height = GAME_BUTTON_HEIGHT;
        break;
    }
case SKIN_PICKED:
    {
        button_width = SKIN_PICKED_WIDTH;
        button_height = SKIN_PICKED_HEIGHT;
        break;
    }
}
        if(x < pPosition.x) inside = false;
        else if (x > pPosition.x + button_width) inside = false;
        else if (y < pPosition.y) inside = false;
        else if (y > pPosition.y + button_height) inside = false;
        if(inside&&e->type == SDL_MOUSEBUTTONDOWN) picked = 1;
        return inside;
    }
    return false;
}
void Button::render(SDL_Renderer* renderer, SDL_Rect* currentClip, SDL_Texture* texture,int kind)
{
    int width = 0,height = 0;
    switch(kind) {
    case GAME_BUTTON:
        {
            width = GAME_BUTTON_WIDTH;
            height = GAME_BUTTON_HEIGHT;
            break;
        }
    case MAIN_BUTTON:
        {
            width = MAIN_BUTTON_WIDTH;
            height = MAIN_BUTTON_HEIGHT;
            break;
        }
    case SKIN_PICKED:
        {
            width = SKIN_PICKED_WIDTH;
            height = SKIN_PICKED_HEIGHT;
            break;
        }
    }
    SDL_Rect renderQuad = {pPosition.x, pPosition.y, width, height};
    SDL_RenderCopy(renderer, texture, currentClip, &renderQuad);
}
void setSkin(Button* b1, Button* b2, Button* b3,SDL_Event e, Mix_Chunk* sound, int& _highScore, TTF_Font* font, SDL_Renderer* renderer)
{
    if(b1->picked) b1->currentSprite = BUTTON_MOUSE_OVER;
        else if(b1->handleEventInside(&e,SKIN_PICKED)) {
                b1->currentSprite = BUTTON_MOUSE_OVER;
                if(b2->picked || b3->picked) if(b1->picked ) {
                        b2->picked = 0;
                        b3->picked = 0;
                        Mix_PlayChannel(-1,sound,0);
                    }
                }
            else b1->currentSprite = BUTTON_MOUSE_OUT;
    if(b2->picked) b2->currentSprite = BUTTON_MOUSE_OVER;
        else if(b2->handleEventInside(&e,SKIN_PICKED)) {
                b2->currentSprite = BUTTON_MOUSE_OVER;
                if(b1->picked || b3->picked) {
                        if(_highScore >= 20 && b2->picked)
                    {
                        b1->picked = 0;
                        b3->picked = 0;
                        Mix_PlayChannel(-1,sound,0);
                    }
                        else if(b2->picked)
                    {
                        b2->picked = 0;
                        Mix_PlayChannel(-1,sound,0);
                    }
                }
            }
            else b2->currentSprite = BUTTON_MOUSE_OUT;
    if(b3->picked) b3->currentSprite = BUTTON_MOUSE_OVER;
        else if(b3->handleEventInside(&e,SKIN_PICKED)) {
                b3->currentSprite = BUTTON_MOUSE_OVER;
                if(b2->picked || b1->picked) {
                        if(_highScore >= 30 && b3->picked)
                    {
                        b1->picked = 0;
                        b2->picked = 0;
                        Mix_PlayChannel(-1,sound,0);
                    }
                        else if(b3->picked)
                    {
                        b3->picked = 0;
                        Mix_PlayChannel(-1,sound,0);
                    }
                }
            }
            else b3->currentSprite = BUTTON_MOUSE_OUT;
}

void initSkin(Button* b1, Button* b2, Button* b3, int& loaded)
{
    switch(loaded) {
        case 1: {b1->picked = 1;break;}
        case 2: {b2->picked = 1;break;}
        case 3: {b3->picked = 1;break;}
    }
}
