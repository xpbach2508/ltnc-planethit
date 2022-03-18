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
        Node();

        ~Node();

        void free();
        bool loadFromFile( std::string path,SDL_Renderer* renderer);
        void render(SDL_Renderer* renderer=NULL);
        float rotation;
        float x,y;
    private:
        SDL_Texture* mTexture;
        int mWidth;
        int mHeight;
};
class   Planet
{
    public:
        //Rotation
        float rotation;
        void SetRotation(double value);
        //Speed
        float speed = 1;
        //Node in planet
        Node node;
        //Initializes variables
        Planet();

        //Deallocates memory
        ~Planet();

        //Loads image at specified path
        bool loadFromFile( std::string path,SDL_Renderer* renderer);
        //Deallocates texture
        void free();

        //Renders texture at given point
        void render(SDL_Renderer* renderer=NULL);

        //The actual hardware texture
        SDL_Texture* mTexture;
        //Image dimensions
        int mWidth;
        int mHeight;
};
#endif // PLANET_H
