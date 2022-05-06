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
    void move(); void move1();void move2();void move3();

        //Shows the dot on the screen
        void render1();
    void render2();
            //The X and Y offsets of the dot
        int mPosX, mPosY;
    int cpoint ,lives,cpoint1;
        //The velocity of the dot
        int mVelX, mVelY;
};


Dot::Dot()
{
    //Initialize the offsets
    mPosX = 0;
    mPosY = 0;
    cpoint=0;
    lives=3;
    cpoint1=0;
    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;
}

