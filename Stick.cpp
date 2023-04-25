#include "Stick.h"

Stick::Stick(Side lor){
    this->lor = lor;
    this->width = 16;
    this->height = 100;
    switch(lor)
    {
        case LEFT:
            this->posx = 0;
            break;
        case RIGHT:
            this->posx = 800 - width;
            break;
    }
    this->posy = 300 - height/2;
    this->speed = 0;
    this->lastMoveDir = 0;
    this->acc = 0;
}

void Stick::moveDown()
{
    this->speed = 20;
    this->posy += this->speed;
    this->lastMoveDir = 1;
    checkBoundaries();
}

void Stick::moveUp()
{
    this->speed = -20;
    this->posy += this->speed;
    this->lastMoveDir = -1;
    checkBoundaries();
}

void Stick::accUpdate(float accCommand)
{
    this->acc = accCommand;
    this->speed += this->acc;
    this->posy += this->speed;
    checkBoundaries();
    if(speed>0)
        this->lastMoveDir = 1;
    else if(speed<0)
        this->lastMoveDir = -1;
    else
        this->lastMoveDir = 0;
}

void Stick::checkBoundaries()
{
    if(this->posy<0)
    {
        this->posy = 0;
        this->speed = 0;
    }    
    if((this->posy + this->height)>600)
    {
        this->speed = 0;
        this->posy = 600 - this->height;
    }
}