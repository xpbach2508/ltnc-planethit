#include "headers/planet.h"


using namespace std;
//PLANET
void Planet::render(SDL_Renderer* renderer)
{
    node.render(renderer);
    planetQuad = { (SCREEN_WIDTH - Width)/2, (SCREEN_HEIGHT-Height)/2 , Width, Height };
    //Render to screen
    SDL_RenderCopyExF( renderer, Texture, NULL, &planetQuad, rotation, NULL, SDL_FLIP_HORIZONTAL);

}
Planet::Planet()
{
	//Initialize
	Texture = NULL;
	Width = 0;
	Height = 0;
	health = 5;
}

Planet::~Planet()
{
	//Deallocate
	free();
}

void Planet::free()
{
	//Free texture if it exists
	if( Texture != NULL )
	{
		SDL_DestroyTexture( Texture );
		Texture = NULL;
		Width = 0;
		Height = 0;
	}
}
void Planet::SetRotation(Uint32 value)
{
    if(value%1000 > 900 && lastChange + 10000 < value) clockwise = - clockwise,lastChange = value;
    rotation += clockwise * speed;
    node.rotation += clockwise * speed;
    if(rotation > 360) rotation -= 360;
    if(rotation < 0) rotation += 360;
}

//NODE
void Node::Restart()
{
    rotation = rand() % (360 + 1);
}
Node::~Node()
{
    free();
}
void Node::free()
{
    if(Texture != NULL) {
        SDL_DestroyTexture(Texture);
        Texture = NULL;
        Width = 0;
        Height = 0;
    }
}
void Node::render(SDL_Renderer* renderer)
{
    //Set rendering space and render to screen
    //int x = ( 800 - EarthTexture.getWidth())/2;
    //int y = ( 600 - EarthTexture.getHeight())/2;
    if(rotation < 0) {rotation += 360;}
    x = SCREEN_WIDTH/2 + sin(rotation*Pi/180)*140-29;
    y = SCREEN_HEIGHT/2 - cos(rotation*Pi/180)*140-29;
    //mTexture = loadTexture("images/node.png",renderer);
    renderQuad = { x, y, Width, Height };
    //Render to screen
    SDL_RenderCopyExF( renderer, Texture, NULL, &renderQuad, rotation, NULL, SDL_FLIP_HORIZONTAL);
    //SDL_RenderCopyF(renderer,Texture,NULL,&renderQuad);
}
