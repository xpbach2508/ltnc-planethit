#include "headers/planet.h"


using namespace std;
//PLANET
void Planet::render(SDL_Renderer* renderer)
{
    node.render(renderer,&planetCir);
    planetQuad = { (SCREEN_WIDTH - Width)/2, (SCREEN_HEIGHT-Height)/2 , Width, Height };
    planetCir = {SCREEN_WIDTH/2, SCREEN_HEIGHT/2, Width/2};
    //Render to screen
    SDL_RenderCopyExF( renderer, Texture, NULL, &planetQuad, rotation, NULL, SDL_FLIP_HORIZONTAL);
    //std::cout << planetCir.r << std::endl;

}
Planet::Planet()
{
	//Initialize
	Texture = NULL;
	Width = 0;
	Height = 0;
}

Planet::~Planet()
{
	//Deallocate
	free();
}

void Planet::free()
{
	//Free texture if it exists
	freeTexture(Texture);
	freeTexture(node.Texture);
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
void Node::render(SDL_Renderer* renderer, Circle* planetCircle)
{
    nodeCir.r = Width/2;
    if(rotation < 0) rotation += 360;
    x = SCREEN_WIDTH/2 + sin(rotation*Pi/180)*(nodeCir.r/4 + planetCircle->r)-Width/2;
    y = SCREEN_HEIGHT/2 - cos(rotation*Pi/180)*(nodeCir.r/4 + planetCircle->r)-Height/2;
    renderQuad = { x, y, Width, Height };
    nodeCir.x = x + nodeCir.r;
    nodeCir.y = y + nodeCir.r;
    //Render to screen
    SDL_RenderCopyExF( renderer, Texture, NULL, &renderQuad, rotation, NULL, SDL_FLIP_HORIZONTAL);
    //std::cout << "rendered node" << std::endl;
}
