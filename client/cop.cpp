/*This source code copyrighted by Lazy Foo' Productions (2004-2022)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
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
#include "Dot.cpp"
#include "LTimer.cpp"
#include "LTexture.cpp"
#include "sdl_helper.cpp"
 #include "client.hpp"

using namespace std;
//Screen dimension constants
const int SCREEN_WIDTH = 1439;
const int SCREEN_HEIGHT = 860;
SDL_Rect PlayerCollider;
vector<SDL_Rect> walls;
TTF_Font *gFont = NULL;
int c;
vector<pair<SDL_Rect,int>> points;
vector<pair<SDL_Rect,int>> point1s;
vector<pair<SDL_Rect,int>> point2s;
vector<pair<SDL_Rect,int>> point3s;

//Texture wrapper class
//int arr[200];
vector<int> arr(6500, 0);
vector<int> arr2(5500, 0);
int score1=0;

LTexture gTextTexture,gstartTexture, gstartdarkTexture,giitdelhiTexture,gokmenuTexture, gokmenudarkTexture,gtasksmenuTexture,gcoin50texture,gdiamondtexture,gemerald100teexture,ggold175texture,gpearl25texture,gruby150texture,gsapphire200texture,gsilver75texture,gwarning1texture,gwarning2texture,gwarning3texture,gwarning4texture,gwarning5texture,gwarning6texture,gwarning7texture,gwarning8texture,gwarning9texture,gpenalty1texture,gpenalty2texture,gpenalty3texture,gpenalty4texture,gpenalty5texture,gpenalty6texture,gpenalty7texture,gpenalty8texture,gpenalty9texture;
//The application time based timer
LTexture ghint1texture,ghint2texture,ghint3texture,ghint4texture,ghint5texture,ghint6texture,ghint7texture,ghint8texture,ghint9texture,ghint10texture,ghint11texture,ghint12texture,ghint13texture,ghint14texture,ghint15texture,ghint16texture,ghint17texture,ghint18texture,ghint19texture,ghint20texture,ghint21texture,ghint22texture,ghint23texture,ghint24texture,ghint25texture,ghint26texture,ghint27texture,ghint28texture,ghint29texture,ghint30texture,
ggamewontexture,ggamewon1texture,ggameovertexture,ggamefinishtexture;

struct opponent{
    int x, y, s,l;};

opponent getopponentdata(string s){
    string temp = "";
    vector<int> v;
    for(int i=0;i<s.size();i++){
        if(s[i] != '_'){
            temp += s[i];
        }else{
            v.push_back(stoi(temp));
            temp = "";
        }
    }
    v.push_back(stoi(temp));
    opponent op;
    op.x = v[0];
    op.y = v[1];
    op.s = v[2];
    op.l= v[3];
    return op;
}
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

SDL_Texture* gTexture1=NULL;
SDL_Texture* gTexture2=NULL;
SDL_Texture* gTexture3=NULL;
//Scene textures
LTexture gDotTexture;
LTexture gDot2Texture;
LTexture instructionscore,instructionsanswer;
LTexture timetexture,timeatexture;
LTexture lives1texture,lives2texture,lives3texture;

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
void renderOutline(int pointer){
    SDL_Rect Outline;
    if(pointer == 0){
        Outline = {59,149,101,101};
    }else if(pointer == 1){
        Outline = {300,60,100,100};
    }else if(pointer == 2){
        Outline = {379,149,101,101};
    }else{
        Outline = {539,149,101,101};
    }
    SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF );
    SDL_RenderDrawRect( gRenderer, &Outline );
}
SDL_Rect clip1= {600,100,426,500};
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
    // gcoin50texture,gdiamondtexture,gemerald100teexture ,ggold175texture,gpearl25texture, gruby150texture,gsapphire200texture,gsilver75texture
    if(checkCollision2( PlayerCollider, points ))
    {
        int x= amountreturn( PlayerCollider, points);
      
        if( x>=0 &&  (x==5000) && arr[x]==0){
            cpoint = cpoint + x;
           // giitdelhiTexture.render(300,60);
          //  SDL_RenderPresent( gRenderer );
           // SDL_Delay(3000);
            mPosY -= mVelY;
            PlayerCollider.y = mPosY;mPosX -= mVelX; PlayerCollider.x = mPosX;arr[x]=1;}
        
        if( x>=0 &&  (x==75) && arr[x]==0){
            cpoint1 = cpoint1 + x;
   // gtasksmenuTexture.render(0,0);
            gsilver75texture.render(506.5,180.5);
            SDL_RenderPresent( gRenderer );
            SDL_Delay(3000);
            mPosY -= mVelY;
            PlayerCollider.y = mPosY;mPosX -= mVelX; PlayerCollider.x = mPosX;arr[x]=1;}

        if( x>=0 &&  (x==200) && arr[x]==0){
            cpoint1 = cpoint1 + x;
   // gtasksmenuTexture.render(0,0);
            gsapphire200texture.render(506.5,180.5);
            SDL_RenderPresent( gRenderer );
            SDL_Delay(3000);
            mPosY -= mVelY;
            PlayerCollider.y = mPosY;mPosX -= mVelX; PlayerCollider.x = mPosX;arr[x]=1;}
        
        if( x>=0 &&  (x==150) && arr[x]==0){
            cpoint1 = cpoint1 + x;
   // gtasksmenuTexture.render(0,0);
            gruby150texture.render(506.5,180.5);
            SDL_RenderPresent( gRenderer );
            SDL_Delay(3000);
            mPosY -= mVelY;
            PlayerCollider.y = mPosY;mPosX -= mVelX; PlayerCollider.x = mPosX;arr[x]=1;}
        
        if( x>=0 &&  (x==25) && arr[x]==0){
            cpoint1 = cpoint1 + x;
   // gtasksmenuTexture.render(0,0);
            gpearl25texture.render(506.5,180.5);
            SDL_RenderPresent( gRenderer );
            SDL_Delay(3000);
            mPosY -= mVelY;
            PlayerCollider.y = mPosY;mPosX -= mVelX; PlayerCollider.x = mPosX;arr[x]=1;}
        
        if( x>=0 &&  (x==175) && arr[x]==0){
            cpoint1 = cpoint1 + x;
   // gtasksmenuTexture.render(0,0);
            ggold175texture.render(506.5,180.5);
            SDL_RenderPresent( gRenderer );
            SDL_Delay(3000);
            mPosY -= mVelY;
            PlayerCollider.y = mPosY;mPosX -= mVelX; PlayerCollider.x = mPosX;arr[x]=1;}
        
        if( x>=0 &&  (x==100) && arr[x]==0){
            cpoint1 = cpoint1 + x;
   // gtasksmenuTexture.render(0,0);
            gemerald100teexture.render(506.5,180.5);
            SDL_RenderPresent( gRenderer );
            SDL_Delay(3000);
            mPosY -= mVelY;
            PlayerCollider.y = mPosY;mPosX -= mVelX; PlayerCollider.x = mPosX;arr[x]=1;}
        
        if( x>=0 &&  (x==50) && arr[x]==0){
            cpoint1 = cpoint1 + x;
   // gtasksmenuTexture.render(0,0);
            gcoin50texture.render(506.5,180.5);
            SDL_RenderPresent( gRenderer );
            SDL_Delay(3000);
            mPosY -= mVelY;
            PlayerCollider.y = mPosY;mPosX -= mVelX; PlayerCollider.x = mPosX;arr[x]=1;}
       

    
        //penalty
        if(x<0  && arr2[5500+x]==0 && x== -50 )
        {
            lives--;
            cpoint1 = cpoint1 + x;
            gpenalty1texture.render(531.5,180);
            SDL_RenderPresent( gRenderer );SDL_Delay(2000);
            mPosY -= mVelY;
            PlayerCollider.y = mPosY;mPosX -= mVelX; PlayerCollider.x = mPosX;
            arr2[5500+x]=1;
        }
        if(x<0  && arr2[5500+x]==0 && x== -100 )
        {
            lives--;
            cpoint1 = cpoint1 + x;
            gpenalty2texture.render(531.5,180);
            SDL_RenderPresent( gRenderer );SDL_Delay(2000);
            mPosY -= mVelY;
            PlayerCollider.y = mPosY;mPosX -= mVelX; PlayerCollider.x = mPosX;
            arr2[5500+x]=1;
        }
        if(x<0 && arr2[5500+x]==0 && x== -75 )
        {
            lives--;
            cpoint1 = cpoint1 + x;
            gpenalty3texture.render(531.5,180);
            SDL_RenderPresent( gRenderer );SDL_Delay(2000);
            mPosY -= mVelY;
            PlayerCollider.y = mPosY;mPosX -= mVelX; PlayerCollider.x = mPosX;
            arr2[5500+x]=1;
        }
        if(x<0 && arr2[5500+x]==0 && x== -115 )
        {
            lives--;
            cpoint1 = cpoint1 + x;
            gpenalty4texture.render(531.5,180);
            SDL_RenderPresent( gRenderer );SDL_Delay(2000);
            mPosY -= mVelY;
            PlayerCollider.y = mPosY;mPosX -= mVelX; PlayerCollider.x = mPosX;
            arr2[5500+x]=1;
        }
        if(x<0 && arr2[5500+x]==0 && x== -60 )
        {
            lives--;
            cpoint1 = cpoint1 + x;
            gpenalty5texture.render(531.5,180);
            SDL_RenderPresent( gRenderer );SDL_Delay(2000);
            mPosY -= mVelY;
            PlayerCollider.y = mPosY;mPosX -= mVelX; PlayerCollider.x = mPosX;
            arr2[5500+x]=1;
        }
        if(x<0 && arr2[5500+x]==0 && x== -200 )
        {
            lives--;
            cpoint1 = cpoint1 + x;
            gpenalty6texture.render(531.5,180);
            SDL_RenderPresent( gRenderer );SDL_Delay(2000);
            mPosY -= mVelY;
            PlayerCollider.y = mPosY;mPosX -= mVelX; PlayerCollider.x = mPosX;
            arr2[5500+x]=1;
        }
        if(x<0 && arr2[5500+x]==0 && x== -150 )
        {
            lives--;
            cpoint1 = cpoint1 + x;
            gpenalty9texture.render(531.5,180);
            SDL_RenderPresent( gRenderer );SDL_Delay(2000);
            mPosY -= mVelY;
            PlayerCollider.y = mPosY;mPosX -= mVelX; PlayerCollider.x = mPosX;
            arr2[5500+x]=1;
        }
        if(x<0 && arr2[5500+x]==0 && x== -175 )
        {
            lives--;
            cpoint1 = cpoint1 + x;
            gpenalty7texture.render(531.5,180);
            SDL_RenderPresent( gRenderer );SDL_Delay(2000);
            mPosY -= mVelY;
            PlayerCollider.y = mPosY;mPosX -= mVelX; PlayerCollider.x = mPosX;
            arr2[5500+x]=1;
        }
        if(x<0 && arr2[5500+x]==0 && x== -25 )
        {
            lives--;
            cpoint1 = cpoint1 + x;
            gpenalty8texture.render(531.5,180);
            SDL_RenderPresent( gRenderer );SDL_Delay(2000);
            mPosY -= mVelY;
            PlayerCollider.y = mPosY;mPosX -= mVelX; PlayerCollider.x = mPosX;
            arr2[5500+x]=1;
        }
        
    }

    
        }


void Dot::move1()
{
    
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
    if(checkCollision2( PlayerCollider, point1s ))
    {
        int x= amountreturn( PlayerCollider, point1s);
      
        if( x>=0 &&  (x==6000) && arr[x]==0){
            cpoint1 = cpoint1 + x;
           // giitdelhiTexture.render(300,60);
          //  SDL_RenderPresent( gRenderer );
           // SDL_Delay(3000);
            mPosY -= mVelY;
            PlayerCollider.y = mPosY;mPosX -= mVelX; PlayerCollider.x = mPosX;arr[x]=1;}
    }}

void Dot::move2()
{
    
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
    if(checkCollision2( PlayerCollider, point2s ))
    {
        int x= amountreturn( PlayerCollider, point2s);
      
        if( x>=0 &&  (x==6000) && arr[x]==0){
            cpoint1 = cpoint1 + x;
           // giitdelhiTexture.render(300,60);
          //  SDL_RenderPresent( gRenderer );
           // SDL_Delay(3000);
            mPosY -= mVelY;
            PlayerCollider.y = mPosY;mPosX -= mVelX; PlayerCollider.x = mPosX;arr[x]=1;}
    }}


void Dot::move3()
{
    
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
    if(checkCollision2( PlayerCollider, point3s ))
    {
        int x= amountreturn( PlayerCollider, point3s);
      
        if( x>=0 &&  (x==6000) && arr[x]==0){
            cpoint1 = cpoint1 + x;
           // giitdelhiTexture.render(300,60);
          //  SDL_RenderPresent( gRenderer );
           // SDL_Delay(3000);
            mPosY -= mVelY;
            PlayerCollider.y = mPosY;mPosX -= mVelX; PlayerCollider.x = mPosX;arr[x]=1;}
    }}
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

bool loadMedia()
{
	//Loading success flag
	bool success = true;
    gFont = TTF_OpenFont( "resources/lazy.ttf", 28 );
    SDL_Color textColor = { 0,0x00,0x00 };

    
    gTexture = loadTexture( "resources/background.png" );

    if( gTexture == NULL )
    {
        printf( "Failed to load texture image!\n" );
        success = false;
    }
     gTexture1 = loadTexture( "resources/karakoram.png" );

    if( gTexture1 == NULL )
    {
        printf( "Failed to load texture image!\n" );
        success = false;
    }
    gTexture2 = loadTexture( "resources/jwalamukhi.png" );

    if( gTexture2 == NULL )
    {
        printf( "Failed to load texture image!\n" );
        success = false;
    }
    gTexture3 = loadTexture( "resources/dograhall.png" );

    if( gTexture3 == NULL )
    {
        printf( "Failed to load texture image!\n" );
        success = false;
    }
	//Load dot texture
	if( !gDotTexture.loadFromFile( "resources/player1.png" ) )
	{
		printf( "Failed to load dot texture!\n" );
		success = false;
	}
    if( !timetexture.loadFromFile( "resources/clock.png" ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    }
    if( !gDot2Texture.loadFromFile( "resources/player2.png" ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    }
    // gcoin50texture,gdiamondtexture,gemerald100teexture ,ggold175texture,gpearl25texture, gruby150texture,gsapphire200texture,gsilver75texture
    if( !gcoin50texture.loadFromFile( "treasure/coin.png" ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    }
    if( !lives1texture.loadFromFile( "resources/lives1.png" ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    }
    if( !lives2texture.loadFromFile( "resources/lives2.png" ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    }
    if( !lives3texture.loadFromFile( "resources/lives3.png" ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    }
   
    if( !gemerald100teexture.loadFromFile( "treasure/emerald.png" ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    }
    if( !ggold175texture.loadFromFile( "treasure/gold.png" ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    }
    if( !gpearl25texture.loadFromFile( "treasure/pearl.png" ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    }
    if( !gruby150texture.loadFromFile( "treasure/ruby.png" ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    }
    if( !gsapphire200texture.loadFromFile( "treasure/sapphire.png" ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    }
    if( !gsilver75texture.loadFromFile( "treasure/silver.png" ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    }
    // gwarning1texture,gwarning2texture,gwarning3texture,gwarning4texture,gwarning5texture,gwarning6texture,gwarning7texture,gwarning8texture,gwarning9texture;
    if( !gwarning1texture.loadFromFile( "warning/warning1.png" ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    }
    if( !gwarning2texture.loadFromFile( "warning/warning2.png" ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    }
    if( !gwarning3texture.loadFromFile( "warning/warning3.png" ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    }
    if( !gwarning4texture.loadFromFile( "warning/warning4.png" ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    }
    if( !gwarning5texture.loadFromFile( "warning/warning5.png" ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    }
    if( !gwarning6texture.loadFromFile( "warning/warning6.png" ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    }
    if( !gwarning7texture.loadFromFile( "warning/warning7.png" ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    }
    if( !gwarning8texture.loadFromFile( "warning/warning8.png" ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    }
    if( !gwarning9texture.loadFromFile( "warning/warning9.png" ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    }
    if( !ghint1texture.loadFromFile( "hints/hint1.png" ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    }
    if( !ghint2texture.loadFromFile( "hints/hint2.png" ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    } if( !ghint3texture.loadFromFile( "hints/hint3.png" ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    } if( !ghint4texture.loadFromFile( "hints/hint4.png" ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    } if( !ghint5texture.loadFromFile( "hints/hint5.png" ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    } if( !ghint6texture.loadFromFile( "hints/hint6.png" ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    } if( !ghint7texture.loadFromFile( "hints/hint7.png" ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    } if( !ghint8texture.loadFromFile( "hints/hint8.png" ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    }
    if( !ghint9texture.loadFromFile( "hints/hint9.png" ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    }
    if( !ghint10texture.loadFromFile( "hints/hint10.png" ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    }
    if( !ghint11texture.loadFromFile( "hints/hint11.png" ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    }
    if( !ghint12texture.loadFromFile( "hints/hint12.png" ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    }
    if( !ghint13texture.loadFromFile( "hints/hint13.png" ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    }
    if( !ghint14texture.loadFromFile( "hints/hint14.png" ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    }
    if( !ghint15texture.loadFromFile( "hints/hint15.png" ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    }
    if( !ghint16texture.loadFromFile( "hints/hint16.png" ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    }
    if( !ghint17texture.loadFromFile( "hints/hint17.png" ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    }
    if( !ghint18texture.loadFromFile( "hints/hint18.png" ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    }
    if( !ghint19texture.loadFromFile( "hints/hint19.png" ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    }
    if( !ghint20texture.loadFromFile( "hints/hint20.png" ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    }
    if( !ghint21texture.loadFromFile( "hints/hint21.png" ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    }
    if( !ghint22texture.loadFromFile( "hints/hint22.png" ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    }
    if( !ghint23texture.loadFromFile( "hints/hint23.png" ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    }
    if( !ghint24texture.loadFromFile( "hints/hint24.png" ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    }
    if( !ghint25texture.loadFromFile( "hints/hint25.png" ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    }
    if( !ghint26texture.loadFromFile( "hints/hint26.png" ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    }
    if( !ghint27texture.loadFromFile( "hints/hint27.png" ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    }
    if( !ghint28texture.loadFromFile( "hints/hint28.png" ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    }
    if( !ghint29texture.loadFromFile( "hints/hint29.png" ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    }
    if( !ghint30texture.loadFromFile( "hints/hint30.png" ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    }
    if( !ggamewontexture.loadFromFile( "resources/gamewon.png" ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    }
    if( !ggamewon1texture.loadFromFile( "resources/gamewon1.png" ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    }
    if( !ggamefinishtexture.loadFromFile( "resources/gamefinish.png" ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    }
    if( !ggameovertexture.loadFromFile( "resources/gameover.png" ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    }
    if( !gpenalty1texture.loadFromFile( "penalty/penalty1.png" ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    }
    if( !gpenalty2texture.loadFromFile( "penalty/penalty2.png" ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    }
    if( !gpenalty3texture.loadFromFile( "penalty/penalty3.png" ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    }
    if( !gpenalty4texture.loadFromFile( "penalty/penalty4.png" ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    }
    if( !gpenalty5texture.loadFromFile( "penalty/penalty5.png" ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    }
    if( !gpenalty6texture.loadFromFile( "penalty/penalty6.png" ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    }
    if( !gpenalty7texture.loadFromFile( "penalty/penalty7.png" ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    }
    if( !gpenalty8texture.loadFromFile( "penalty/penalty8.png" ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    }
    if( !gpenalty9texture.loadFromFile( "penalty/penalty9.png" ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    }
   
    if( !gstartTexture.loadFromFile( "resources/startmenu.png" ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    }if( ! gstartdarkTexture.loadFromFile( "resources/startmenudark.png" ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    }
    if( ! gokmenuTexture.loadFromFile( "resources/okmenu.png" ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    }
    if( ! gokmenudarkTexture.loadFromFile( "resources/okmenudark.png" ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    }
    if( !giitdelhiTexture.loadFromFile( "resources/iitdelhi.png" ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    }
    if( !gtasksmenuTexture.loadFromFile( "treasure/sapphire.png" ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    }
	

	return success;
}

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
    client player1;
    string clientdata = "",data ="";
   
    cout<<clientdata<<"\n";
    PlayerCollider.w =  5;
    PlayerCollider.h = 5;
    int setting = (int)(rand()%2) +2 ;
 Uint32 timepassed = 0; timepassed=SDL_GetTicks();
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
                if( !timeatexture.loadFromRenderedText( to_string(120-(SDL_GetTicks()/1000)), textColor ) )
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
                
                if(dot.lives<=0)
                {
                    ggameovertexture.render(0,0);
                    SDL_RenderPresent( gRenderer );SDL_Delay(1000);
                    
                }
                data="";
            data+= to_string(dot.mPosX);
            data += "_";
            data += to_string(dot.mPosY);
            data += "_";
            data += to_string(dot.cpoint1);
                data += "_";
                data += to_string(dot.lives);
                clientdata = player1.sendrecieve(data);
                opponent op2 = getopponentdata(clientdata);
                dot2.mPosX=op2.x;
                dot2.mPosY=op2.y;
                dot2.cpoint1=op2.s;dot2.lives=op2.l;
               
                if(dot2.cpoint1>=6000)
                {
                    ggameovertexture.render(0,0);
                    SDL_RenderPresent( gRenderer );SDL_Delay(1000);quit=true;
                    
                }
//                if(dot.lives > 0 )
//                SDL_RenderPresent( gRenderer );
                data="";
            data+= to_string(dot.mPosX);
            data += "_";
            data += to_string(dot.mPosY);
            data += "_";
            data += to_string(dot.cpoint1);
                data += "_";
                    data += to_string(dot.lives);
                clientdata = player1.sendrecieve(data);
                opponent op7 = getopponentdata(clientdata);
                dot2.mPosX=op7.x;
                dot2.mPosY=op7.y;
                dot2.cpoint1=op7.s;dot2.lives=op7.l;
                cout<<dot2.lives<<"\n";
                if(dot2.lives<=0)
                {
                    ggamewon1texture.render(0,0);
                    SDL_RenderPresent( gRenderer );SDL_Delay(1000);
                    
                }
                data="";
            data+= to_string(dot.mPosX);
            data += "_";
            data += to_string(dot.mPosY);
            data += "_";
            data += to_string(dot.cpoint1); data += "_";
                data += to_string(dot.lives);
                clientdata = player1.sendrecieve(data);
                opponent op5 = getopponentdata(clientdata);
                dot2.mPosX=op5.x;
                dot2.mPosY=op5.y;
                dot2.cpoint1=op5.s;dot2.lives=op5.l;
                 if((120-(SDL_GetTicks()/1000)) <= 5 && dot.cpoint1 > dot2.cpoint1)
                {
                    ggamewon1texture.render(0,0);
                    SDL_RenderPresent( gRenderer );SDL_Delay(1000);
                }
                data="";
            data+= to_string(dot.mPosX);
            data += "_";
            data += to_string(dot.mPosY);
            data += "_";
            data += to_string(dot.cpoint1);
                data += "_";
                    data += to_string(dot.lives);
                clientdata = player1.sendrecieve(data);
                opponent op6 = getopponentdata(clientdata);
                dot2.mPosX=op6.x;
                dot2.mPosY=op6.y;
                dot2.cpoint1=op6.s;
                dot2.lives=op6.l;
                 if((120-(SDL_GetTicks()/1000)) <= 5 && dot.cpoint1 <  dot2.cpoint1)
                {
                    ggameovertexture.render(0,0);
                    SDL_RenderPresent( gRenderer );SDL_Delay(1000);
                }
                if(  (120-(SDL_GetTicks()/1000)) <= 5 || dot.lives<=0 || dot2.lives<=0) quit=true;
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
                    else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE && !taskscreen){
                        taskscreen = true;
                    }else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE){
                        taskscreen = false;
                    }
                    else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_1 && !hint1){
                        hint1 = true;
                    }else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_1){
                        hint1 = false;
                    }
                    else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_2 && !hint2){
                        hint2 = true;
                    }else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_2){
                        hint2 = false;
                    }
                    else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_a && !hint3){
                        hint3 = true;
                    }else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_a){
                        hint3 = false;
                    }
                    else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_3 && !hint4){
                        hint4 = true;
                    }else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_3){
                        hint4 = false;
                    }
                    else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_4 && !hint5){
                        hint5 = true;
                    }else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_4){
                        hint5 = false;
                    }
                    else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_b && !hint6){
                        hint6 = true;
                    }else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_b){
                        hint6 = false;
                    }
                    else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_5 && !hint7){
                        hint7 = true;
                    }else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_5){
                        hint7 = false;
                    }
                    else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_6 && !hint8){
                        hint8 = true;
                    }else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_6){
                        hint8 = false;
                    }
                    else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_c && !hint9){
                        hint9 = true;
                    }else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_c){
                        hint9 = false;
                    }
                    else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_7 && !hint10){
                        hint10 = true;
                    }else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_7){
                        hint10 = false;
                    }
                    else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_8 && !hint11){
                        hint11 = true;
                    }else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_8){
                        hint11 = false;
                    }
                    else if ( dot.mPosX>=1 && dot.mPosX<=66 && dot.mPosY>=470 && dot.mPosY<=536 && e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_e )
                    {
                        //quit=true;
                        quit10=false;
                        while(!quit10)
                        {
                            score1=dot.cpoint1;
                            if( !instructionsanswer.loadFromRenderedText( to_string(score1), textColor ) )
                            {printf( "Failed to render text texture!\n" );}
                            
                            if( !instructionscore.loadFromRenderedText( "SCORE=", textColor ) )
                                {
                                            
                                    printf( "Failed to render text texture!\n" );
                             //   success = false;
                                }
//                            if( !timetexture.loadFromRenderedText( "TIME LEFT=", textColor ) )
//                                {
//
//                                    printf( "Failed to render text texture!\n" );
//                             //   success = false;
//                                }
                            if( !timeatexture.loadFromRenderedText( to_string(120-(SDL_GetTicks()/1000)), textColor ) )
                                {
                                            
                                    printf( "Failed to render text texture!\n" );
                             //   success = false;
                                }
                            while( SDL_PollEvent( &e ) != 0 )
                            {
                                //User requests quit
                                if( e.type == SDL_QUIT )
                                {quit = true;}
                                int x = handleMouseEvent(e, createwall(465,680,100,100));
                                if(x == 2){
                                    quit10 = true;
                                }
                                 if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_e )
                                {
                                    quit10=true;quit=false;}
                                //Handle input for the dot
                                dot.handleEvent( e );

                            }
                            SDL_Color textColor = { 0, 0, 0, 255 };
                                       //Current time start time
                                       Uint32 startTime = 0;
                                       //In memory text stream
                                       std::stringstream timeText;
                        //    startTime = SDL_GetTicks();
                            dot.move1();
                            data="";
                        data+= to_string(dot.mPosX);
                        data += "_";
                        data += to_string(dot.mPosY);
                        data += "_";
                        data += to_string(dot.cpoint1);
                            data += "_";
                                data += to_string(dot.lives);
                            clientdata = player1.sendrecieve(data);
                            opponent op1 = getopponentdata(clientdata);
                            dot2.mPosX=op1.x;
                            dot2.mPosY=op1.y;
                            dot2.cpoint1=op1.s;dot2.lives=op1.l;
                            SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                            SDL_RenderClear( gRenderer );
                            SDL_RenderCopy( gRenderer, gTexture1, NULL, NULL );
                            //Render objects
                           // instruction1.render(0,0);
                            instructionscore.render(240,5);
                            instructionsanswer.render(355,5);
                            timetexture.render(1116,625);
                            timeatexture.render(1210,675);
                                    if(dot.lives == 3)
                                        lives3texture.render(1103,733);
                                    if(dot.lives == 2)
                                        lives2texture.render(1103,733);
                                    if(dot.lives == 1)
                                        lives1texture.render(1103,733);
                            dot.render1();
                           dot2.render2();
                            if(dot.lives <= 0)
                            {
                                ggameovertexture.render(0,0);
                                SDL_RenderPresent( gRenderer ); SDL_Delay(2000);

                            }
                            //Update screen
                        
                            if(dot.lives > 0 )
                            SDL_RenderPresent( gRenderer );
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
                            dot2.cpoint1=op3.s;dot2.lives=op3.l;
                            if(dot.cpoint1>=6000)
                            {
                                ggamewontexture.render(0,0);
                                SDL_RenderPresent( gRenderer );SDL_Delay(1000);
                                
                            }
                            data="";
                        data+= to_string(dot.mPosX);
                        data += "_";
                        data += to_string(dot.mPosY);
                        data += "_";
                        data += to_string(dot.cpoint1);
                            data += "_";
                                data += to_string(dot.lives);
                            clientdata = player1.sendrecieve(data);
                            opponent op2 = getopponentdata(clientdata);
                            dot2.mPosX=op2.x;
                            dot2.mPosY=op2.y;
                            dot2.cpoint1=op2.s;dot2.lives=op2.l;
                            if(dot2.cpoint1>=6000)
                            {
                                ggameovertexture.render(0,0);
                                SDL_RenderPresent( gRenderer );SDL_Delay(1000);
                                
                            }
                            data="";
                        data+= to_string(dot.mPosX);
                        data += "_";
                        data += to_string(dot.mPosY);
                        data += "_";
                        data += to_string(dot.cpoint1);
                            data += "_";
                                data += to_string(dot.lives);
                            clientdata = player1.sendrecieve(data);
                            opponent op5 = getopponentdata(clientdata);
                            dot2.mPosX=op5.x;
                            dot2.mPosY=op5.y;
                            dot2.cpoint1=op5.s;dot2.lives=op5.l;
                             if((120-(SDL_GetTicks()/1000)) <= 5 && dot.cpoint1 > dot2.cpoint1)
                            {
                                ggamewon1texture.render(0,0);
                                SDL_RenderPresent( gRenderer );SDL_Delay(1000);
                            }
                            data="";
                        data+= to_string(dot.mPosX);
                        data += "_";
                        data += to_string(dot.mPosY);
                        data += "_";
                        data += to_string(dot.cpoint1);
                            data += "_";
                                data += to_string(dot.lives);
                            clientdata = player1.sendrecieve(data);
                            opponent op6 = getopponentdata(clientdata);
                            dot2.mPosX=op6.x;
                            dot2.mPosY=op6.y;
                            dot2.cpoint1=op6.s;dot2.lives=op6.l;
                             if((120-(SDL_GetTicks()/1000)) <= 5 && dot.cpoint1<  dot2.cpoint1)
                            {
                                ggameovertexture.render(0,0);
                                SDL_RenderPresent( gRenderer );SDL_Delay(1000);
                            }
                            
                            if(dot.cpoint1 >=6000 || dot2.cpoint1>=6000 || (120-(SDL_GetTicks()/1000)) <= 5 || dot.lives<=0 || dot2.lives<=0) {quit10=true;quit=true;}
                            }}

                         //   1,146,61,192

         

                             else if ( dot.mPosX>=1 && dot.mPosX<=66 && dot.mPosY>=140 && dot.mPosY<=190 && e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_e )
                    {
                        //quit=true;
                        quit9=false;
                        while(!quit9)
                        {
                            score1=dot.cpoint1;
                            if( !instructionsanswer.loadFromRenderedText( to_string(score1), textColor ) )
                            {printf( "Failed to render text texture!\n" );}
                            if( !instructionscore.loadFromRenderedText( "SCORE=", textColor ) )
                                {
                                            
                                    printf( "Failed to render text texture!\n" );
                             //   success = false;
                                }
//                            if( !timetexture.loadFromRenderedText( "TIME LEFT=", textColor ) )
//                                {
//
//                                    printf( "Failed to render text texture!\n" );
//                             //   success = false;
//                                }
//                            if( !timetexture.loadFromRenderedText( "TIME LEFT=", textColor ) )
//                                {
//
//                                    printf( "Failed to render text texture!\n" );
//                             //   success = false;
//                                }
                            if( !timeatexture.loadFromRenderedText( to_string(120-(SDL_GetTicks()/1000)), textColor ) )
                                {
                                            
                                    printf( "Failed to render text texture!\n" );
                             //   success = false;
                                }
                            while( SDL_PollEvent( &e ) != 0 )
                            {
                                //User requests quit
                                if( e.type == SDL_QUIT )
                                {quit = true;}
                                int x = handleMouseEvent(e, createwall(465,680,100,100));
                                if(x == 2){
                                    quit9 = true;
                                }
                                 if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_e )
                                {
                                    quit9=true;quit=false;}
                                //Handle input for the dot
                                dot.handleEvent( e );

                            }
                            SDL_Color textColor = { 0, 0, 0, 0 };
                                       //Current time start time
                                       Uint32 startTime = 0;
                                       //In memory text stream
                                       std::stringstream timeText;
                            startTime = SDL_GetTicks();
                            dot.move2();
                            data="";
                        data+= to_string(dot.mPosX);
                        data += "_";
                        data += to_string(dot.mPosY);
                        data += "_";
                        data += to_string(dot.cpoint1);
                            data += "_";
                                data += to_string(dot.lives);
                            clientdata = player1.sendrecieve(data);
                            opponent op1 = getopponentdata(clientdata);
                            dot2.mPosX=op1.x;
                            dot2.mPosY=op1.y;
                            dot2.cpoint1=op1.s;dot2.lives=op1.l;
                            SDL_SetRenderDrawColor( gRenderer, 0x00, 0xFF, 0xFF, 0xFF );
                            SDL_RenderClear( gRenderer );
                            SDL_RenderCopy( gRenderer, gTexture2, NULL, NULL );
                            //Render objects
                           // instruction1.render(0,0);
                            instructionscore.render(240,5);
                            instructionsanswer.render(355,5);
                            timetexture.render(1116,625);
                            timeatexture.render(1210,675);
                                    if(dot.lives == 3)
                                        lives3texture.render(1103,733);
                                    if(dot.lives == 2)
                                        lives2texture.render(1103,733);
                                    if(dot.lives == 1)
                                        lives1texture.render(1103,733);
                            dot.render1();
                           dot2.render2();
                            if(dot.lives <= 0)
                            {
                                ggameovertexture.render(0,0);
                                SDL_RenderPresent( gRenderer );SDL_Delay(2000);quit=true;
                            }
                            //Update screen
                            if(dot.lives > 0 )
                            SDL_RenderPresent( gRenderer );
                            data="";
                        data+= to_string(dot.mPosX);
                        data += "_";
                        data += to_string(dot.mPosY);
                        data += "_";
                        data += to_string(dot.cpoint1);
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
                            dot2.cpoint1=op3.s;dot2.lives=op3.l;
                            if(dot.cpoint1>=6000)
                            {
                                ggamewontexture.render(0,0);
                                SDL_RenderPresent( gRenderer );SDL_Delay(1000);
                                
                            }
                            data="";
                        data+= to_string(dot.mPosX);
                        data += "_";
                        data += to_string(dot.mPosY);
                        data += "_";
                        data += to_string(dot.cpoint1);
                            data += "_";
                                data += to_string(dot.lives);
                            clientdata = player1.sendrecieve(data);
                            opponent op2 = getopponentdata(clientdata);
                            dot2.mPosX=op2.x;
                            dot2.mPosY=op2.y;
                            dot2.cpoint1=op2.s;dot2.lives=op3.l;
                            if(dot2.cpoint1>=6000)
                            {
                                ggameovertexture.render(0,0);
                                SDL_RenderPresent( gRenderer );SDL_Delay(1000);
                                
                            }
                            data="";
                        data+= to_string(dot.mPosX);
                        data += "_";
                        data += to_string(dot.mPosY);
                        data += "_";
                        data += to_string(dot.cpoint1);
                            data += "_";
                                data += to_string(dot.lives);
                            clientdata = player1.sendrecieve(data);
                            opponent op5 = getopponentdata(clientdata);
                            dot2.mPosX=op5.x;
                            dot2.mPosY=op5.y;
                            dot2.cpoint1=op5.s;dot2.lives=op5.l;
                             if((120-(SDL_GetTicks()/1000)) <= 5 && dot.cpoint1 > dot2.cpoint1)
                            {
                                ggamewon1texture.render(0,0);
                                SDL_RenderPresent( gRenderer );SDL_Delay(1000);
                            }
                            data="";
                        data+= to_string(dot.mPosX);
                        data += "_";
                        data += to_string(dot.mPosY);
                        data += "_";
                        data += to_string(dot.cpoint1);
                            data += "_";
                                data += to_string(dot.lives);
                            clientdata = player1.sendrecieve(data);
                            opponent op6 = getopponentdata(clientdata);
                            dot2.mPosX=op6.x;
                            dot2.mPosY=op6.y;
                            dot2.cpoint1=op6.s;dot2.lives=op6.l;
                             if((120-(SDL_GetTicks()/1000)) <= 5 && dot.cpoint1<  dot2.cpoint1)
                            {
                                ggameovertexture.render(0,0);
                                SDL_RenderPresent( gRenderer );SDL_Delay(1000);
                            }
                          
                            
                            if(dot.cpoint1 >=6000 || dot2.cpoint1>=6000 || (120-(SDL_GetTicks()/1000)) <= 5 ) {quit9=true;quit=true;}

                    }}
// 1096,154,1199,223
                             else if ( dot.mPosX>=1096 && dot.mPosX<=1199 && dot.mPosY>=154 && dot.mPosY<=223 && e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_e )
                    {
                        //quit=true;
                            quit8=false;
                      while(!quit8)
                      {
                          score1=dot.cpoint1;
                          if( !instructionsanswer.loadFromRenderedText( to_string(score1), textColor ) )
                          {printf( "Failed to render text texture!\n" );}
                          if( !instructionscore.loadFromRenderedText( "SCORE=", textColor ) )
                              {
                                          
                                  printf( "Failed to render text texture!\n" );
                           //   success = false;
                              }

                          if( !timeatexture.loadFromRenderedText( to_string(120-(SDL_GetTicks()/1000)), textColor ) )
                              {
                                          
                                  printf( "Failed to render text texture!\n" );
                           //   success = false;
                              }
                          while( SDL_PollEvent( &e ) != 0 )
                          {
                              //User requests quit
                              if( e.type == SDL_QUIT )
                              {quit = true;}
                              int x = handleMouseEvent(e, createwall(465,680,100,100));
                              if(x == 2){
                                  quit8 = true;
                              }
                               if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_e )
                              {
                                  quit8=true;quit=false;}
                              //Handle input for the dot
                              dot.handleEvent( e );

                          }
                          SDL_Color textColor = { 0, 0, 0, 0 };
                                     //Current time start time
                                     Uint32 startTime = 0;
                                     //In memory text stream
                                     std::stringstream timeText;
                          startTime = SDL_GetTicks();
                          dot.move3();
                          data="";
                      data+= to_string(dot.mPosX);
                      data += "_";
                      data += to_string(dot.mPosY);
                      data += "_";
                      data += to_string(dot.cpoint1);
                          data += "_";
                              data += to_string(dot.lives);
                          clientdata = player1.sendrecieve(data);
                          opponent op1 = getopponentdata(clientdata);
                          dot2.mPosX=op1.x;
                          dot2.mPosY=op1.y;
                          dot2.cpoint1=op1.s;dot2.lives=op1.l;
                          SDL_SetRenderDrawColor( gRenderer, 0x00, 0xFF, 0xFF, 0xFF );
                          SDL_RenderClear( gRenderer );
                          SDL_RenderCopy( gRenderer, gTexture3, NULL, NULL );
                          //Render objects
                         // instruction1.render(0,0);
                          instructionscore.render(240,5);
                          instructionsanswer.render(355,5);
                          timetexture.render(1116,625);
                          timeatexture.render(1210,675);
                                  if(dot.lives == 3)
                                      lives3texture.render(1103,733);
                                  if(dot.lives == 2)
                                      lives2texture.render(1103,733);
                                  if(dot.lives == 1)
                                      lives1texture.render(1103,733);
                          dot.render1();
                         dot2.render2();
                          if(dot.lives <= 0)
                          {
                              ggameovertexture.render(0,0);
                              SDL_RenderPresent( gRenderer );SDL_Delay(2000);quit=true;
                          }
                          //Update screen
                          if(dot.lives > 0 )
                          SDL_RenderPresent( gRenderer );
                          data="";
                      data+= to_string(dot.mPosX);
                      data += "_";
                      data += to_string(dot.mPosY);
                      data += "_";
                      data += to_string(dot.cpoint1);
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
                          dot2.cpoint1=op3.s;dot2.lives=op3.l;
                          if(dot.cpoint1>=6000)
                          {
                              ggamewontexture.render(0,0);
                              SDL_RenderPresent( gRenderer );SDL_Delay(1000);
                              
                          }
                          data="";
                      data+= to_string(dot.mPosX);
                      data += "_";
                      data += to_string(dot.mPosY);
                      data += "_";
                      data += to_string(dot.cpoint1);
                          data += "_";
                              data += to_string(dot.lives);
                          clientdata = player1.sendrecieve(data);
                          opponent op2 = getopponentdata(clientdata);
                          dot2.mPosX=op2.x;
                          dot2.mPosY=op2.y;
                          dot2.cpoint1=op2.s;dot2.lives=op3.l;
                          if(dot2.cpoint1>=6000)
                          {
                              ggameovertexture.render(0,0);
                              SDL_RenderPresent( gRenderer );SDL_Delay(1000);
                              
                          }
                          data="";
                      data+= to_string(dot.mPosX);
                      data += "_";
                      data += to_string(dot.mPosY);
                      data += "_";
                      data += to_string(dot.cpoint1);
                          data += "_";
                              data += to_string(dot.lives);
                          clientdata = player1.sendrecieve(data);
                          opponent op5 = getopponentdata(clientdata);
                          dot2.mPosX=op5.x;
                          dot2.mPosY=op5.y;
                          dot2.cpoint1=op5.s;dot2.lives=op5.l;
                           if((120-(SDL_GetTicks()/1000)) <= 5 && dot.cpoint1 > dot2.cpoint1)
                          {
                              ggamewon1texture.render(0,0);
                              SDL_RenderPresent( gRenderer );SDL_Delay(1000);
                          }
                          data="";
                      data+= to_string(dot.mPosX);
                      data += "_";
                      data += to_string(dot.mPosY);
                      data += "_";
                      data += to_string(dot.cpoint1);
                          data += "_";
                              data += to_string(dot.lives);
                          clientdata = player1.sendrecieve(data);
                          opponent op6 = getopponentdata(clientdata);
                          dot2.mPosX=op6.x;
                          dot2.mPosY=op6.y;
                          dot2.cpoint1=op6.s;dot2.lives=op6.l;
                           if((120-(SDL_GetTicks()/1000)) <= 5 && dot.cpoint1<  dot2.cpoint1)
                          {
                              ggameovertexture.render(0,0);
                              SDL_RenderPresent( gRenderer );SDL_Delay(1000);
                          }
                        
                          
                          if(dot.cpoint1 >=6000 || dot2.cpoint1>=6000 || (120-(SDL_GetTicks()/1000)) <= 5 ) {quit8=true;quit=true;}

                  }}
                    int x = handleMouseEvent(e, createwall(1217,542,150,69));
                    if(x == 2){
                        quit = true;
                    }
					//Handle input for the dot
					dot.handleEvent( e );
                }
                //Move the dot
                dot.move();
                
                data="";
            data+= to_string(dot.mPosX);
            data += "_";
            data += to_string(dot.mPosY);
            data += "_";
            data += to_string(dot.cpoint1);
                data += "_";
                    data += to_string(dot.lives);
                clientdata = player1.sendrecieve(data);
              //  cout<<clientdata<<"\n";
                opponent op = getopponentdata(clientdata);
                dot2.mPosX=op.x;
                dot2.mPosY=op.y;
                dot2.cpoint1=op.s;dot2.lives=op.l;
              
              //  cout<<dot2.lives<<"\n";
                if(dot2.lives<=0)
                {
                    ggamewon1texture.render(0,0);
                    SDL_RenderPresent( gRenderer );SDL_Delay(1000);
                    
                }
                if(dot.lives <= 0)
                {ggameovertexture.render(0,0);
                    SDL_RenderPresent( gRenderer );SDL_Delay(1000);

                }
                //Update screen
//                if(dot.lives > 0 )
//                SDL_RenderPresent( gRenderer );
                if(  (120-(SDL_GetTicks()/1000)) <= 5 || dot.lives<=0 || dot2.lives<=0) quit=true;
                if(taskscreen){
                    gtasksmenuTexture.render(0,0);
                    SDL_RenderPresent( gRenderer );
                    SDL_Delay(10);
                    continue;
                }
                if(hint1){
                    ghint1texture.render(275,180);
                    SDL_RenderPresent( gRenderer );
                    SDL_Delay(10);
                    continue;
                }
                if(hint2){
                    ghint2texture.render(275,180);
                    SDL_RenderPresent( gRenderer );
                    SDL_Delay(10);
                    continue;
                }
                if(hint3){
                    gwarning1texture.render(466.5,180);
                    SDL_RenderPresent( gRenderer );
                    SDL_Delay(10);
                    continue;
                }
                if(hint4){
                    ghint3texture.render(275,180);
                    SDL_RenderPresent( gRenderer );
                    SDL_Delay(10);
                    continue;
                }
                if(hint4){
                    ghint3texture.render(275,180);
                    SDL_RenderPresent( gRenderer );
                    SDL_Delay(10);
                    continue;
                }
                if(hint5){
                    ghint4texture.render(275,180);
                    SDL_RenderPresent( gRenderer );
                    SDL_Delay(10);
                    continue;
                }
                if(hint6){
                    gwarning4texture.render(466.5,180);
                    SDL_RenderPresent( gRenderer );
                    SDL_Delay(10);
                    continue;
                }
                if(hint7){
                    ghint5texture.render(275,180);
                    SDL_RenderPresent( gRenderer );
                    SDL_Delay(10);
                    continue;
                }
                if(hint8){
                    ghint6texture.render(275,180);
                    SDL_RenderPresent( gRenderer );
                    SDL_Delay(10);
                    continue;
                }
                if(hint9){
                    gwarning7texture.render(466.5,180);
                    SDL_RenderPresent( gRenderer );
                    SDL_Delay(10);
                    continue;
                }
                if(hint10){
                    ghint7texture.render(275,180);
                    SDL_RenderPresent( gRenderer );
                    SDL_Delay(10);
                    continue;
                }
                if(hint11){
                    ghint15texture.render(275,180);
                    SDL_RenderPresent( gRenderer );
                    SDL_Delay(10);
                    continue;
                }
                SDL_Color textColor = { 0, 0, 0, 0 };

                           //Current time start time
                           Uint32 startTime = 0;

                           //In memory text stream
                           std::stringstream timeText;
                startTime = SDL_GetTicks();
				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0x00, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );
                SDL_RenderCopy( gRenderer, gTexture, NULL, NULL );
				//Render objects
				//instruction1.render(0,0);
                instructionscore.render(240,5);
                instructionsanswer.render(355,5);
                timetexture.render(1116,625);
                timeatexture.render(1210,675);
				dot.render1();
                dot2.render2();
                if(dot.lives == 3)
                    lives3texture.render(1103,733);
                if(dot.lives == 2)
                    lives2texture.render(1103,733);
                if(dot.lives == 1)
                    lives1texture.render(1103,733);
                data="";
            data+= to_string(dot.mPosX);
            data += "_";
            data += to_string(dot.mPosY);
            data += "_";
            data += to_string(dot.cpoint1);
                data += "_";
                    data += to_string(dot.lives);
                clientdata = player1.sendrecieve(data);
                opponent op8 = getopponentdata(clientdata);
                dot2.mPosX=op8.x;
                dot2.mPosY=op8.y;
                dot2.cpoint1=op8.s;dot2.lives=op8.l;
                cout<<dot2.lives<<"\n";
                if(dot2.lives<=0)
                {
                    ggamewon1texture.render(0,0);
                    SDL_RenderPresent( gRenderer );SDL_Delay(1000);
                    
                }
				if(dot.lives <= 0)
                {ggameovertexture.render(0,0);
                    SDL_RenderPresent( gRenderer );SDL_Delay(1000);

                }
				//Update screen
                if(dot.lives > 0 )
				SDL_RenderPresent( gRenderer );
                if(  (120-(SDL_GetTicks()/1000)) <= 5 || dot.lives<=0 || dot2.lives<=0) quit=true;

            }
        c=dot.cpoint1;

	//Free resources and close SDL
	
      //here
    
quit7=false;
      //  if(dot.cpoint >=6000 || dot2.cpoint1>=6000)
        while(!quit7){
            data="";
        data+= to_string(dot.mPosX);
        data += "_";
        data += to_string(dot.mPosY);
        data += "_";
        data += to_string(dot.cpoint1);
//            clientdata = player1.sendrecieve(data);
//            opponent op1 = getopponentdata(clientdata);
//            dot2.mPosX=op1.x;
//            dot2.mPosY=op1.y;
//            dot2.cpoint1=op1.s;
         //   musicobj.keypress3();
            while( SDL_PollEvent( &e ) != 0 ){
                if( e.type == SDL_QUIT ){
                    close();
                    return 0;
                }
               }
              ggamefinishtexture.render(0,0);
                    SDL_RenderPresent( gRenderer );
               
            
        }
//        quit=false
//        while(!quit)
//        {
//
//        }
        cout<<c<<"\n";}
        else if(setting == 2)
    {
      
        
        
        bool quit10=true;bool quit9=true;bool quit8=true;bool quit7=true;
        walls = setWalls();
        // walls.push_back(createwall(153,28,486,86));
          musicobj.maintune();
        points=set2Points();
            point1s=set2Point1s();point2s=set2Point2s();point3s=set2Point3s();
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
                if( !timeatexture.loadFromRenderedText( to_string(120-(SDL_GetTicks()/1000)), textColor ) )
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
                
                if(dot.lives<=0)
                {
                    ggameovertexture.render(0,0);
                    SDL_RenderPresent( gRenderer );SDL_Delay(1000);
                    
                }
                data="";
            data+= to_string(dot.mPosX);
            data += "_";
            data += to_string(dot.mPosY);
            data += "_";
            data += to_string(dot.cpoint1);
                data += "_";
                data += to_string(dot.lives);
                clientdata = player1.sendrecieve(data);
                opponent op2 = getopponentdata(clientdata);
                dot2.mPosX=op2.x;
                dot2.mPosY=op2.y;
                dot2.cpoint1=op2.s;dot2.lives=op2.l;
               
                if(dot2.cpoint1>=6000)
                {
                    ggameovertexture.render(0,0);
                    SDL_RenderPresent( gRenderer );SDL_Delay(1000);quit=true;
                    
                }
        //                if(dot.lives > 0 )
        //                SDL_RenderPresent( gRenderer );
                data="";
            data+= to_string(dot.mPosX);
            data += "_";
            data += to_string(dot.mPosY);
            data += "_";
            data += to_string(dot.cpoint1);
                data += "_";
                    data += to_string(dot.lives);
                clientdata = player1.sendrecieve(data);
                opponent op7 = getopponentdata(clientdata);
                dot2.mPosX=op7.x;
                dot2.mPosY=op7.y;
                dot2.cpoint1=op7.s;dot2.lives=op7.l;
                cout<<dot2.lives<<"\n";
                if(dot2.lives<=0)
                {
                    ggamewon1texture.render(0,0);
                    SDL_RenderPresent( gRenderer );SDL_Delay(1000);
                    
                }
                data="";
            data+= to_string(dot.mPosX);
            data += "_";
            data += to_string(dot.mPosY);
            data += "_";
            data += to_string(dot.cpoint1); data += "_";
                data += to_string(dot.lives);
                clientdata = player1.sendrecieve(data);
                opponent op5 = getopponentdata(clientdata);
                dot2.mPosX=op5.x;
                dot2.mPosY=op5.y;
                dot2.cpoint1=op5.s;dot2.lives=op5.l;
                 if((120-(SDL_GetTicks()/1000)) <= 5 && dot.cpoint1 > dot2.cpoint1)
                {
                    ggamewon1texture.render(0,0);
                    SDL_RenderPresent( gRenderer );SDL_Delay(1000);
                }
                data="";
            data+= to_string(dot.mPosX);
            data += "_";
            data += to_string(dot.mPosY);
            data += "_";
            data += to_string(dot.cpoint1);
                data += "_";
                    data += to_string(dot.lives);
                clientdata = player1.sendrecieve(data);
                opponent op6 = getopponentdata(clientdata);
                dot2.mPosX=op6.x;
                dot2.mPosY=op6.y;
                dot2.cpoint1=op6.s;
                dot2.lives=op6.l;
                 if((120-(SDL_GetTicks()/1000)) <= 5 && dot.cpoint1 <  dot2.cpoint1)
                {
                    ggameovertexture.render(0,0);
                    SDL_RenderPresent( gRenderer );SDL_Delay(1000);
                }
                if(  (120-(SDL_GetTicks()/1000)) <= 5 || dot.lives<=0 || dot2.lives<=0) quit=true;
                while( SDL_PollEvent( &e ) != 0 )
                {
                    //User requests quit
                    if( e.type == SDL_QUIT )
                    {
                        quit = true;
                    }
                    else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE && !taskscreen){
                        taskscreen = true;
                    }else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE){
                        taskscreen = false;
                    }
                    else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_1 && !hint1){
                        hint1 = true;
                    }else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_1){
                        hint1 = false;
                    }
                    else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_2 && !hint2){
                        hint2 = true;
                    }else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_2){
                        hint2 = false;
                    }
                    else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_a && !hint3){
                        hint3 = true;
                    }else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_a){
                        hint3 = false;
                    }
                    else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_3 && !hint4){
                        hint4 = true;
                    }else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_3){
                        hint4 = false;
                    }
                    else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_4 && !hint5){
                        hint5 = true;
                    }else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_4){
                        hint5 = false;
                    }
                    else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_b && !hint6){
                        hint6 = true;
                    }else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_b){
                        hint6 = false;
                    }
                    else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_5 && !hint7){
                        hint7 = true;
                    }else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_5){
                        hint7 = false;
                    }
                    else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_6 && !hint8){
                        hint8 = true;
                    }else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_6){
                        hint8 = false;
                    }
                    else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_c && !hint9){
                        hint9 = true;
                    }else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_c){
                        hint9 = false;
                    }
                    else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_7 && !hint10){
                        hint10 = true;
                    }else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_7){
                        hint10 = false;
                    }
                    else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_8 && !hint11){
                        hint11 = true;
                    }else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_8){
                        hint11 = false;
                    }
                    else if ( dot.mPosX>=1 && dot.mPosX<=66 && dot.mPosY>=470 && dot.mPosY<=536 && e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_e )
                    {
                        //quit=true;
                        quit10=false;
                        while(!quit10)
                        {
                            score1=dot.cpoint1;
                            if( !instructionsanswer.loadFromRenderedText( to_string(score1), textColor ) )
                            {printf( "Failed to render text texture!\n" );}
                            
                            if( !instructionscore.loadFromRenderedText( "SCORE=", textColor ) )
                                {
                                            
                                    printf( "Failed to render text texture!\n" );
                             //   success = false;
                                }
        //                            if( !timetexture.loadFromRenderedText( "TIME LEFT=", textColor ) )
        //                                {
        //
        //                                    printf( "Failed to render text texture!\n" );
        //                             //   success = false;
        //                                }
                            if( !timeatexture.loadFromRenderedText( to_string(120-(SDL_GetTicks()/1000)), textColor ) )
                                {
                                            
                                    printf( "Failed to render text texture!\n" );
                             //   success = false;
                                }
                            while( SDL_PollEvent( &e ) != 0 )
                            {
                                //User requests quit
                                if( e.type == SDL_QUIT )
                                {quit = true;}
                                int x = handleMouseEvent(e, createwall(465,680,100,100));
                                if(x == 2){
                                    quit10 = true;
                                }
                                 if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_e )
                                {
                                    quit10=true;quit=false;}
                                //Handle input for the dot
                                dot.handleEvent( e );

                            }
                            SDL_Color textColor = { 0, 0, 0, 255 };
                                       //Current time start time
                                       Uint32 startTime = 0;
                                       //In memory text stream
                                       std::stringstream timeText;
                        //    startTime = SDL_GetTicks();
                            dot.move1();
                            data="";
                        data+= to_string(dot.mPosX);
                        data += "_";
                        data += to_string(dot.mPosY);
                        data += "_";
                        data += to_string(dot.cpoint1);
                            data += "_";
                                data += to_string(dot.lives);
                            clientdata = player1.sendrecieve(data);
                            opponent op1 = getopponentdata(clientdata);
                            dot2.mPosX=op1.x;
                            dot2.mPosY=op1.y;
                            dot2.cpoint1=op1.s;dot2.lives=op1.l;
                            SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                            SDL_RenderClear( gRenderer );
                            SDL_RenderCopy( gRenderer, gTexture1, NULL, NULL );
                            //Render objects
                           // instruction1.render(0,0);
                            instructionscore.render(240,5);
                            instructionsanswer.render(355,5);
                            timetexture.render(1116,625);
                            timeatexture.render(1210,675);
                                    if(dot.lives == 3)
                                        lives3texture.render(1103,733);
                                    if(dot.lives == 2)
                                        lives2texture.render(1103,733);
                                    if(dot.lives == 1)
                                        lives1texture.render(1103,733);
                            dot.render1();
                           dot2.render2();
                            if(dot.lives <= 0)
                            {
                                ggameovertexture.render(0,0);
                                SDL_RenderPresent( gRenderer ); SDL_Delay(2000);

                            }
                            //Update screen
                        
                            if(dot.lives > 0 )
                            SDL_RenderPresent( gRenderer );
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
                            dot2.cpoint1=op3.s;dot2.lives=op3.l;
                            if(dot.cpoint1>=6000)
                            {
                                ggamewontexture.render(0,0);
                                SDL_RenderPresent( gRenderer );SDL_Delay(1000);
                                
                            }
                            data="";
                        data+= to_string(dot.mPosX);
                        data += "_";
                        data += to_string(dot.mPosY);
                        data += "_";
                        data += to_string(dot.cpoint1);
                            data += "_";
                                data += to_string(dot.lives);
                            clientdata = player1.sendrecieve(data);
                            opponent op2 = getopponentdata(clientdata);
                            dot2.mPosX=op2.x;
                            dot2.mPosY=op2.y;
                            dot2.cpoint1=op2.s;dot2.lives=op2.l;
                            if(dot2.cpoint1>=6000)
                            {
                                ggameovertexture.render(0,0);
                                SDL_RenderPresent( gRenderer );SDL_Delay(1000);
                                
                            }
                            data="";
                        data+= to_string(dot.mPosX);
                        data += "_";
                        data += to_string(dot.mPosY);
                        data += "_";
                        data += to_string(dot.cpoint1);
                            data += "_";
                                data += to_string(dot.lives);
                            clientdata = player1.sendrecieve(data);
                            opponent op5 = getopponentdata(clientdata);
                            dot2.mPosX=op5.x;
                            dot2.mPosY=op5.y;
                            dot2.cpoint1=op5.s;dot2.lives=op5.l;
                             if((120-(SDL_GetTicks()/1000)) <= 5 && dot.cpoint1 > dot2.cpoint1)
                            {
                                ggamewon1texture.render(0,0);
                                SDL_RenderPresent( gRenderer );SDL_Delay(1000);
                            }
                            data="";
                        data+= to_string(dot.mPosX);
                        data += "_";
                        data += to_string(dot.mPosY);
                        data += "_";
                        data += to_string(dot.cpoint1);
                            data += "_";
                                data += to_string(dot.lives);
                            clientdata = player1.sendrecieve(data);
                            opponent op6 = getopponentdata(clientdata);
                            dot2.mPosX=op6.x;
                            dot2.mPosY=op6.y;
                            dot2.cpoint1=op6.s;dot2.lives=op6.l;
                             if((120-(SDL_GetTicks()/1000)) <= 5 && dot.cpoint1<  dot2.cpoint1)
                            {
                                ggameovertexture.render(0,0);
                                SDL_RenderPresent( gRenderer );SDL_Delay(1000);
                            }
                            
                            if(dot.cpoint1 >=6000 || dot2.cpoint1>=6000 || (120-(SDL_GetTicks()/1000)) <= 5 || dot.lives<=0 || dot2.lives<=0) {quit10=true;quit=true;}}}
                         //   1,146,61,192

         

                             else if ( dot.mPosX>=1 && dot.mPosX<=66 && dot.mPosY>=140 && dot.mPosY<=190 && e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_e )
                    {
                        //quit=true;
                        quit9=false;
                        while(!quit9)
                        {
                            score1=dot.cpoint1;
                            if( !instructionsanswer.loadFromRenderedText( to_string(score1), textColor ) )
                            {printf( "Failed to render text texture!\n" );}
                            if( !instructionscore.loadFromRenderedText( "SCORE=", textColor ) )
                                {
                                            
                                    printf( "Failed to render text texture!\n" );
                             //   success = false;
                                }
        //                            if( !timetexture.loadFromRenderedText( "TIME LEFT=", textColor ) )
        //                                {
        //
        //                                    printf( "Failed to render text texture!\n" );
        //                             //   success = false;
        //                                }
        //                            if( !timetexture.loadFromRenderedText( "TIME LEFT=", textColor ) )
        //                                {
        //
        //                                    printf( "Failed to render text texture!\n" );
        //                             //   success = false;
        //                                }
                            if( !timeatexture.loadFromRenderedText( to_string(120-(SDL_GetTicks()/1000)), textColor ) )
                                {
                                            
                                    printf( "Failed to render text texture!\n" );
                             //   success = false;
                                }
                            while( SDL_PollEvent( &e ) != 0 )
                            {
                                //User requests quit
                                if( e.type == SDL_QUIT )
                                {quit = true;}
                                int x = handleMouseEvent(e, createwall(465,680,100,100));
                                if(x == 2){
                                    quit9 = true;
                                }
                                 if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_e )
                                {
                                    quit9=true;quit=false;}
                                //Handle input for the dot
                                dot.handleEvent( e );

                            }
                            SDL_Color textColor = { 0, 0, 0, 0 };
                                       //Current time start time
                                       Uint32 startTime = 0;
                                       //In memory text stream
                                       std::stringstream timeText;
                            startTime = SDL_GetTicks();
                            dot.move2();
                            data="";
                        data+= to_string(dot.mPosX);
                        data += "_";
                        data += to_string(dot.mPosY);
                        data += "_";
                        data += to_string(dot.cpoint1);
                            data += "_";
                                data += to_string(dot.lives);
                            clientdata = player1.sendrecieve(data);
                            opponent op1 = getopponentdata(clientdata);
                            dot2.mPosX=op1.x;
                            dot2.mPosY=op1.y;
                            dot2.cpoint1=op1.s;dot2.lives=op1.l;
                            SDL_SetRenderDrawColor( gRenderer, 0x00, 0xFF, 0xFF, 0xFF );
                            SDL_RenderClear( gRenderer );
                            SDL_RenderCopy( gRenderer, gTexture2, NULL, NULL );
                            //Render objects
                           // instruction1.render(0,0);
                            instructionscore.render(240,5);
                            instructionsanswer.render(355,5);
                            timetexture.render(1116,625);
                            timeatexture.render(1210,675);
                                    if(dot.lives == 3)
                                        lives3texture.render(1103,733);
                                    if(dot.lives == 2)
                                        lives2texture.render(1103,733);
                                    if(dot.lives == 1)
                                        lives1texture.render(1103,733);
                            dot.render1();
                           dot2.render2();
                            if(dot.lives <= 0)
                            {
                                ggameovertexture.render(0,0);
                                SDL_RenderPresent( gRenderer );SDL_Delay(2000);quit=true;
                            }
                            //Update screen
                            if(dot.lives > 0 )
                            SDL_RenderPresent( gRenderer );
                            data="";
                        data+= to_string(dot.mPosX);
                        data += "_";
                        data += to_string(dot.mPosY);
                        data += "_";
                        data += to_string(dot.cpoint1);
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
                            dot2.cpoint1=op3.s;dot2.lives=op3.l;
                            if(dot.cpoint1>=6000)
                            {
                                ggamewontexture.render(0,0);
                                SDL_RenderPresent( gRenderer );SDL_Delay(1000);
                                
                            }
                            data="";
                        data+= to_string(dot.mPosX);
                        data += "_";
                        data += to_string(dot.mPosY);
                        data += "_";
                        data += to_string(dot.cpoint1);
                            data += "_";
                                data += to_string(dot.lives);
                            clientdata = player1.sendrecieve(data);
                            opponent op2 = getopponentdata(clientdata);
                            dot2.mPosX=op2.x;
                            dot2.mPosY=op2.y;
                            dot2.cpoint1=op2.s;dot2.lives=op3.l;
                            if(dot2.cpoint1>=6000)
                            {
                                ggameovertexture.render(0,0);
                                SDL_RenderPresent( gRenderer );SDL_Delay(1000);
                                
                            }
                            data="";
                        data+= to_string(dot.mPosX);
                        data += "_";
                        data += to_string(dot.mPosY);
                        data += "_";
                        data += to_string(dot.cpoint1);
                            data += "_";
                                data += to_string(dot.lives);
                            clientdata = player1.sendrecieve(data);
                            opponent op5 = getopponentdata(clientdata);
                            dot2.mPosX=op5.x;
                            dot2.mPosY=op5.y;
                            dot2.cpoint1=op5.s;dot2.lives=op5.l;
                             if((120-(SDL_GetTicks()/1000)) <= 5 && dot.cpoint1 > dot2.cpoint1)
                            {
                                ggamewon1texture.render(0,0);
                                SDL_RenderPresent( gRenderer );SDL_Delay(1000);
                            }
                            data="";
                        data+= to_string(dot.mPosX);
                        data += "_";
                        data += to_string(dot.mPosY);
                        data += "_";
                        data += to_string(dot.cpoint1);
                            data += "_";
                                data += to_string(dot.lives);
                            clientdata = player1.sendrecieve(data);
                            opponent op6 = getopponentdata(clientdata);
                            dot2.mPosX=op6.x;
                            dot2.mPosY=op6.y;
                            dot2.cpoint1=op6.s;dot2.lives=op6.l;
                             if((120-(SDL_GetTicks()/1000)) <= 5 && dot.cpoint1<  dot2.cpoint1)
                            {
                                ggameovertexture.render(0,0);
                                SDL_RenderPresent( gRenderer );SDL_Delay(1000);
                            }
                          
                            
                            if(dot.cpoint1 >=6000 || dot2.cpoint1>=6000 || (120-(SDL_GetTicks()/1000)) <= 5 ) {quit9=true;quit=true;}

                    }}
        // 1096,154,1199,223
                             else if ( dot.mPosX>=1096 && dot.mPosX<=1199 && dot.mPosY>=154 && dot.mPosY<=223 && e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_e )
                    {
                          //quit=true;
                            quit8=false;
                      while(!quit8)
                      {
                          score1=dot.cpoint1;
                          if( !instructionsanswer.loadFromRenderedText( to_string(score1), textColor ) )
                          {printf( "Failed to render text texture!\n" );}
                          if( !instructionscore.loadFromRenderedText( "SCORE=", textColor ) )
                              {
                                          
                                  printf( "Failed to render text texture!\n" );
                           //   success = false;
                              }

                          if( !timeatexture.loadFromRenderedText( to_string(120-(SDL_GetTicks()/1000)), textColor ) )
                              {
                                          
                                  printf( "Failed to render text texture!\n" );
                           //   success = false;
                              }
                          while( SDL_PollEvent( &e ) != 0 )
                          {
                              //User requests quit
                              if( e.type == SDL_QUIT )
                              {quit = true;}
                              int x = handleMouseEvent(e, createwall(465,680,100,100));
                              if(x == 2){
                                  quit8 = true;
                              }
                               if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_e )
                              {
                                  quit8=true;quit=false;}
                              //Handle input for the dot
                              dot.handleEvent( e );

                          }
                          SDL_Color textColor = { 0, 0, 0, 0 };
                                     //Current time start time
                                     Uint32 startTime = 0;
                                     //In memory text stream
                                     std::stringstream timeText;
                          startTime = SDL_GetTicks();
                          dot.move3();
                          data="";
                      data+= to_string(dot.mPosX);
                      data += "_";
                      data += to_string(dot.mPosY);
                      data += "_";
                      data += to_string(dot.cpoint1);
                          data += "_";
                              data += to_string(dot.lives);
                          clientdata = player1.sendrecieve(data);
                          opponent op1 = getopponentdata(clientdata);
                          dot2.mPosX=op1.x;
                          dot2.mPosY=op1.y;
                          dot2.cpoint1=op1.s;dot2.lives=op1.l;
                          SDL_SetRenderDrawColor( gRenderer, 0x00, 0xFF, 0xFF, 0xFF );
                          SDL_RenderClear( gRenderer );
                          SDL_RenderCopy( gRenderer, gTexture3, NULL, NULL );
                          //Render objects
                         // instruction1.render(0,0);
                          instructionscore.render(240,5);
                          instructionsanswer.render(355,5);
                          timetexture.render(1116,625);
                          timeatexture.render(1210,675);
                                  if(dot.lives == 3)
                                      lives3texture.render(1103,733);
                                  if(dot.lives == 2)
                                      lives2texture.render(1103,733);
                                  if(dot.lives == 1)
                                      lives1texture.render(1103,733);
                          dot.render1();
                         dot2.render2();
                          if(dot.lives <= 0)
                          {
                              ggameovertexture.render(0,0);
                              SDL_RenderPresent( gRenderer );SDL_Delay(2000);quit=true;
                          }
                          //Update screen
                          if(dot.lives > 0 )
                          SDL_RenderPresent( gRenderer );
                          data="";
                      data+= to_string(dot.mPosX);
                      data += "_";
                      data += to_string(dot.mPosY);
                      data += "_";
                      data += to_string(dot.cpoint1);
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
                          dot2.cpoint1=op3.s;dot2.lives=op3.l;
                          if(dot.cpoint1>=6000)
                          {
                              ggamewontexture.render(0,0);
                              SDL_RenderPresent( gRenderer );SDL_Delay(1000);
                              
                          }
                          data="";
                      data+= to_string(dot.mPosX);
                      data += "_";
                      data += to_string(dot.mPosY);
                      data += "_";
                      data += to_string(dot.cpoint1);
                          data += "_";
                              data += to_string(dot.lives);
                          clientdata = player1.sendrecieve(data);
                          opponent op2 = getopponentdata(clientdata);
                          dot2.mPosX=op2.x;
                          dot2.mPosY=op2.y;
                          dot2.cpoint1=op2.s;dot2.lives=op3.l;
                          if(dot2.cpoint1>=6000)
                          {
                              ggameovertexture.render(0,0);
                              SDL_RenderPresent( gRenderer );SDL_Delay(1000);
                              
                          }
                          data="";
                      data+= to_string(dot.mPosX);
                      data += "_";
                      data += to_string(dot.mPosY);
                      data += "_";
                      data += to_string(dot.cpoint1);
                          data += "_";
                              data += to_string(dot.lives);
                          clientdata = player1.sendrecieve(data);
                          opponent op5 = getopponentdata(clientdata);
                          dot2.mPosX=op5.x;
                          dot2.mPosY=op5.y;
                          dot2.cpoint1=op5.s;dot2.lives=op5.l;
                           if((120-(SDL_GetTicks()/1000)) <= 5 && dot.cpoint1 > dot2.cpoint1)
                          {
                              ggamewon1texture.render(0,0);
                              SDL_RenderPresent( gRenderer );SDL_Delay(1000);
                          }
                          data="";
                      data+= to_string(dot.mPosX);
                      data += "_";
                      data += to_string(dot.mPosY);
                      data += "_";
                      data += to_string(dot.cpoint1);
                          data += "_";
                              data += to_string(dot.lives);
                          clientdata = player1.sendrecieve(data);
                          opponent op6 = getopponentdata(clientdata);
                          dot2.mPosX=op6.x;
                          dot2.mPosY=op6.y;
                          dot2.cpoint1=op6.s;dot2.lives=op6.l;
                           if((120-(SDL_GetTicks()/1000)) <= 5 && dot.cpoint1<  dot2.cpoint1)
                          {
                              ggameovertexture.render(0,0);
                              SDL_RenderPresent( gRenderer );SDL_Delay(1000);
                          }
                        
                          
                          if(dot.cpoint1 >=6000 || dot2.cpoint1>=6000 || (120-(SDL_GetTicks()/1000)) <= 5 ) {quit8=true;quit=true;}

                  }}
                    int x = handleMouseEvent(e, createwall(1217,542,150,69));
                    if(x == 2){
                        quit = true;
                    }
                    //Handle input for the dot
                    dot.handleEvent( e );
                }
                //Move the dot
                dot.move();
                
                data="";
            data+= to_string(dot.mPosX);
            data += "_";
            data += to_string(dot.mPosY);
            data += "_";
            data += to_string(dot.cpoint1);
                data += "_";
                    data += to_string(dot.lives);
                clientdata = player1.sendrecieve(data);
              //  cout<<clientdata<<"\n";
                opponent op = getopponentdata(clientdata);
                dot2.mPosX=op.x;
                dot2.mPosY=op.y;
                dot2.cpoint1=op.s;dot2.lives=op.l;
              
              //  cout<<dot2.lives<<"\n";
                if(dot2.lives<=0)
                {
                    ggamewon1texture.render(0,0);
                    SDL_RenderPresent( gRenderer );SDL_Delay(1000);
                    
                }
                if(dot.lives <= 0)
                {ggameovertexture.render(0,0);
                    SDL_RenderPresent( gRenderer );SDL_Delay(1000);

                }
                //Update screen
        //                if(dot.lives > 0 )
        //                SDL_RenderPresent( gRenderer );
                if(  (120-(SDL_GetTicks()/1000)) <= 5 || dot.lives<=0 || dot2.lives<=0) quit=true;
                if(taskscreen){
                    gtasksmenuTexture.render(0,0);
                    SDL_RenderPresent( gRenderer );
                    SDL_Delay(10);
                    continue;
                }
                if(hint1){
                    ghint8texture.render(275,180);
                    SDL_RenderPresent( gRenderer );
                    SDL_Delay(10);
                    continue;
                }
                if(hint2){
                    ghint9texture.render(275,180);
                    SDL_RenderPresent( gRenderer );
                    SDL_Delay(10);
                    continue;
                }
                if(hint3){
                    gwarning8texture.render(466.5,180);
                    SDL_RenderPresent( gRenderer );
                    SDL_Delay(10);
                    continue;
                }
                if(hint4){
                    ghint10texture.render(275,180);
                    SDL_RenderPresent( gRenderer );
                    SDL_Delay(10);
                    continue;
                }
                if(hint5){
                    ghint11texture.render(275,180);
                    SDL_RenderPresent( gRenderer );
                    SDL_Delay(10);
                    continue;
                }
                if(hint6){
                    gwarning5texture.render(466.5,180);
                    SDL_RenderPresent( gRenderer );
                    SDL_Delay(10);
                    continue;
                }
                if(hint7){
                    ghint12texture.render(275,180);
                    SDL_RenderPresent( gRenderer );
                    SDL_Delay(10);
                    continue;
                }
                if(hint8){
                    ghint13texture.render(275,180);
                    SDL_RenderPresent( gRenderer );
                    SDL_Delay(10);
                    continue;
                }
                if(hint9){
                    gwarning6texture.render(466.5,180);
                    SDL_RenderPresent( gRenderer );
                    SDL_Delay(10);
                    continue;
                }
                if(hint10){
                    ghint14texture.render(275,180);
                    SDL_RenderPresent( gRenderer );
                    SDL_Delay(10);
                    continue;
                }
                if(hint11){
                    ghint29texture.render(275,180);
                    SDL_RenderPresent( gRenderer );
                    SDL_Delay(10);
                    continue;
                }
                SDL_Color textColor = { 0, 0, 0, 0 };

                           //Current time start time
                           Uint32 startTime = 0;

                           //In memory text stream
                           std::stringstream timeText;
                startTime = SDL_GetTicks();
                //Clear screen
                SDL_SetRenderDrawColor( gRenderer, 0x00, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( gRenderer );
                SDL_RenderCopy( gRenderer, gTexture, NULL, NULL );
                //Render objects
                //instruction1.render(0,0);
                instructionscore.render(240,5);
                instructionsanswer.render(355,5);
                timetexture.render(1116,625);
                timeatexture.render(1210,675);
                dot.render1();
                dot2.render2();
                if(dot.lives == 3)
                    lives3texture.render(1103,733);
                if(dot.lives == 2)
                    lives2texture.render(1103,733);
                if(dot.lives == 1)
                    lives1texture.render(1103,733);
                data="";
            data+= to_string(dot.mPosX);
            data += "_";
            data += to_string(dot.mPosY);
            data += "_";
            data += to_string(dot.cpoint1);
                data += "_";
                    data += to_string(dot.lives);
                clientdata = player1.sendrecieve(data);
                opponent op8 = getopponentdata(clientdata);
                dot2.mPosX=op8.x;
                dot2.mPosY=op8.y;
                dot2.cpoint1=op8.s;dot2.lives=op8.l;
                cout<<dot2.lives<<"\n";
                if(dot2.lives<=0)
                {
                    ggamewon1texture.render(0,0);
                    SDL_RenderPresent( gRenderer );SDL_Delay(1000);
                    
                }
                if(dot.lives <= 0)
                {ggameovertexture.render(0,0);
                    SDL_RenderPresent( gRenderer );SDL_Delay(1000);

                }
                //Update screen
                if(dot.lives > 0 )
                SDL_RenderPresent( gRenderer );
                if(  (120-(SDL_GetTicks()/1000)) <= 5 || dot.lives<=0 || dot2.lives<=0) quit=true;

            }
        c=dot.cpoint1;

        //Free resources and close SDL

        //here

        quit7=false;
        //  if(dot.cpoint >=6000 || dot2.cpoint1>=6000)
        while(!quit7){
            data="";
        data+= to_string(dot.mPosX);
        data += "_";
        data += to_string(dot.mPosY);
        data += "_";
        data += to_string(dot.cpoint1);
        //            clientdata = player1.sendrecieve(data);
        //            opponent op1 = getopponentdata(clientdata);
        //            dot2.mPosX=op1.x;
        //            dot2.mPosY=op1.y;
        //            dot2.cpoint1=op1.s;
         //   musicobj.keypress3();
            while( SDL_PollEvent( &e ) != 0 ){
                if( e.type == SDL_QUIT ){
                    close();
                    return 0;
                }
               }
              ggamefinishtexture.render(0,0);
                    SDL_RenderPresent( gRenderer );
               
            
        }
        //        quit=false
        //        while(!quit)
        //        {
        //
        //        }
        cout<<c<<"\n";

        }
          else if(setting == 3)
    {
     
        
        
        bool quit10=true;bool quit9=true;bool quit8=true;bool quit7=true;
        walls = setWalls();
        // walls.push_back(createwall(153,28,486,86));
         musicobj.maintune();
        points=set3Points();
            point1s=set3Point1s();point2s=set3Point2s();point3s=set3Point3s();
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
                if( !timeatexture.loadFromRenderedText( to_string(120-(SDL_GetTicks()/1000)), textColor ) )
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
                
                if(dot.lives<=0)
                {
                    ggameovertexture.render(0,0);
                    SDL_RenderPresent( gRenderer );SDL_Delay(1000);
                    
                }
                data="";
            data+= to_string(dot.mPosX);
            data += "_";
            data += to_string(dot.mPosY);
            data += "_";
            data += to_string(dot.cpoint1);
                data += "_";
                data += to_string(dot.lives);
                clientdata = player1.sendrecieve(data);
                opponent op2 = getopponentdata(clientdata);
                dot2.mPosX=op2.x;
                dot2.mPosY=op2.y;
                dot2.cpoint1=op2.s;dot2.lives=op2.l;
               
                if(dot2.cpoint1>=6000)
                {
                    ggameovertexture.render(0,0);
                    SDL_RenderPresent( gRenderer );SDL_Delay(1000);quit=true;
                    
                }
        //                if(dot.lives > 0 )
        //                SDL_RenderPresent( gRenderer );
                data="";
            data+= to_string(dot.mPosX);
            data += "_";
            data += to_string(dot.mPosY);
            data += "_";
            data += to_string(dot.cpoint1);
                data += "_";
                    data += to_string(dot.lives);
                clientdata = player1.sendrecieve(data);
                opponent op7 = getopponentdata(clientdata);
                dot2.mPosX=op7.x;
                dot2.mPosY=op7.y;
                dot2.cpoint1=op7.s;dot2.lives=op7.l;
                cout<<dot2.lives<<"\n";
                if(dot2.lives<=0)
                {
                    ggamewon1texture.render(0,0);
                    SDL_RenderPresent( gRenderer );SDL_Delay(1000);
                    
                }
                data="";
            data+= to_string(dot.mPosX);
            data += "_";
            data += to_string(dot.mPosY);
            data += "_";
            data += to_string(dot.cpoint1); data += "_";
                data += to_string(dot.lives);
                clientdata = player1.sendrecieve(data);
                opponent op5 = getopponentdata(clientdata);
                dot2.mPosX=op5.x;
                dot2.mPosY=op5.y;
                dot2.cpoint1=op5.s;dot2.lives=op5.l;
                 if((120-(SDL_GetTicks()/1000)) <= 5 && dot.cpoint1 > dot2.cpoint1)
                {
                    ggamewon1texture.render(0,0);
                    SDL_RenderPresent( gRenderer );SDL_Delay(1000);
                }
                data="";
            data+= to_string(dot.mPosX);
            data += "_";
            data += to_string(dot.mPosY);
            data += "_";
            data += to_string(dot.cpoint1);
                data += "_";
                    data += to_string(dot.lives);
                clientdata = player1.sendrecieve(data);
                opponent op6 = getopponentdata(clientdata);
                dot2.mPosX=op6.x;
                dot2.mPosY=op6.y;
                dot2.cpoint1=op6.s;
                dot2.lives=op6.l;
                 if((120-(SDL_GetTicks()/1000)) <= 5 && dot.cpoint1 <  dot2.cpoint1)
                {
                    ggameovertexture.render(0,0);
                    SDL_RenderPresent( gRenderer );SDL_Delay(1000);
                }
                if(  (120-(SDL_GetTicks()/1000)) <= 5 || dot.lives<=0 || dot2.lives<=0) quit=true;
                while( SDL_PollEvent( &e ) != 0 )
                {
                    //User requests quit
                    if( e.type == SDL_QUIT )
                    {
                        quit = true;
                    }
                    else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE && !taskscreen){
                        taskscreen = true;
                    }else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE){
                        taskscreen = false;
                    }
                    else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_1 && !hint1){
                        hint1 = true;
                    }else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_1){
                        hint1 = false;
                    }
                    else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_2 && !hint2){
                        hint2 = true;
                    }else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_2){
                        hint2 = false;
                    }
                    else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_a && !hint3){
                        hint3 = true;
                    }else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_a){
                        hint3 = false;
                    }
                    else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_3 && !hint4){
                        hint4 = true;
                    }else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_3){
                        hint4 = false;
                    }
                    else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_4 && !hint5){
                        hint5 = true;
                    }else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_4){
                        hint5 = false;
                    }
                    else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_b && !hint6){
                        hint6 = true;
                    }else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_b){
                        hint6 = false;
                    }
                    else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_5 && !hint7){
                        hint7 = true;
                    }else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_5){
                        hint7 = false;
                    }
                    else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_6 && !hint8){
                        hint8 = true;
                    }else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_6){
                        hint8 = false;
                    }
                    else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_c && !hint9){
                        hint9 = true;
                    }else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_c){
                        hint9 = false;
                    }
                    else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_7 && !hint10){
                        hint10 = true;
                    }else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_7){
                        hint10 = false;
                    }
                    else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_8 && !hint11){
                        hint11 = true;
                    }else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_8){
                        hint11 = false;
                    }
                    else if ( dot.mPosX>=1 && dot.mPosX<=66 && dot.mPosY>=470 && dot.mPosY<=536 && e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_e )
                    {
                        //quit=true;
                        quit10=false;
                        while(!quit10)
                        {
                            score1=dot.cpoint1;
                            if( !instructionsanswer.loadFromRenderedText( to_string(score1), textColor ) )
                            {printf( "Failed to render text texture!\n" );}
                            
                            if( !instructionscore.loadFromRenderedText( "SCORE=", textColor ) )
                                {
                                            
                                    printf( "Failed to render text texture!\n" );
                             //   success = false;
                                }
        //                            if( !timetexture.loadFromRenderedText( "TIME LEFT=", textColor ) )
        //                                {
        //
        //                                    printf( "Failed to render text texture!\n" );
        //                             //   success = false;
        //                                }
                            if( !timeatexture.loadFromRenderedText( to_string(120-(SDL_GetTicks()/1000)), textColor ) )
                                {
                                            
                                    printf( "Failed to render text texture!\n" );
                             //   success = false;
                                }
                            while( SDL_PollEvent( &e ) != 0 )
                            {
                                //User requests quit
                                if( e.type == SDL_QUIT )
                                {quit = true;}
                                int x = handleMouseEvent(e, createwall(465,680,100,100));
                                if(x == 2){
                                    quit10 = true;
                                }
                                 if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_e )
                                {
                                    quit10=true;quit=false;}
                                //Handle input for the dot
                                dot.handleEvent( e );

                            }
                            SDL_Color textColor = { 0, 0, 0, 255 };
                                       //Current time start time
                                       Uint32 startTime = 0;
                                       //In memory text stream
                                       std::stringstream timeText;
                        //    startTime = SDL_GetTicks();
                            dot.move1();
                            data="";
                        data+= to_string(dot.mPosX);
                        data += "_";
                        data += to_string(dot.mPosY);
                        data += "_";
                        data += to_string(dot.cpoint1);
                            data += "_";
                                data += to_string(dot.lives);
                            clientdata = player1.sendrecieve(data);
                            opponent op1 = getopponentdata(clientdata);
                            dot2.mPosX=op1.x;
                            dot2.mPosY=op1.y;
                            dot2.cpoint1=op1.s;dot2.lives=op1.l;
                            SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                            SDL_RenderClear( gRenderer );
                            SDL_RenderCopy( gRenderer, gTexture1, NULL, NULL );
                            //Render objects
                           // instruction1.render(0,0);
                            instructionscore.render(240,5);
                            instructionsanswer.render(355,5);
                            timetexture.render(1116,625);
                            timeatexture.render(1210,675);
                                    if(dot.lives == 3)
                                        lives3texture.render(1103,733);
                                    if(dot.lives == 2)
                                        lives2texture.render(1103,733);
                                    if(dot.lives == 1)
                                        lives1texture.render(1103,733);
                            dot.render1();
                           dot2.render2();
                            if(dot.lives <= 0)
                            {
                                ggameovertexture.render(0,0);
                                SDL_RenderPresent( gRenderer ); SDL_Delay(2000);

                            }
                            //Update screen
                        
                            if(dot.lives > 0 )
                            SDL_RenderPresent( gRenderer );
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
                            dot2.cpoint1=op3.s;dot2.lives=op3.l;
                            if(dot.cpoint1>=6000)
                            {
                                ggamewontexture.render(0,0);
                                SDL_RenderPresent( gRenderer );SDL_Delay(1000);
                                
                            }
                            data="";
                        data+= to_string(dot.mPosX);
                        data += "_";
                        data += to_string(dot.mPosY);
                        data += "_";
                        data += to_string(dot.cpoint1);
                            data += "_";
                                data += to_string(dot.lives);
                            clientdata = player1.sendrecieve(data);
                            opponent op2 = getopponentdata(clientdata);
                            dot2.mPosX=op2.x;
                            dot2.mPosY=op2.y;
                            dot2.cpoint1=op2.s;dot2.lives=op2.l;
                            if(dot2.cpoint1>=6000)
                            {
                                ggameovertexture.render(0,0);
                                SDL_RenderPresent( gRenderer );SDL_Delay(1000);
                                
                            }
                            data="";
                        data+= to_string(dot.mPosX);
                        data += "_";
                        data += to_string(dot.mPosY);
                        data += "_";
                        data += to_string(dot.cpoint1);
                            data += "_";
                                data += to_string(dot.lives);
                            clientdata = player1.sendrecieve(data);
                            opponent op5 = getopponentdata(clientdata);
                            dot2.mPosX=op5.x;
                            dot2.mPosY=op5.y;
                            dot2.cpoint1=op5.s;dot2.lives=op5.l;
                             if((120-(SDL_GetTicks()/1000)) <= 5 && dot.cpoint1 > dot2.cpoint1)
                            {
                                ggamewon1texture.render(0,0);
                                SDL_RenderPresent( gRenderer );SDL_Delay(1000);
                            }
                            data="";
                        data+= to_string(dot.mPosX);
                        data += "_";
                        data += to_string(dot.mPosY);
                        data += "_";
                        data += to_string(dot.cpoint1);
                            data += "_";
                                data += to_string(dot.lives);
                            clientdata = player1.sendrecieve(data);
                            opponent op6 = getopponentdata(clientdata);
                            dot2.mPosX=op6.x;
                            dot2.mPosY=op6.y;
                            dot2.cpoint1=op6.s;dot2.lives=op6.l;
                             if((120-(SDL_GetTicks()/1000)) <= 5 && dot.cpoint1<  dot2.cpoint1)
                            {
                                ggameovertexture.render(0,0);
                                SDL_RenderPresent( gRenderer );SDL_Delay(1000);
                            }
                            
                            if(dot.cpoint1 >=6000 || dot2.cpoint1>=6000 || (120-(SDL_GetTicks()/1000)) <= 5 || dot.lives<=0 || dot2.lives<=0) {quit10=true;quit=true;}}}
                         //   1,146,61,192

         

                             else if ( dot.mPosX>=1 && dot.mPosX<=66 && dot.mPosY>=140 && dot.mPosY<=190 && e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_e )
                    {
                        //quit=true;
                        quit9=false;
                        while(!quit9)
                        {
                            score1=dot.cpoint1;
                            if( !instructionsanswer.loadFromRenderedText( to_string(score1), textColor ) )
                            {printf( "Failed to render text texture!\n" );}
                            if( !instructionscore.loadFromRenderedText( "SCORE=", textColor ) )
                                {
                                            
                                    printf( "Failed to render text texture!\n" );
                             //   success = false;
                                }
        //                            if( !timetexture.loadFromRenderedText( "TIME LEFT=", textColor ) )
        //                                {
        //
        //                                    printf( "Failed to render text texture!\n" );
        //                             //   success = false;
        //                                }
        //                            if( !timetexture.loadFromRenderedText( "TIME LEFT=", textColor ) )
        //                                {
        //
        //                                    printf( "Failed to render text texture!\n" );
        //                             //   success = false;
        //                                }
                            if( !timeatexture.loadFromRenderedText( to_string(120-(SDL_GetTicks()/1000)), textColor ) )
                                {
                                            
                                    printf( "Failed to render text texture!\n" );
                             //   success = false;
                                }
                            while( SDL_PollEvent( &e ) != 0 )
                            {
                                //User requests quit
                                if( e.type == SDL_QUIT )
                                {quit = true;}
                                int x = handleMouseEvent(e, createwall(465,680,100,100));
                                if(x == 2){
                                    quit9 = true;
                                }
                                 if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_e )
                                {
                                    quit9=true;quit=false;}
                                //Handle input for the dot
                                dot.handleEvent( e );

                            }
                            SDL_Color textColor = { 0, 0, 0, 0 };
                                       //Current time start time
                                       Uint32 startTime = 0;
                                       //In memory text stream
                                       std::stringstream timeText;
                            startTime = SDL_GetTicks();
                            dot.move2();
                            data="";
                        data+= to_string(dot.mPosX);
                        data += "_";
                        data += to_string(dot.mPosY);
                        data += "_";
                        data += to_string(dot.cpoint1);
                            data += "_";
                                data += to_string(dot.lives);
                            clientdata = player1.sendrecieve(data);
                            opponent op1 = getopponentdata(clientdata);
                            dot2.mPosX=op1.x;
                            dot2.mPosY=op1.y;
                            dot2.cpoint1=op1.s;dot2.lives=op1.l;
                            SDL_SetRenderDrawColor( gRenderer, 0x00, 0xFF, 0xFF, 0xFF );
                            SDL_RenderClear( gRenderer );
                            SDL_RenderCopy( gRenderer, gTexture2, NULL, NULL );
                            //Render objects
                           // instruction1.render(0,0);
                            instructionscore.render(240,5);
                            instructionsanswer.render(355,5);
                            timetexture.render(1116,625);
                            timeatexture.render(1210,675);
                                    if(dot.lives == 3)
                                        lives3texture.render(1103,733);
                                    if(dot.lives == 2)
                                        lives2texture.render(1103,733);
                                    if(dot.lives == 1)
                                        lives1texture.render(1103,733);
                            dot.render1();
                           dot2.render2();
                            if(dot.lives <= 0)
                            {
                                ggameovertexture.render(0,0);
                                SDL_RenderPresent( gRenderer );SDL_Delay(2000);quit=true;
                            }
                            //Update screen
                            if(dot.lives > 0 )
                            SDL_RenderPresent( gRenderer );
                            data="";
                        data+= to_string(dot.mPosX);
                        data += "_";
                        data += to_string(dot.mPosY);
                        data += "_";
                        data += to_string(dot.cpoint1);
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
                            dot2.cpoint1=op3.s;dot2.lives=op3.l;
                            if(dot.cpoint1>=6000)
                            {
                                ggamewontexture.render(0,0);
                                SDL_RenderPresent( gRenderer );SDL_Delay(1000);
                                
                            }
                            data="";
                        data+= to_string(dot.mPosX);
                        data += "_";
                        data += to_string(dot.mPosY);
                        data += "_";
                        data += to_string(dot.cpoint1);
                            data += "_";
                                data += to_string(dot.lives);
                            clientdata = player1.sendrecieve(data);
                            opponent op2 = getopponentdata(clientdata);
                            dot2.mPosX=op2.x;
                            dot2.mPosY=op2.y;
                            dot2.cpoint1=op2.s;dot2.lives=op3.l;
                            if(dot2.cpoint1>=6000)
                            {
                                ggameovertexture.render(0,0);
                                SDL_RenderPresent( gRenderer );SDL_Delay(1000);
                                
                            }
                            data="";
                        data+= to_string(dot.mPosX);
                        data += "_";
                        data += to_string(dot.mPosY);
                        data += "_";
                        data += to_string(dot.cpoint1);
                            data += "_";
                                data += to_string(dot.lives);
                            clientdata = player1.sendrecieve(data);
                            opponent op5 = getopponentdata(clientdata);
                            dot2.mPosX=op5.x;
                            dot2.mPosY=op5.y;
                            dot2.cpoint1=op5.s;dot2.lives=op5.l;
                             if((120-(SDL_GetTicks()/1000)) <= 5 && dot.cpoint1 > dot2.cpoint1)
                            {
                                ggamewon1texture.render(0,0);
                                SDL_RenderPresent( gRenderer );SDL_Delay(1000);
                            }
                            data="";
                        data+= to_string(dot.mPosX);
                        data += "_";
                        data += to_string(dot.mPosY);
                        data += "_";
                        data += to_string(dot.cpoint1);
                            data += "_";
                                data += to_string(dot.lives);
                            clientdata = player1.sendrecieve(data);
                            opponent op6 = getopponentdata(clientdata);
                            dot2.mPosX=op6.x;
                            dot2.mPosY=op6.y;
                            dot2.cpoint1=op6.s;dot2.lives=op6.l;
                             if((120-(SDL_GetTicks()/1000)) <= 5 && dot.cpoint1<  dot2.cpoint1)
                            {
                                ggameovertexture.render(0,0);
                                SDL_RenderPresent( gRenderer );SDL_Delay(1000);
                            }
                          
                            
                            if(dot.cpoint1 >=6000 || dot2.cpoint1>=6000 || (120-(SDL_GetTicks()/1000)) <= 5 ) {quit9=true;quit=true;}

                    }}
        // 1096,154,1199,223
                             else if ( dot.mPosX>=1096 && dot.mPosX<=1199 && dot.mPosY>=154 && dot.mPosY<=223 && e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_e )
                    {
                         //quit=true;
                            quit8=false;
                      while(!quit8)
                      {
                          score1=dot.cpoint1;
                          if( !instructionsanswer.loadFromRenderedText( to_string(score1), textColor ) )
                          {printf( "Failed to render text texture!\n" );}
                          if( !instructionscore.loadFromRenderedText( "SCORE=", textColor ) )
                              {
                                          
                                  printf( "Failed to render text texture!\n" );
                           //   success = false;
                              }

                          if( !timeatexture.loadFromRenderedText( to_string(120-(SDL_GetTicks()/1000)), textColor ) )
                              {
                                          
                                  printf( "Failed to render text texture!\n" );
                           //   success = false;
                              }
                          while( SDL_PollEvent( &e ) != 0 )
                          {
                              //User requests quit
                              if( e.type == SDL_QUIT )
                              {quit = true;}
                              int x = handleMouseEvent(e, createwall(465,680,100,100));
                              if(x == 2){
                                  quit8 = true;
                              }
                               if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_e )
                              {
                                  quit8=true;quit=false;}
                              //Handle input for the dot
                              dot.handleEvent( e );

                          }
                          SDL_Color textColor = { 0, 0, 0, 0 };
                                     //Current time start time
                                     Uint32 startTime = 0;
                                     //In memory text stream
                                     std::stringstream timeText;
                          startTime = SDL_GetTicks();
                          dot.move3();
                          data="";
                      data+= to_string(dot.mPosX);
                      data += "_";
                      data += to_string(dot.mPosY);
                      data += "_";
                      data += to_string(dot.cpoint1);
                          data += "_";
                              data += to_string(dot.lives);
                          clientdata = player1.sendrecieve(data);
                          opponent op1 = getopponentdata(clientdata);
                          dot2.mPosX=op1.x;
                          dot2.mPosY=op1.y;
                          dot2.cpoint1=op1.s;dot2.lives=op1.l;
                          SDL_SetRenderDrawColor( gRenderer, 0x00, 0xFF, 0xFF, 0xFF );
                          SDL_RenderClear( gRenderer );
                          SDL_RenderCopy( gRenderer, gTexture3, NULL, NULL );
                          //Render objects
                         // instruction1.render(0,0);
                          instructionscore.render(240,5);
                          instructionsanswer.render(355,5);
                          timetexture.render(1116,625);
                          timeatexture.render(1210,675);
                                  if(dot.lives == 3)
                                      lives3texture.render(1103,733);
                                  if(dot.lives == 2)
                                      lives2texture.render(1103,733);
                                  if(dot.lives == 1)
                                      lives1texture.render(1103,733);
                          dot.render1();
                         dot2.render2();
                          if(dot.lives <= 0)
                          {
                              ggameovertexture.render(0,0);
                              SDL_RenderPresent( gRenderer );SDL_Delay(2000);quit=true;
                          }
                          //Update screen
                          if(dot.lives > 0 )
                          SDL_RenderPresent( gRenderer );
                          data="";
                      data+= to_string(dot.mPosX);
                      data += "_";
                      data += to_string(dot.mPosY);
                      data += "_";
                      data += to_string(dot.cpoint1);
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
                          dot2.cpoint1=op3.s;dot2.lives=op3.l;
                          if(dot.cpoint1>=6000)
                          {
                              ggamewontexture.render(0,0);
                              SDL_RenderPresent( gRenderer );SDL_Delay(1000);
                              
                          }
                          data="";
                      data+= to_string(dot.mPosX);
                      data += "_";
                      data += to_string(dot.mPosY);
                      data += "_";
                      data += to_string(dot.cpoint1);
                          data += "_";
                              data += to_string(dot.lives);
                          clientdata = player1.sendrecieve(data);
                          opponent op2 = getopponentdata(clientdata);
                          dot2.mPosX=op2.x;
                          dot2.mPosY=op2.y;
                          dot2.cpoint1=op2.s;dot2.lives=op3.l;
                          if(dot2.cpoint1>=6000)
                          {
                              ggameovertexture.render(0,0);
                              SDL_RenderPresent( gRenderer );SDL_Delay(1000);
                              
                          }
                          data="";
                      data+= to_string(dot.mPosX);
                      data += "_";
                      data += to_string(dot.mPosY);
                      data += "_";
                      data += to_string(dot.cpoint1);
                          data += "_";
                              data += to_string(dot.lives);
                          clientdata = player1.sendrecieve(data);
                          opponent op5 = getopponentdata(clientdata);
                          dot2.mPosX=op5.x;
                          dot2.mPosY=op5.y;
                          dot2.cpoint1=op5.s;dot2.lives=op5.l;
                           if((120-(SDL_GetTicks()/1000)) <= 5 && dot.cpoint1 > dot2.cpoint1)
                          {
                              ggamewon1texture.render(0,0);
                              SDL_RenderPresent( gRenderer );SDL_Delay(1000);
                          }
                          data="";
                      data+= to_string(dot.mPosX);
                      data += "_";
                      data += to_string(dot.mPosY);
                      data += "_";
                      data += to_string(dot.cpoint1);
                          data += "_";
                              data += to_string(dot.lives);
                          clientdata = player1.sendrecieve(data);
                          opponent op6 = getopponentdata(clientdata);
                          dot2.mPosX=op6.x;
                          dot2.mPosY=op6.y;
                          dot2.cpoint1=op6.s;dot2.lives=op6.l;
                           if((120-(SDL_GetTicks()/1000)) <= 5 && dot.cpoint1<  dot2.cpoint1)
                          {
                              ggameovertexture.render(0,0);
                              SDL_RenderPresent( gRenderer );SDL_Delay(1000);
                          }
                        
                          
                          if(dot.cpoint1 >=6000 || dot2.cpoint1>=6000 || (120-(SDL_GetTicks()/1000)) <= 5 ) {quit8=true;quit=true;}

                  }}
                    int x = handleMouseEvent(e, createwall(1217,542,150,69));
                    if(x == 2){
                        quit = true;
                    }
                    //Handle input for the dot
                    dot.handleEvent( e );
                }
                //Move the dot
                dot.move();
                
                data="";
            data+= to_string(dot.mPosX);
            data += "_";
            data += to_string(dot.mPosY);
            data += "_";
            data += to_string(dot.cpoint1);
                data += "_";
                    data += to_string(dot.lives);
                clientdata = player1.sendrecieve(data);
              //  cout<<clientdata<<"\n";
                opponent op = getopponentdata(clientdata);
                dot2.mPosX=op.x;
                dot2.mPosY=op.y;
                dot2.cpoint1=op.s;dot2.lives=op.l;
              
              //  cout<<dot2.lives<<"\n";
                if(dot2.lives<=0)
                {
                    ggamewon1texture.render(0,0);
                    SDL_RenderPresent( gRenderer );SDL_Delay(1000);
                    
                }
                if(dot.lives <= 0)
                {ggameovertexture.render(0,0);
                    SDL_RenderPresent( gRenderer );SDL_Delay(1000);

                }
                //Update screen
        //                if(dot.lives > 0 )
        //                SDL_RenderPresent( gRenderer );
                if(  (120-(SDL_GetTicks()/1000)) <= 5 || dot.lives<=0 || dot2.lives<=0) quit=true;
                if(taskscreen){
                    gtasksmenuTexture.render(0,0);
                    SDL_RenderPresent( gRenderer );
                    SDL_Delay(10);
                    continue;
                }if(hint1){
                    ghint16texture.render(275,180);
                    SDL_RenderPresent( gRenderer );
                    SDL_Delay(10);
                    continue;
                }
                if(hint2){
                    ghint17texture.render(275,180);
                    SDL_RenderPresent( gRenderer );
                    SDL_Delay(10);
                    continue;
                }
                if(hint3){
                    gwarning8texture.render(466.5,180);
                    SDL_RenderPresent( gRenderer );
                    SDL_Delay(10);
                    continue;
                }
                if(hint4){
                    ghint18texture.render(275,180);
                    SDL_RenderPresent( gRenderer );
                    SDL_Delay(10);
                    continue;
                }
                if(hint5){
                    ghint20texture.render(275,180);
                    SDL_RenderPresent( gRenderer );
                    SDL_Delay(10);
                    continue;
                }
                if(hint6){
                    gwarning9texture.render(466.5,180);
                    SDL_RenderPresent( gRenderer );
                    SDL_Delay(10);
                    continue;
                }
                if(hint7){
                    ghint22texture.render(275,180);
                    SDL_RenderPresent( gRenderer );
                    SDL_Delay(10);
                    continue;
                }
                if(hint8){
                    ghint28texture.render(275,180);
                    SDL_RenderPresent( gRenderer );
                    SDL_Delay(10);
                    continue;
                }
                if(hint9){
                    gwarning7texture.render(466.5,180);
                    SDL_RenderPresent( gRenderer );
                    SDL_Delay(10);
                    continue;
                }
                if(hint10){
                    ghint24texture.render(275,180);
                    SDL_RenderPresent( gRenderer );
                    SDL_Delay(10);
                    continue;
                }
                if(hint11){
                    ghint23texture.render(275,180);
                    SDL_RenderPresent( gRenderer );
                    SDL_Delay(10);
                    continue;
                }
                SDL_Color textColor = { 0, 0, 0, 0 };

                           //Current time start time
                           Uint32 startTime = 0;

                           //In memory text stream
                           std::stringstream timeText;
                startTime = SDL_GetTicks();
                //Clear screen
                SDL_SetRenderDrawColor( gRenderer, 0x00, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( gRenderer );
                SDL_RenderCopy( gRenderer, gTexture, NULL, NULL );
                //Render objects
                //instruction1.render(0,0);
                instructionscore.render(240,5);
                instructionsanswer.render(355,5);
                timetexture.render(1116,625);
                timeatexture.render(1210,675);
                dot.render1();
                dot2.render2();
                if(dot.lives == 3)
                    lives3texture.render(1103,733);
                if(dot.lives == 2)
                    lives2texture.render(1103,733);
                if(dot.lives == 1)
                    lives1texture.render(1103,733);
                data="";
            data+= to_string(dot.mPosX);
            data += "_";
            data += to_string(dot.mPosY);
            data += "_";
            data += to_string(dot.cpoint1);
                data += "_";
                    data += to_string(dot.lives);
                clientdata = player1.sendrecieve(data);
                opponent op8 = getopponentdata(clientdata);
                dot2.mPosX=op8.x;
                dot2.mPosY=op8.y;
                dot2.cpoint1=op8.s;dot2.lives=op8.l;
                cout<<dot2.lives<<"\n";
                if(dot2.lives<=0)
                {
                    ggamewon1texture.render(0,0);
                    SDL_RenderPresent( gRenderer );SDL_Delay(1000);
                    
                }
                if(dot.lives <= 0)
                {ggameovertexture.render(0,0);
                    SDL_RenderPresent( gRenderer );SDL_Delay(1000);

                }
                //Update screen
                if(dot.lives > 0 )
                SDL_RenderPresent( gRenderer );
                if(  (120-(SDL_GetTicks()/1000)) <= 5 || dot.lives<=0 || dot2.lives<=0) quit=true;

            }
        c=dot.cpoint1;

        //Free resources and close SDL

        //here

        quit7=false;
        //  if(dot.cpoint >=6000 || dot2.cpoint1>=6000)
        while(!quit7){
            data="";
        data+= to_string(dot.mPosX);
        data += "_";
        data += to_string(dot.mPosY);
        data += "_";
        data += to_string(dot.cpoint1);
        //            clientdata = player1.sendrecieve(data);
        //            opponent op1 = getopponentdata(clientdata);
        //            dot2.mPosX=op1.x;
        //            dot2.mPosY=op1.y;
        //            dot2.cpoint1=op1.s;
         //   musicobj.keypress3();
            while( SDL_PollEvent( &e ) != 0 ){
                if( e.type == SDL_QUIT ){
                    close();
                    return 0;
                }
               }
              ggamefinishtexture.render(0,0);
                    SDL_RenderPresent( gRenderer );
               
            
        }
        //        quit=false
        //        while(!quit)
        //        {
        //
        //        }
        cout<<c<<"\n";}
	return 0;
    }
