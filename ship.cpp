#include "headers/ship.h"

using namespace std;

//BULLET
Bullet::Bullet(pff _position, float BulletW, float BulletH)
{
    pos = _position;
    dir.f = pos.f - SCREEN_WIDTH/2 + BulletW/2.0f;
    dir.s = pos.s - SCREEN_HEIGHT/2+ BulletH/2.0f;
}
void Bullet::Move()
{
    pos.f -= dir.f*speed;
    pos.s -= dir.s*speed;
}
void Ship::renderBullet(SDL_Renderer* renderer, int& i, float& degreee)
{
    SDL_FRect renderQuad = { Bullets[i].pos.f, Bullets[i].pos.s, BulletWidth, BulletHeight };
    Bullets[i].bulletQuad = { Bullets[i].pos.f, Bullets[i].pos.s, BulletWidth, BulletHeight };
    //Render to screen
    SDL_RenderCopyExF( renderer, BulletTexture, NULL, &renderQuad,degreee, NULL, SDL_FLIP_HORIZONTAL);
}
void Ship::freeBullet()
{
    if( shipTexture != NULL )
	{
		SDL_DestroyTexture( BulletTexture );
		BulletTexture = NULL;
        BulletHeight = 0;
		BulletWidth = 0;
	}
}

//SHIP
Ship::Ship()
{
    pos.f = SCREEN_WIDTH/2 + sin(rotation*Pi/180)*radius-shipWidth/2;
    pos.s = SCREEN_HEIGHT/2 - cos(rotation*Pi/180)*radius-shipHeight/2;
    health = 5;
}
void Ship::Move(int i)
{
    if(i == -1 || i == 1) rotation += i;
    if(radius > 220 && i == -2) radius += i;
    else if(pos.f < SCREEN_WIDTH && pos.s < SCREEN_HEIGHT && pos.f > 0 && pos.s > 0 && i == 2) radius += i;
    //cout << pos.f << " " << pos.s << endl;

}
void Ship::Shoot()
{
    pos.f = SCREEN_WIDTH/2 + sin(rotation*Pi/180)*radius - BulletWidth/2.0f;
    pos.s = SCREEN_HEIGHT/2 - cos(rotation*Pi/180)*radius - BulletHeight/2.0f;
    Bullet fire(pos,BulletWidth,BulletWidth);
    Bullets.push_back(fire);
    Bullets[Bullets.size()-1].degree = rotation;
}

void Ship::render(SDL_Renderer* renderer,SDL_FRect nodeQuad,SDL_FRect planetQuad)
{
    for(int i = 0; i < health; i++) {
        SDL_Rect dRect = {HEALTH_POSX+30*(5-i),HEALTH_POSY,30,30};
        SDL_RenderCopy(renderer,shipHealthTexture,NULL,&dRect);
    }
    if(rotation < 0) {rotation += 360;}
    pos.f = SCREEN_WIDTH/2 + sin(rotation*Pi/180)*radius-shipWidth/2;
    pos.s = SCREEN_HEIGHT/2 - cos(rotation*Pi/180)*radius-shipHeight/2;
    shipQuad = { pos.f, pos.s, shipWidth, shipHeight };

    for(int i = 0; i < Bullets.size(); i++)
    {
        if((Bullets[i].pos.f > SCREEN_WIDTH || Bullets[i].pos.f < 0) && (Bullets[i].pos.s < 0 || Bullets[i].pos.s > SCREEN_HEIGHT))
        {
            Bullets.erase(Bullets.begin() + i);
        }
        if(CheckCollision(Bullets[i].bulletQuad,nodeQuad))
        {
            score++;
            cout << score << endl;
            Bullets.erase(Bullets.begin() + i);
        }
        else if(CheckCollision(Bullets[i].bulletQuad,planetQuad)) Bullets.erase(Bullets.begin() + i),cout << Bullets[i].pos.f << " " << Bullets[i].pos.s << endl;
        Bullets[i].Move();
        renderBullet(renderer,i,Bullets[i].degree);
    }
    SDL_RenderCopyExF( renderer, shipTexture, NULL, &shipQuad, rotation, NULL, SDL_FLIP_HORIZONTAL);
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

