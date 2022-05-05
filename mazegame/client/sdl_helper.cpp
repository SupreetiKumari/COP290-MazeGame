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
    void move(); void move1();

        //Shows the dot on the screen
        void render1();
    void render2();
            //The X and Y offsets of the dot
        int mPosX, mPosY;
    int cpoint ,lives,cpoint1;
        //The velocity of the dot
        int mVelX, mVelY;
};
