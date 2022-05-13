#include "headers/asteroids.h"

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
    asterCir = {pos.f-asterWidth/2, pos.s - asterHeight/2, asterWidth/2};
    //Render to screen
    SDL_RenderCopyExF( renderer, asterTexture, NULL, &asterQuad, rotation, NULL, SDL_FLIP_HORIZONTAL);
    //std::cout << "rendered asteroid" << std::endl;
}

void asteroid::moving()
{
    pos.f += velocity.f;
    pos.s += velocity.s;
    rotation += 0.5;
}
