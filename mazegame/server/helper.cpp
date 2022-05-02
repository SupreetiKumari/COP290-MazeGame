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

SDL_Rect createwall(int x, int y, int w, int h){
    SDL_Rect wall;
    wall.x = x;
    wall.y = y;
    wall.w = w;
    wall.h = h;
    return wall;
}

pair < SDL_Rect,int> createwall2(int x, int y, int w, int h,int a){
    SDL_Rect wall;
    pair < SDL_Rect,int> wall2;
    wall.x = x;
    wall.y = y;
    wall.w = w;
    wall.h = h;
    wall2.first=wall;
    wall2.second=a;
    return wall2;
}
bool checkCollision( SDL_Rect a, vector<SDL_Rect> b ){
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;
    for(int i=0;i<b.size();i++){
        leftB = b[i].x;
        rightB = b[i].x + b[i].w;
        topB = b[i].y;
        bottomB = b[i].y + b[i].h;
        if( bottomA <= topB ){
            continue;
        }
        if( topA >= bottomB ){
            continue;
        }
        if( rightA <= leftB ){
            continue;
        }
        if( leftA >= rightB ){
            continue;
        }
        return true;
    }
}
bool checkCollision2( SDL_Rect a, vector<pair<SDL_Rect,int>> b ){
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;
    for(int i=0;i<b.size();i++){
        leftB = b[i].first.x;
        rightB = b[i].first.x + b[i].first.w;
        topB = b[i].first.y;
        bottomB = b[i].first.y + b[i].first.h;
        if( bottomA <= topB ){
            continue;
        }
        if( topA >= bottomB ){
            continue;
        }
        if( rightA <= leftB ){
            continue;
        }
        if( leftA >= rightB ){
            continue;
        }
        return true;
    }
}
int amountreturn(SDL_Rect a, vector<pair<SDL_Rect,int>> b ){
    int leftA, leftB;
    int rightA, rightB;int prize=0;
    int topA, topB;
    int bottomA, bottomB;
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;
    for(int i=0;i<b.size();i++){
        leftB = b[i].first.x;
        rightB = b[i].first.x + b[i].first.w;
        topB = b[i].first.y;
        bottomB = b[i].first.y + b[i].first.h;
        if( bottomA <= topB ){
            continue;
        }
        if( topA >= bottomB ){
            continue;
        }
        if( rightA <= leftB ){
            continue;
        }
        if( leftA >= rightB ){
            continue;
        }
        prize=b[i].second;b[i].second=0;
    }
    return prize;
}
vector<SDL_Rect> setWalls(){
    vector<SDL_Rect> walls;
    walls.push_back(createwall(235,3,400,87));
    

    return walls;
}

vector<pair<SDL_Rect,int>> set1Points(){
    vector<pair<SDL_Rect,int>> points;
    points.push_back(createwall2(0,154,10,10,50));
    points.push_back(createwall2(1,361,10,10,80));
    points.push_back(createwall2(1,501,10,10,-160));
    points.push_back(createwall2(1,607,10,10,-150));
    

    return points;
}
vector<pair<SDL_Rect,int>> set2Points(){
    vector<pair<SDL_Rect,int>> points;
    points.push_back(createwall2(159,117,10,10,50));
    points.push_back(createwall2(333,112,10,10,80));
    points.push_back(createwall2(564,126,10,10,-160));
    points.push_back(createwall2(685,112,10,10,-150));
    

    return points;
}
vector<pair<SDL_Rect,int>> set3Points(){
    vector<pair<SDL_Rect,int>> points;
    points.push_back(createwall2(0,118,4,4,50));
    points.push_back(createwall2(215,268,10,10,150));
    

    return points;
}


