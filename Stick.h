#pragma once
#include "Object.h"

enum Side 
{   
    LEFT = 0,
    RIGHT = 1
};

class Stick : public GameObject
{
public:
    Side lor;
    float acc;
    int lastMoveDir;
    void moveUp();
    void moveDown();
    void accUpdate(float accCommand);
    void checkBoundaries();
    Stick(Side lor);
};