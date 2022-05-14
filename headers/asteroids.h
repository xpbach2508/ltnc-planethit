#ifndef ASTEROIDS_H
#define ASTEROIDS_H

#include "GAME_ultils.h"

using namespace std;
#define pff pair<float,float>

class asteroid
{
    public:
        pff pos;
        pff velocity;
        float rotation;

        asteroid();

        void render(SDL_Renderer* renderer = nullptr,SDL_Texture* asterTexture = nullptr,float asterWidth = 0, float asterHeight = 0);

        void moving();

        SDL_FRect asterQuad{};
        Circle asterCir{};
};


#endif // ASTEROIDS_H


