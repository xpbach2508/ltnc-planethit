#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <cmath>
#include "headers/planet.h"

using namespace std;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;
const string WINDOW_TITLE = "Let's go";

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);

void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal = false);

void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
void waitUntilKeyPressed();


SDL_Texture* loadTexture(string path, SDL_Renderer* renderer);
int main(int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);

    Planet EarthTexture;
    if(!EarthTexture.node.loadFromFile("images/node.png",renderer)) cout << "Failed to load node\n";
    if(EarthTexture.loadFromFile("images/earth.png",renderer)==0)
            cout << "Failed to load Earth\n";
    bool quit = false;
    SDL_Event e;
    while(!quit) {
        SDL_RendererFlip flipType = SDL_FLIP_HORIZONTAL;
        while(SDL_PollEvent(&e)!=0) {
            if(e.type==SDL_QUIT) {
                quit = true;
            }
            else if(e.type == SDL_KEYDOWN)
            switch (e.key.keysym.sym) {
                case SDLK_q:
                quit = true;
                break;
            }
        }
        //Clear screen
        SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( renderer );

        EarthTexture.render(renderer);
        EarthTexture.SetRotation(0.5f);

        SDL_RenderPresent( renderer );
    }
    quitSDL(window, renderer);
    return 0;
}

SDL_Texture* loadTexture(string path, SDL_Renderer* renderer)
{
    SDL_Texture* newTexture = nullptr;
    SDL_Surface* loadedSurface = IMG_Load( path.c_str());
    if( loadedSurface == nullptr)
        cout << "Unable to load image " << path << " SDL_image Error: "
             << IMG_GetError() << endl;
    else {
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface);
        if( newTexture == nullptr) cout << "Unable to create texture from " << path << "SDL Error:"
                                << SDL_GetError() << endl;
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(std::cout, "SDL_Init", true);

    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
       SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    //window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
       //SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (window == nullptr) logSDLError(std::cout, "CreateWindow", true);


    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);
    //renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));

    if (renderer == nullptr) logSDLError(std::cout, "CreateRenderer", true);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}
void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_WaitEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}
