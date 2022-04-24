#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
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
void Button::setRect(SDL_Rect* re,int type)
{
    for(int i = 0; i < BUTTON_MOUSE_TOTAL; i++)
    {
        re[i].x = MAIN_BUTTON_WIDTH*i;
        re[i].y = MAIN_BUTTON_HEIGHT*type;
        re[i].w = MAIN_BUTTON_WIDTH;
        re[i].h = MAIN_BUTTON_HEIGHT;
    }
}
bool Button::handleEventInside(SDL_Event* e,int sizeB)
{
    if(e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
    {
        int x,y;
        SDL_GetMouseState(&x,&y);
        bool inside = true;
        int button_width,button_height;
        if (sizeB == MAIN_BUTTON)
		{
			button_width = MAIN_BUTTON_WIDTH;
			button_height = MAIN_BUTTON_HEIGHT;
		}
		else;
        if(x < pPosition.x) inside = false;
        else if (x > pPosition.x + button_width) inside = false;
        else if (y < pPosition.y) inside = false;
        else if (y > pPosition.y + button_height) inside = false;
        return inside;
    }
    return false;
}
void Button::render(SDL_Renderer* renderer, SDL_Rect* currentClip, SDL_Texture* texture)
{
    SDL_Rect renderQuad = {pPosition.x,pPosition.y,MAIN_BUTTON_WIDTH,MAIN_BUTTON_HEIGHT};
    SDL_RenderCopy(renderer, texture, currentClip, &renderQuad);
}
void Button::free(SDL_Texture* ButtonTexture)
{
	//Free texture if it exists
	if( ButtonTexture != NULL )
	{
		SDL_DestroyTexture( ButtonTexture );
		ButtonTexture = NULL;
	}
}
