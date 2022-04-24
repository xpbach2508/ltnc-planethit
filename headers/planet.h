#ifndef PLANET_H
#define PLANET_H
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <cmath>

using namespace std;
class   Node
{
    public:
        ~Node();
        void free();
        void render(SDL_Renderer* renderer=NULL);
        float x,y;
        float rotation;
        SDL_Texture* Texture;
        float Width;
        float Height;
        //Restart the node
        void Restart();
        //Collision Box
        SDL_FRect renderQuad;

};
class   Planet
{
    public:
        //Rotation
        float rotation;
        void SetRotation(Uint32 value);
        Uint32 lastChange = -1;
        int clockwise = 1;
        //Speed
        float speed = 0.5;
        //Node in planet
        Node node;
        //Initializes variables
        Planet();

        //Deallocates memory
        ~Planet();

        //Deallocates texture
        void free();

        //Renders texture at given point
        void render(SDL_Renderer* renderer=NULL);

        //The actual hardware texture
        SDL_Texture* Texture;
        //Image dimensions
        float Width;
        float Height;
        //Collision Box
        SDL_FRect planetQuad;
};
#endif // PLANET_H
