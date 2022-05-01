#ifndef SHIP_H
#define SHIP_H
#include <vector>

#include "planet.h"
#include "SDL_ultils.h"

#define f first
#define s second
#define pff pair<float,float>

using namespace std;
class Bullet
{
    public:
    pff pos;
    pff dir;
    float speed = 0.03f;
    float degree;
    Bullet(pff pos, float BulletW, float BulletH);
    void Move();
    //void render();
    SDL_FRect bulletQuad;
};
class Ship
{
public:
    Ship();
    ~Ship();
    void render(SDL_Renderer* renderer = NULL,SDL_FRect nodeQuad = {},SDL_FRect planetQuad = {},Mix_Chunk* shot = NULL,Mix_Chunk* collide=NULL);
    void free();

    //Ship Charateristics
    pff pos;
    float speed = 0,rotation = rand()%361;
    SDL_Texture* shipTexture;
    float shipHeight,shipWidth;
    void Move(int i);
    double radius = 300;
    int health;
    SDL_Texture* shipHealthTexture;
    //Bullets
    SDL_Texture* BulletTexture;
    float BulletWidth,BulletHeight;
    void renderBullet(SDL_Renderer* renderer,int& i, float& degreee);
    vector<Bullet> Bullets;
    void freeBullet();
    void Shoot();
    //Check collision
    SDL_FRect shipQuad{};
    //score
    int score = 0;

};

#endif // SHIP_H
