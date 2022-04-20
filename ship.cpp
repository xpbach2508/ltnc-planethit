#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <vector>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <cmath>

#include "headers/ship.h"
#include "headers/planet.h"
#include "headers/SDL_ultils.h"

#define Pi 3.14159265
#define f first
#define s second

using namespace std;

//BULLET
Bullet::Bullet(pff _position)
{
    pos = _position;
    dir.f = pos.f - 400 + 57.647;
    dir.s = pos.s - 400 + 59.4117;
}
void Bullet::Move()
{
    pos.f -= dir.f*speed;
    pos.s -= dir.s*speed;
}
void Ship::renderBullet(SDL_Renderer* renderer, int& i, float& degreee)
{
    SDL_FRect renderQuad = { Bullets[i].pos.f, Bullets[i].pos.s, BulletWidth/8.0f, BulletHeight/8.0f };
    Bullets[i].bulletQuad = { Bullets[i].pos.f, Bullets[i].pos.s, BulletWidth/8.0f, BulletHeight/8.0f };
    //Render to screen
    SDL_RenderCopyExF( renderer, BulletTexture, NULL, &renderQuad,degreee, NULL, SDL_FLIP_HORIZONTAL);
}
void Ship::freeBullet()
{
    if( shipTexture != NULL )
	{
		SDL_DestroyTexture( shipTexture );
		shipTexture = NULL;
        shipHeight = 0;
		shipWidth = 0;
	}
}

//SHIP
Ship::Ship()
{
    pos.f = 400 + sin(rotation*Pi/180)*radius-60;
    pos.s = 400 - cos(rotation*Pi/180)*radius-60;
}
void Ship::Move(int i)
{
    if(i == -1 || i == 1) rotation += i;
    if(radius > 220 && i == -2) radius += i;
    else if(i == 2) radius += i;

}
void Ship::Shoot()
{
    pos.f = 400 + sin(rotation*Pi/180)*radius-57.647;
    pos.s = 400 - cos(rotation*Pi/180)*radius-59.4117;
    Bullet fire(pos);
    Bullets.push_back(fire);
    Bullets[Bullets.size()-1].degree = rotation;
}

void Ship::render(SDL_Renderer* renderer,SDL_FRect nodeQuad,SDL_FRect planetQuad)
{
    if(rotation < 0) {rotation += 360;}
    pos.f = 400 + sin(rotation*Pi/180)*radius-57.647;
    pos.s = 400 - cos(rotation*Pi/180)*radius-59.4117;
    //mTexture = loadTexture("images/node.png",renderer);
    shipQuad = { pos.f, pos.s, shipWidth/1.7f, shipHeight/1.7f };
    //Render to screen
        SDL_RenderCopyExF( renderer, shipTexture, NULL, &shipQuad, rotation, NULL, SDL_FLIP_HORIZONTAL);

        for(int i = 0; i < Bullets.size(); i++)
        {
            if((Bullets[i].pos.f > 800 || Bullets[i].pos.f < 0) && (Bullets[i].pos.s < 0 || Bullets[i].pos.s > 800))
            {
                Bullets.erase(Bullets.begin() + i);
            }
            if(CheckCollision(Bullets[i].bulletQuad,nodeQuad))
            {
                score++;
                cout << score << endl;
                Bullets.erase(Bullets.begin() + i);
            }
            else if(CheckCollision(Bullets[i].bulletQuad,planetQuad)) Bullets.erase(Bullets.begin() + i);
            Bullets[i].Move();
            renderBullet(renderer,i,Bullets[i].degree);
        }
}
Ship::~Ship()
{
	//Deallocate
	free();
}
void Ship::free()
{
	//Free texture if it exists
	if( shipTexture != NULL )
	{
		SDL_DestroyTexture( shipTexture );
		shipTexture = NULL;
        shipHeight = 0;
		shipWidth = 0;
	}
}

