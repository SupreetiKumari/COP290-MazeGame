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

void Dot::move()
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
    else if(checkCollision( PlayerCollider, walls )){
        mPosX -= mVelX; PlayerCollider.x = mPosX;
    }
    //Move the dot up or down
    
    //If the dot went too far up or down
    if( ( mPosY < 0 ) || ( mPosY + DOT_HEIGHT > SCREEN_HEIGHT ) )
    {
        //Move back
        mPosY -= mVelY;
        PlayerCollider.y = mPosY;
       
    }
    else if(checkCollision( PlayerCollider, walls )){
        mPosY -= mVelY;
        PlayerCollider.y = mPosY;
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
	void Dot::render1()
{
    //Show the dot
	gDotTexture.render( mPosX, mPosY );
}
void Dot::render2()
{
    //Show the dot
    gDot2Texture.render( mPosX, mPosY );
}
bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
            if( TTF_Init() < 0 )
            {
                printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
                success = false;
            }
		}
	}

	return success;
}
	//
	
	void close()
{
	//Free loaded images
	gDotTexture.free();

	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}
int main( int argc, char* args[] )
{
    Music musicobj = Music();
    server player1;
    string clientdata = "",data ="";
   
    cout<<clientdata<<"\n";
    PlayerCollider.w =  5;
    PlayerCollider.h = 5;
    int setting = (int)(rand()%3) +1 ;
    setting=3;Uint32 timepassed = 0; timepassed=SDL_GetTicks();
    if(setting == 1)
    {
        bool quit10=true;bool quit9=true;bool quit8=true;bool quit7=true;
    walls = setWalls();
   // walls.push_back(createwall(153,28,486,86));
       musicobj.maintune();
    points=set1Points();
        point1s=set1Point1s();point2s=set1Point2s();point3s=set1Point3s();
	//Start up SDL and create window
	init();
	//Load media
	loadMedia();
	SDL_Color textColor = { 0, 0x00, 0x00 };
//    giitdelhiTexture.render(0,0);
//    SDL_RenderPresent( gRenderer );
//    SDL_Delay(2000);
	// SDL_RenderPresent( gRenderer );
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;
    while(!quit){
       // musicobj.keypress2();
        while( SDL_PollEvent( &e ) != 0 ){
            if( e.type == SDL_QUIT ){
                close();
                return 0;
            }
            int x = handleMouseEvent(e, createwall(548,443,339,110));
            if(x == 0){
                gstartTexture.render(0,0);
                SDL_RenderPresent( gRenderer );
            }else if(x == 1){
                
                gstartdarkTexture.render(0,0);
                SDL_RenderPresent( gRenderer );
            }else if(x == 2){
                musicobj.keypress();
                quit = true;
            }
        }
    }quit=false;
    while(!quit){
       // musicobj.keypress3();
        while( SDL_PollEvent( &e ) != 0 ){
            if( e.type == SDL_QUIT ){
                close();
                return 0;
            }
          
            int x = handleMouseEvent(e, createwall(313,648,372,164));
            if(x == 0){
                gokmenuTexture.render(0,0);
                SDL_RenderPresent( gRenderer );
            }else if(x == 1){
                gokmenudarkTexture.render(0,0);
                SDL_RenderPresent( gRenderer );
            }else if(x == 2){
                musicobj.keypress();
                quit = true;
            }
        }
    }
			//The dot that will be moving around on the screen
			Dot dot;
        Dot dot2;
            int cc=0;
    quit=false; bool taskscreen = false;
        bool hint1=false;  bool hint2=false;  bool hint3=false;  bool hint4=false;  bool hint5=false;  bool hint6=false;  bool hint7=false;  bool hint8=false;  bool hint9=false;  bool hint10=false; bool hint11=false;
			//While application is running
			while( !quit )
			{
                score1=dot.cpoint1;
                if( !instructionsanswer.loadFromRenderedText( to_string(score1), textColor ) )
                    {
                    printf( "Failed to render text texture!\n" );
                 }
                if( !instructionscore.loadFromRenderedText( "SCORE=", textColor ) )
                    {
                                
                        printf( "Failed to render text texture!\n" );
                 //   success = false;
                    }
//                if( !timetexture.loadFromRenderedText( "TIME LEFT=", textColor ) )
//                    {
//
//                        printf( "Failed to render text texture!\n" );
//                 //   success = false;
//                    }
                if( !timeatexture.loadFromRenderedText( to_string(300-(SDL_GetTicks()/1000)), textColor ) )
                    {
                                
                        printf( "Failed to render text texture!\n" );
                 //   success = false;
                    }
                
                data="";
                data+= to_string(dot.mPosX);
                data += "_";
                data += to_string(dot.mPosY);
                data += "_";
                data += to_string(dot.cpoint1);
                data += "_";
                data += to_string(dot.lives);
				//Handle events on queue
                data="";
            data+= to_string(dot.mPosX);
            data += "_";
            data += to_string(dot.mPosY);
            data += "_";
            data += to_string(dot.cpoint1);
                data += "_";
                data += to_string(dot.lives);
                clientdata = player1.sendrecieve(data);
                opponent op3 = getopponentdata(clientdata);
                dot2.mPosX=op3.x;
                dot2.mPosY=op3.y;
                dot2.cpoint1=op3.s;
                dot2.lives=op3.l;
                if(dot.cpoint1>=6000)
                {
                    ggamewontexture.render(0,0);
                    SDL_RenderPresent( gRenderer );SDL_Delay(1000);quit=true;
                    
                }
                 
