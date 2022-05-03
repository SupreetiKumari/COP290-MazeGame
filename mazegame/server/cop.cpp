#include <SDL.h>
#include <SDL_image.h>
#include<SDL_ttf.h>
#include <stdio.h>
#include <string>
#include<array>
#include<iostream>
#include<algorithm>
#include<vector>
#include<set>
#include<unordered_set>
#include<iterator>
#include<string>
#include<cmath>
#include<sstream>
#include<map>
#include<iomanip>
#include<stack>
#include<cstring>
#include<queue>
#include "music.hpp"
#include "helper.cpp"
#include "sdl_helper.cpp"
// #include "server.hpp"
using namespace std;
//Screen dimension constants
const int SCREEN_WIDTH = 1439;
const int SCREEN_HEIGHT = 860;


#if defined(SDL_TTF_MAJOR_VERSION)
bool LTexture::loadFromRenderedText( std::string textureText, SDL_Color textColor )
{
    //Get rid of preexisting texture
    //free();

    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
    if( textSurface != NULL )
    {
        //Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
        if( mTexture == NULL )
        {
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }
        else
        {
            //Get image dimensions
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }

        //Get rid of old surface
        SDL_FreeSurface( textSurface );
    }
    else
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }

    
    //Return success
    return mTexture != NULL;
}
#endif



//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;
SDL_Texture* gTexture = NULL;
//The window renderer


//Scene textures
LTexture gDotTexture;
LTexture gDot2Texture;
LTexture instruction1;

void Dot::handleEvent( SDL_Event& e )
{
    //If a key was pressed
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY -= DOT_VEL; break;
            case SDLK_DOWN: mVelY += DOT_VEL; break;
            case SDLK_LEFT: mVelX -= DOT_VEL; break;
            case SDLK_RIGHT: mVelX += DOT_VEL; break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY += DOT_VEL; break;
            case SDLK_DOWN: mVelY -= DOT_VEL; break;
            case SDLK_LEFT: mVelX += DOT_VEL; break;
            case SDLK_RIGHT: mVelX -= DOT_VEL; break;
        }
    }
}


void Dot::move1()
{
    // cout<<cpoint<<"\n";
     //Move the dot left or right
     mPosX += mVelX;mPosY += mVelY;
     PlayerCollider.x = mPosX;
     PlayerCollider.y = mPosY;
     //If the dot went too far to the left or right
     if( ( mPosX < 0 ) || ( mPosX + DOT_WIDTH > SCREEN_WIDTH ) )
     {
         //Move back
         mPosX -= mVelX; PlayerCollider.x = mPosX;
     }
//     else if(checkCollision( PlayerCollider, walls )){
//         mPosX -= mVelX; PlayerCollider.x = mPosX;
//     }
     //Move the dot up or down
     
     //If the dot went too far up or down
     if( ( mPosY < 0 ) || ( mPosY + DOT_HEIGHT > SCREEN_HEIGHT ) )
     {
         //Move back
         mPosY -= mVelY;
         PlayerCollider.y = mPosY;
        
     }
//     else if(checkCollision( PlayerCollider, walls )){
//         mPosY -= mVelY;
//         PlayerCollider.y = mPosY;
//     }
}
