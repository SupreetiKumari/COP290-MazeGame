#include<iostream>
#include<algorithm>
#include<vector>
#include<set>
#include<map>
#include<unordered_set>
#include<iterator>
#include<string>
#include<cmath>
#include<sstream>
#include<iomanip>
#include<stack>

#include<cstring>
#include<queue>
#include<SDL.h>
#include<SDL_image.h>
using namespace std;



int handleMouseEvent(SDL_Event& e, SDL_Rect rect){
    if( e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP ){
        int x, y;
        SDL_GetMouseState( &x, &y );
        bool inside = false;
        if( x > rect.x && x <= rect.x + rect.w && y > rect.y && y <= rect.y + rect.h ){
            inside = true;
        }

        if( !inside ){
            return 0;  // Mouse is outside the button
        }else{
            switch( e.type ){
                case SDL_MOUSEMOTION:
                return 1;  // Mouse is hovering over the button
                case SDL_MOUSEBUTTONDOWN:
                return 2;  // Mouse is clicking the button
                case SDL_MOUSEBUTTONUP:
                return 3;  // Mouse is releasing the button
            }
        }
    }
}


//SDL_Renderer* gRenderer = NULL;
SDL_Texture* loadTexture( std::string path )
{
    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    return newTexture;
}



