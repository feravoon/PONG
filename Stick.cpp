#include "Stick.h"

Stick::Stick(Side lor){
    this->lor = lor;
    this->width = 20;
    this->height = 150;
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
    this->speed = 4;
    this->lastMoveDir = 0;
}

void Stick::moveDown()
{
    this->posy += this->speed;
    this->lastMoveDir = 1;
    checkBoundaries();
}

void Stick::moveUp()
{
    this->posy -= this->speed;
    this->lastMoveDir = -1;
    checkBoundaries();
}

void Stick::checkBoundaries()
{
    if(this->posy<0)
        this->posy = 0;

    if((this->posy + this->height)>600)
        this->posy = 600 - this->height;
}