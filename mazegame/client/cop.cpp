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
	
bool loadMedia()
{
    // Loading success flag
    bool success = true;
    gFont = TTF_OpenFont("lazy.ttf", 28);
    SDL_Color textColor = {0, 0xff, 0xff};

    gTexture = loadTexture("/Users/arushigoyal/Downloads/task2/background.png");

    if (gTexture == NULL)
    {
        printf("Failed to load texture image!\n");
        success = false;
    }
    gTexture1 = loadTexture("/Users/arushigoyal/Downloads/task2/karakoram.png");

    if (gTexture == NULL)
    {
        printf("Failed to load texture image!\n");
        success = false;
    }
    // Load dot texture
    if (!gDotTexture.loadFromFile("player1.png"))
    {
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if (!gDot2Texture.loadFromFile("player2.png"))
    {
        printf("Failed to load dot texture!\n");
        success = false;
    }
    // gcoin50texture,gdiamondtexture,gemerald100teexture ,ggold175texture,gpearl25texture, gruby150texture,gsapphire200texture,gsilver75texture
    if (!gcoin50texture.loadFromFile("coin.png"))
    {
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if (!lives1texture.loadFromFile("lives1.png"))
    {
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if (!lives2texture.loadFromFile("lives2.png"))
    {
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if (!lives3texture.loadFromFile("lives3.png"))
    {
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if (!gdiamondtexture.loadFromFile("diamond.png"))
    {
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if (!gemerald100teexture.loadFromFile("emerald.png"))
    {
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if (!ggold175texture.loadFromFile("gold.png"))
    {
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if (!gpearl25texture.loadFromFile("pearl.png"))
    {
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if (!gruby150texture.loadFromFile("ruby.png"))
    {
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if (!gsapphire200texture.loadFromFile("sapphire.png"))
    {
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if (!gsilver75texture.loadFromFile("silver.png"))
    {
        printf("Failed to load dot texture!\n");
        success = false;
    }
    // gwarning1texture,gwarning2texture,gwarning3texture,gwarning4texture,gwarning5texture,gwarning6texture,gwarning7texture,gwarning8texture,gwarning9texture;
    if (!gwarning1texture.loadFromFile("warning1.png"))
    {
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if (!gwarning2texture.loadFromFile("warning2.png"))
    {
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if (!gwarning3texture.loadFromFile("warning3.png"))
    {
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if (!gwarning4texture.loadFromFile("warning4.png"))
    {
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if (!gwarning5texture.loadFromFile("warning5.png"))
    {
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if (!gwarning6texture.loadFromFile("warning6.png"))
    {
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if (!gwarning7texture.loadFromFile("warning7.png"))
    {
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if (!gwarning8texture.loadFromFile("warning8.png"))
    {
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if (!gwarning9texture.loadFromFile("warning9.png"))
    {
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if (!ghint1texture.loadFromFile("hint1.png"))
    {
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if (!ghint2texture.loadFromFile("hint2.png"))
    {
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if (!ghint3texture.loadFromFile("hint3.png"))
    {
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if (!ghint4texture.loadFromFile("hint4.png"))
    {
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if (!ghint5texture.loadFromFile("hint5.png"))
    {
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if (!ghint6texture.loadFromFile("hint6.png"))
    {
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if (!ghint7texture.loadFromFile("hint7.png"))
    {
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if (!ghint8texture.loadFromFile("hint8.png"))
    {
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if (!ghint9texture.loadFromFile("hint9.png"))
    {
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if (!ghint10texture.loadFromFile("hint10.png"))
    {
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if (!ghint11texture.loadFromFile("hint11.png"))
    {
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if (!ghint12texture.loadFromFile("hint12.png"))
    {
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if (!ghint13texture.loadFromFile("hint13.png"))
    {
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if (!ghint14texture.loadFromFile("hint14.png"))
    {
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if (!ghint15texture.loadFromFile("hint15.png"))
    {
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if (!ghint16texture.loadFromFile("hint16.png"))
    {
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if (!ghint17texture.loadFromFile("hint17.png"))
    {
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if (!ghint18texture.loadFromFile("hint18.png"))
    {
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if (!ghint19texture.loadFromFile("hint19.png"))
    {
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if (!ghint20texture.loadFromFile("hint20.png"))
    {
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if (!ghint21texture.loadFromFile("hint21.png"))
    {
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if (!ghint22texture.loadFromFile("hint22.png"))
    {
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if (!ghint23texture.loadFromFile("hint23.png"))
    {
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if (!ghint24texture.loadFromFile("hint24.png"))
    {
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if (!ghint25texture.loadFromFile("hint25.png"))
    {
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if (!ghint26texture.loadFromFile("hint26.png"))
    {
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if (!ghint27texture.loadFromFile("hint27.png"))
    {
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if (!ghint28texture.loadFromFile("hint28.png"))
    {
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if (!ghint29texture.loadFromFile("hint29.png"))
    {
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if (!ghint30texture.loadFromFile("hint30.png"))
    {
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if (!ggamewontexture.loadFromFile("gamewon.png"))
    {
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if (!ggamefinishtexture.loadFromFile("gamefinish.png"))
    {
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if (!ggameovertexture.loadFromFile("gameover.png"))
    {
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if (!gpenalty1texture.loadFromFile("penalty1.png"))
    {
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if (!gpenalty2texture.loadFromFile("penalty2.png"))
    {
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if (!gpenalty3texture.loadFromFile("penalty3.png"))
    {
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if (!gpenalty4texture.loadFromFile("penalty4.png"))
    {
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if (!gpenalty5texture.loadFromFile("penalty5.png"))
    {
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if (!gpenalty6texture.loadFromFile("penalty6.png"))
    {
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if (!gpenalty7texture.loadFromFile("penalty7.png"))
    {
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if (!gpenalty8texture.loadFromFile("penalty8.png"))
    {
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if (!gpenalty9texture.loadFromFile("penalty9.png"))
    {
        printf("Failed to load dot texture!\n");
        success = false;
    }

    if (!gstartTexture.loadFromFile("/Users/arushigoyal/Downloads/task2/startmenu.png"))
    {
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if (!gstartdarkTexture.loadFromFile("/Users/arushigoyal/Downloads/task2/startmenudark.png"))
    {
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if (!gokmenuTexture.loadFromFile("/Users/arushigoyal/Downloads/task2/okmenu.png"))
    {
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if (!gokmenudarkTexture.loadFromFile("/Users/arushigoyal/Downloads/task2/okmenudark.png"))
    {
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if (!giitdelhiTexture.loadFromFile("/Users/arushigoyal/Downloads/task2/iitdelhi.png"))
    {
        printf("Failed to load dot texture!\n");
        success = false;
    }
    if (!gtasksmenuTexture.loadFromFile("/Users/arushigoyal/Downloads/task2/sapphire.png"))
    {
        printf("Failed to load dot texture!\n");
        success = false;
    }

    return success;
}

