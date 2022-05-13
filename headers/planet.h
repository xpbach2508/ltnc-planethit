#ifndef PLANET_H
#define PLANET_H
#include "SDL_ultils.h"

#define Pi 3.14159265

using namespace std;
class   Node
{
    public:
        void render(SDL_Renderer* renderer=NULL, Circle* planetCircle = NULL);
        float x,y;
        float rotation;
        SDL_Texture* Texture;
        float Width;
        float Height;
        //Restart the node
        void Restart();
        //Collision Box
        SDL_FRect renderQuad;
        Circle nodeCir;

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
        Circle planetCir;
};
#endif // PLANET_H
