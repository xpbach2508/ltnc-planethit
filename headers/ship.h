#ifndef SHIP_H
#define SHIP_H
#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <cmath>


#define pff pair<float,float>

using namespace std;
class Bullet
{
    public:
    pff pos;
    pff dir;
    float speed = 0.03f;
    float degree;
    Bullet(pff pos);
    void Move();
    //void render();
    SDL_FRect bulletQuad;
};
class Ship
{
public:
    Ship();
    ~Ship();
    void render(SDL_Renderer* renderer = NULL,SDL_FRect nodeQuad = {},SDL_FRect planetQuad = {});
    void free();

    //Ship Charateristics
    pff pos;
    float speed = 0,rotation = rand()%361;
    SDL_Texture* shipTexture;
    float shipHeight,shipWidth;
    void Move(int i);
    double radius = 300;
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
