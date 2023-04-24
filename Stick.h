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
    int lastMoveDir;
    void moveUp();
    void moveDown();
    void checkBoundaries();
    Stick(Side lor);
};