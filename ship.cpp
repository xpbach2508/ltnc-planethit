#include "headers/ship.h"

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
    Bullets[i].bulletCir = {Bullets[i].pos.f + BulletWidth/2, Bullets[i].pos.s + BulletHeight/2, BulletWidth/2};
    //need to be fixed
    //Render to screen
    SDL_RenderCopyExF( renderer, BulletTexture, NULL, &renderQuad,degreee, NULL, SDL_FLIP_HORIZONTAL);
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
    pos.f = SCREEN_WIDTH/2 + sin(rotation*Pi/180)*radius - BulletWidth/2;
    pos.s = SCREEN_HEIGHT/2 - cos(rotation*Pi/180)*radius - BulletHeight/2;
    Bullet fire(pos,BulletWidth,BulletWidth);
    Bullets.push_back(fire);
    Bullets[Bullets.size()-1].degree = rotation;
}

void Ship::render(SDL_Renderer* renderer,Circle* nodeCir,Circle* planetCir,Mix_Chunk* shot,Mix_Chunk* collide)
{
    if(rotation < 0) {rotation += 360;}
    pos.f = SCREEN_WIDTH/2 + sin(rotation*Pi/180)*radius-shipWidth/2;
    pos.s = SCREEN_HEIGHT/2 - cos(rotation*Pi/180)*radius-shipHeight/2;
    shipQuad = { pos.f, pos.s, shipWidth, shipHeight };
    shipCir = {pos.f + shipWidth/2, pos.s + shipHeight/2, shipWidth/2};

    for(int i = 0; i < Bullets.size(); i++)
    {
        if((Bullets[i].pos.f > SCREEN_WIDTH || Bullets[i].pos.f < 0) && (Bullets[i].pos.s < 0 || Bullets[i].pos.s > SCREEN_HEIGHT))
        {
            Bullets.erase(Bullets.begin() + i);
        }
        if(checkCollision2(Bullets[i].bulletCir,*nodeCir))
        {
            score++;
            //cout << score << endl;
            Bullets.erase(Bullets.begin() + i);
            Mix_PlayChannel(-1,collide,0);
        }
        else if(checkCollision2(Bullets[i].bulletCir,*planetCir)) {
                Bullets.erase(Bullets.begin() + i);
                std::cout << Bullets[i].pos.f << " " << Bullets[i].pos.s << std::endl;
                Mix_PlayChannel(-1,collide,0);
        }
        Bullets[i].Move();
        renderBullet(renderer,i,Bullets[i].degree);
        //std::cout << "rendered bullet" << std::endl;
    }
    SDL_RenderCopyExF( renderer, shipTexture, NULL, &shipQuad, rotation, NULL, SDL_FLIP_HORIZONTAL);
    //std::cout << "rendered ship" << std::endl;
}
Ship::~Ship()
{
	//Deallocate
	free();
}
void Ship::free()
{
	//Free texture if it exists
	freeTexture(shipTexture);
	freeTexture(BulletTexture);
    freeTexture(shipHealthTexture);
}

