#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
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
SDL_Rect earthrect;

int main(int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);

    // Your drawing code here
    // use SDL_RenderPresent(renderer) to show it
//    SDL_Event e;
//    bool quit = false;
//    while(!quit) while(SDL_PollEvent(&e) != 0) {
//        if(e.type == SDL_QUIT) quit = true;
//        else if(e.type == SDL_KEYDOWN) {
//            SDL_Texture* control;
//            switch(e.key.keysym.sym)
//            {
//                case SDLK_UP:
//                control=loadTexture("up.png", renderer);
//                break;
//                case SDLK_DOWN:
//                control=loadTexture("down.png",renderer);
//                break;
//                case SDLK_LEFT:
//                control=loadTexture("left.png",renderer);
//                break;
//                case SDLK_RIGHT:
//                control=loadTexture("right.png",renderer);
//                break;
//            }
//            SDL_RenderCopy( renderer, control, NULL, NULL);
//            SDL_RenderPresent(renderer);
//        }
//    }
    SDL_Texture* background = loadTexture("images/background.png",renderer);
    SDL_RenderCopy(renderer,background,NULL,NULL);
    earthrect.x = 225;
    earthrect.y = 139;
    earthrect.h = 322;
    earthrect.w = 350;
    SDL_Texture* earth = loadTexture("images/earth.png",renderer);
    SDL_RenderCopy(renderer,earth,NULL,&earthrect);
    SDL_RenderPresent(renderer);
    waitUntilKeyPressed();
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
