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

class LTexture
{
    public:
        //Initializes variables
        LTexture();

        //Deallocates memory
        ~LTexture();

        //s image at specified path
        bool loadFromFile( std::string path );
        
        #if defined(SDL_TTF_MAJOR_VERSION)
        //Creates image from font string
        bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
        #endif

        //Deallocates texture
        void free();

        //Set color modulation
        void setColor( Uint8 red, Uint8 green, Uint8 blue );

        //Set blending
        void setBlendMode( SDL_BlendMode blending );

        //Set alpha modulation
        void setAlpha( Uint8 alpha );
        
        //Renders texture at given point
        void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

        //Gets image dimensions
        int getWidth();
        int getHeight();
        SDL_Texture* getTexture();

    private:
        //The actual hardware texture
        SDL_Texture* mTexture;

        //Image dimensions
        int mWidth;
        int mHeight;
};

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

class LTimer
{
    public:
        //Initializes variables
        LTimer();

        //The various clock actions
        void start();
        void stop();
        void pause();
        void unpause();

        //Gets the timer's time
        Uint32 getTicks();

        //Checks the status of the timer
        bool isStarted();
        bool isPaused();

    private:
        //The clock time when the timer started
        Uint32 mStartTicks;

        //The ticks stored when the timer was paused
        Uint32 mPausedTicks;

        //The timer status
        bool mPaused;
        bool mStarted;
};

//The dot that will move around on the screen
class Dot
{
    public:
        //The dimensions of the dot
        static const int DOT_WIDTH = 5;
        static const int DOT_HEIGHT = 5;

        //Maximum axis velocity of the dot
        static const int DOT_VEL = 4;

        //Initializes the variables
        Dot();

        //Takes key presses and adjusts the dot's velocity
        void handleEvent( SDL_Event& e );

        //Moves the dot
        void move();

        //Shows the dot on the screen
        void render1();
    void render2();
            //The X and Y offsets of the dot
        int mPosX, mPosY;
    int cpoint ,lives;
        //The velocity of the dot
        int mVelX, mVelY;
};

LTexture::LTexture()
{
    //Initialize
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}


LTexture::~LTexture()
{
    //Deallocate
    free();
}

SDL_Renderer* gRenderer = NULL;
bool LTexture::loadFromFile( std::string path )
{
//Get rid of preexisting texture
free();

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
    //Color key image
    SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

    //Create texture from surface pixels
    newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
    if( newTexture == NULL )
    {
        printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
    }
    else
    {
        //Get image dimensions
        mWidth = loadedSurface->w;
        mHeight = loadedSurface->h;
    }

    //Get rid of old loaded surface
    SDL_FreeSurface( loadedSurface );
}

//Return success
mTexture = newTexture;
return mTexture != NULL;
}


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

SDL_Texture* LTexture::getTexture(){
    return mTexture;
}
// void LTexture::free()
// {
//     //Free texture if it exists
//     if( mTexture != NULL )
//     {
//         SDL_DestroyTexture( mTexture );
//         mTexture = NULL;
//         mWidth = 0;
//         mHeight = 0;
//     }
// }

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
    //Modulate texture rgb
    SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void LTexture::setBlendMode( SDL_BlendMode blending )
{
    //Set blending function
    SDL_SetTextureBlendMode( mTexture, blending );
}
        
void LTexture::setAlpha( Uint8 alpha )
{
    //Modulate texture alpha
    SDL_SetTextureAlphaMod( mTexture, alpha );
}


// void LTexture::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
// {
//     //Set rendering space and render to screen
//     SDL_Rect renderQuad = { x, y, mWidth, mHeight };

//     //Set clip rendering dimensions
//     if( clip != NULL )
//     {
//         renderQuad.w = clip->w;
//         renderQuad.h = clip->h;
//     }

//     //Render to screen
//     SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip );
// }

int LTexture::getWidth()
{
    return mWidth;
}

int LTexture::getHeight()
{
    return mHeight;
}

Dot::Dot()
{
    //Initialize the offsets
    mPosX = 0;
    mPosY = 0;
    cpoint=0;lives=2;
    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;
}

