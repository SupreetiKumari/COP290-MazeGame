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
    walls.push_back(createwall(23,768,645,80));
    walls.push_back(createwall(345,739,324,40));
    walls.push_back(createwall(580,417,91,330));
    walls.push_back(createwall(355,417,230,67));
    walls.push_back(createwall(988,604,415,250));
    walls.push_back(createwall(227,0,384,83));
    walls.push_back(createwall(613,0,439,26));
    walls.push_back(createwall(97,345,109,271));
    walls.push_back(createwall(201,345,121,53));
    walls.push_back(createwall(240,419,78,61));
    walls.push_back(createwall(985,417,60,210));
    walls.push_back(createwall(1176,445,224,175));
    walls.push_back(createwall(709,184,89,134));
    walls.push_back(createwall(168,10,30,61));
    walls.push_back(createwall(146,29,29,38));
    walls.push_back(createwall(364,359,148,33));
    walls.push_back(createwall(971,314,74,80));
    walls.push_back(createwall(1356,382,47,77));
    walls.push_back(createwall(1233,69,64,119));
    walls.push_back(createwall(883,20,168,39));
    walls.push_back(createwall(993,61,58,20));
    walls.push_back(createwall(563,188,149,95));
    walls.push_back(createwall(804,188,78,98));
    walls.push_back(createwall(242,520,74,46));
    walls.push_back(createwall(227,652,75,89));
    walls.push_back(createwall(93,613,33,131));
    walls.push_back(createwall(51,712,41,31));
    walls.push_back(createwall(870,138,181,96));
    walls.push_back(createwall(991,97,60,40));
    walls.push_back(createwall(1092,327,117,92));
    walls.push_back(createwall(1091,96,118,38));
    walls.push_back(createwall(1196,139,17,186));
    walls.push_back(createwall(1137,416,76,25));
    walls.push_back(createwall(1095,214,109,19));
    walls.push_back(createwall(491,182,46,44));
    walls.push_back(createwall(491,242,20,164));
    walls.push_back(createwall(288,155,89,46));
    walls.push_back(createwall(342,206,37,124));
    walls.push_back(createwall(1352,200,41,89));
    walls.push_back(createwall(1292,75,96,58));
    walls.push_back(createwall(1095,54,118,21));
    walls.push_back(createwall(866,297,83,37));
    walls.push_back(createwall(565,274,14,130));
    walls.push_back(createwall(931,215,29,57));
    walls.push_back(createwall(855,4,38,133));

    

    return walls;
}

vector<pair<SDL_Rect,int>> set1Points(){
    vector<pair<SDL_Rect,int>> points;
    points.push_back(createwall2(1046,68,54,47,50));//Himadri circle:coin.png:hint1
    points.push_back(createwall2(418,220,67,53,150));//Shivalik:ruby.png:hint2
    points.push_back(createwall2(800,298,74,107,-50));//Bharti:warning1
    points.push_back(createwall2(1049,0,39,29,100));//Gate1:emerald.png:hint3
    points.push_back(createwall2(510,330,47,66,200));//Masala Mix:sapphire.png:hint4
    points.push_back(createwall2(0,447,77,120,-100));//Karakoram:warning2
    points.push_back(createwall2(882,232,57,83,75));//Amul:silver.png:hint5
    points.push_back(createwall2(416,304,74,66,175));//Zanskar:gold.png:hint6
    points.push_back(createwall2(1090,145,111,81,-75));//Dogra hall:warning3
    points.push_back(createwall2(4,256,68,61,25));//Holistic:pearl.png:hint7
    points.push_back(createwall2(3,462,66,92,0));//Karakoram:diamond.png:hint15


    return points;
}
vector<pair<SDL_Rect,int>> set2Points(){
    vector<pair<SDL_Rect,int>> points;
    points.push_back(createwall2(725,681,216,146,50));//Mittal Complex:coin.png:hint8
    points.push_back(createwall2(509,264,51,39,150));//Chaayos:ruby.png:hint9
    points.push_back(createwall2(668,461,140,127,-115));//Football ground:warning4
    points.push_back(createwall2(571,299,145,104,100));//Gate1:emerald.png:hint10
    points.push_back(createwall2(1300,132,105,74,200));//Mother dairy:sapphire.png:hint11
    points.push_back(createwall2(1051,431,137,188,-60));//Food joint:warning5
    points.push_back(createwall2(246,487,75,50,75));//Guest house:silver.png:hint12
    points.push_back(createwall2(799,300,75,106,175));//Bharti:gold.png:hint13
    points.push_back(createwall2(124,95,131,76,-200));//Kumaon:warning6
    points.push_back(createwall2(757,72,89,97,25));//Udaigiri:pearl.png:hint14
    points.push_back(createwall2(2,124,72,89,0));//Jwalamukhi:diamond.png:hint29
    

    return points;
}
vector<pair<SDL_Rect,int>> set3Points(){
    points.push_back(createwall2(0,332,73,104,50));//Aravali:coin.png:hint16
    points.push_back(createwall2(958,238,98,68,150));//Library:ruby.png:hint17
    points.push_back(createwall2(1140,0,77,64,-175));//Kailash:warning8
    points.push_back(createwall2(245,575,79,91,100));//Nalanda:emerald.png:hint18
    points.push_back(createwall2(552,99,79,75,200));//Satpura:sapphire.png:hint20
    points.push_back(createwall2(668,461,140,127,-25));//Football ground:warning9
    points.push_back(createwall2(885,62,110,69,75));//Biotech lawns:silver.png:hint22
    points.push_back(createwall2(1093,242,105,84,175));//LHC:gold.png:hint28
    points.push_back(createwall2(350,495,235,183,-150));//SAC:warning7
    points.push_back(createwall2(484,698,91,56,25));//OAT:pearl.png:hint24
    points.push_back(createwall2(1090,145,111,81,0));//Dogra hall:diamond.png:hint23
    
    return points;
}


