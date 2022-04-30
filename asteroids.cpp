#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <vector>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <cmath>

#include "headers/asteroids.h"

using namespace std;
#define f first
#define s second


asteroid::asteroid()
{
    int ran = rand()%4;
    int rand2 = rand()%3 + 1;
    rotation = rand()%361;
    switch(ran)
    {
        case 0:
            pos.f = rand() % 801;
            pos.s = -50;
            velocity.f = (rand()%41-20) / 20 * rand2;
            velocity.s = 1* rand2;
            break;
        case 1:
            pos.f = rand() % 801;
            pos.s = 850;
            velocity.f = (rand()%41-20) / 20 * rand2;
            velocity.s = -1 * rand2;
            break;
        case 2:
            pos.f = -50;
            pos.s = rand() % 801;
            velocity.f = 1 * rand2;
            velocity.s = (rand()%41-20) / 20 * rand2;
            break;
        case 3:
            pos.f = 850;
            pos.s = rand() % 801;
            velocity.f = -1 * rand2;
            velocity.s = (rand()%41-20) / 20 * rand2;
            break;
    }
}
void asteroid::render(SDL_Renderer* renderer,SDL_Texture* asterTexture, float asterWidth, float asterHeight)
{
    asterQuad = { pos.f, pos.s , asterWidth, asterWidth };
    //Render to screen
    SDL_RenderCopyExF( renderer, asterTexture, NULL, &asterQuad, rotation, NULL, SDL_FLIP_HORIZONTAL);
}

void asteroid::moving()
{
    pos.f += velocity.f;
    pos.s += velocity.s;
    rotation += 0.5;
}
