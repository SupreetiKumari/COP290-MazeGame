#ifndef MUSIC_HPP
#define MUSIC_HPP
#include<map>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <string>

using namespace std;
class Music{
    public:
        Mix_Music *gMusic = NULL;
        Mix_Chunk *ghit = NULL;
        Mix_Chunk *genetrbuilding = NULL;
        Mix_Chunk *gMedium = NULL;
        Mix_Chunk *gLow = NULL;
        Music(){
            Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
        }

        void maintune(){
        
            if( Mix_PlayingMusic() == 0 )
            {
            	gMusic=Mix_LoadMUS( "/Users/arushigoyal/Desktop/task2/beat.wav" );
            	if( gMusic == NULL )
            {
                printf( "SDL_mixer Error: %s\n", Mix_GetError() );
                
            }
                Mix_PlayMusic( gMusic, -1 );
            }
            if( gMusic == NULL )
            {
                printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
            }
        }
};
