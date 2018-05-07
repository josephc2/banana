#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>

#include "animation.cpp"
#include "entity.cpp"
#include "head.cpp"
#include "turret.cpp"
#include "bullet.cpp"

#define MAX_X 1920
#define MAX_Y 1080
#define X_OFFSET 240
#define Y_OFFSET 135
#define X_BULLET 20
#define Y_BULLET 60

std::list<entity*> entities;
bool gameStart=false;
bool gamePause=true;
bool isMove=false;
float dx=0, dy=0;
int count = 0;
int numHeads = 0;
int waveMode = 0;
int bulletShoot = 0;
int liveCheck = 0;
int lifeleft = 10;
int bank = 100;

bool isCollide(entity *a,entity *b){
  return (b->x+X_BULLET - a->x)*(b->x+X_BULLET - a->x)+
         (b->y+Y_BULLET - a->y)*(b->y+Y_BULLET - a->y)<
         (a->R + b->R)*(a->R + b->R);
}
