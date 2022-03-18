#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <cmath>
#include "headers/planet.h"
#define Pi 3.14159265

using namespace std;
//PLANET
void Planet::render(SDL_Renderer* renderer)
{
    node.render(renderer);
    //Set rendering space and render to screen
    //int x = ( 800 - EarthTexture.getWidth())/2;
    //int y = ( 600 - EarthTexture.getHeight())/2;
    SDL_Rect renderQuad = { (800 - mWidth)/2, (800-mHeight)/2 , mWidth, mHeight };
    //Render to screen
    SDL_RenderCopyEx( renderer, mTexture, NULL, &renderQuad, rotation, NULL, SDL_FLIP_HORIZONTAL);

}
Planet::Planet()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

Planet::~Planet()
{
	//Deallocate
	free();
}
bool Planet::loadFromFile( std::string path,SDL_Renderer* renderer)
{
	free();
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );
		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w/1.7f;
			mHeight = loadedSurface->h/1.7f;
		}
		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}
	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

void Planet::free()
{
	//Free texture if it exists
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}
void Planet::SetRotation(double value)
{
    rotation += value * speed;
    node.rotation += value * speed;
    if(rotation > 360) rotation -= 360;
    if(rotation < 0) rotation += 360;
}
//NODE
Node::Node()
{
    srand(time(NULL));
    rotation = rand() % (360 + 1);
    x = 400 + sin(rotation*Pi/180)*140;
    y = 400 + cos(rotation*Pi/180)*140;
}
Node::~Node()
{
    free();
}
void Node::free()
{
    if(mTexture != NULL) {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}
void Node::render(SDL_Renderer* renderer)
{
    //Set rendering space and render to screen
    //int x = ( 800 - EarthTexture.getWidth())/2;
    //int y = ( 600 - EarthTexture.getHeight())/2;
    if(rotation < 0) {rotation += 360;}
    x = 400 + sin(rotation*Pi/180)*140-29;
    y = 400 - cos(rotation*Pi/180)*140-29;
    //mTexture = loadTexture("images/node.png",renderer);
    SDL_FRect renderQuad = { x, y, mWidth, mHeight };
    //Render to screen
    //SDL_RenderCopyEx( renderer, mTexture, NULL, &renderQuad, rotation, NULL, SDL_FLIP_HORIZONTAL);
    SDL_RenderCopyF(renderer,mTexture,NULL,&renderQuad);
}
bool Node::loadFromFile( std::string path,SDL_Renderer* renderer)
{
	free();
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );
		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w/1.0f;
			mHeight = loadedSurface->h/1.0f;
		}
		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}
	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

