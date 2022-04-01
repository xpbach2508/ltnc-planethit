#ifndef ASTEROIDS_H
#define ASTEROIDS_H
#include <iostream>
#include <time.h>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <cmath>

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
};


#endif // ASTEROIDS_H


