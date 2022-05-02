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
    int width,height;
    if(kind == 1) {
         width = MAIN_BUTTON_WIDTH;
         height = MAIN_BUTTON_HEIGHT;
    }
    if(kind == 2) {
        width = GAME_BUTTON_WIDTH;
        height = GAME_BUTTON_HEIGHT;
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
        int button_width,button_height;
        if (sizeB == MAIN_BUTTON)
		{
			button_width = MAIN_BUTTON_WIDTH;
			button_height = MAIN_BUTTON_HEIGHT;
		}
		else if(sizeB == GAME_BUTTON) {
            button_width = GAME_BUTTON_WIDTH;
            button_height = GAME_BUTTON_HEIGHT;
		}
        if(x < pPosition.x) inside = false;
        else if (x > pPosition.x + button_width) inside = false;
        else if (y < pPosition.y) inside = false;
        else if (y > pPosition.y + button_height) inside = false;
        return inside;
    }
    return false;
}
void Button::render(SDL_Renderer* renderer, SDL_Rect* currentClip, SDL_Texture* texture,int kind)
{
    int width,height;
    if(kind == 1) {
         width = MAIN_BUTTON_WIDTH;
         height = MAIN_BUTTON_HEIGHT;
    }
    if(kind == 2) {
        width = GAME_BUTTON_WIDTH;
        height = GAME_BUTTON_HEIGHT;
    }
    SDL_Rect renderQuad = {pPosition.x, pPosition.y, width, height};
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
