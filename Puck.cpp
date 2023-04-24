#include "Puck.h"
#include <math.h>

Puck::Puck()
{
    this->width = 10;
    this->height = 10;
    this->posx = 400 - this->width/2;
    this->posy = 300 - this->height/2;
    this->velocityx = 5;
    this->velocityy = 5;
    this->speed = sqrtf(this->velocityx*this->velocityx+this->velocityy*this->velocityy);
    this->state = WAIT;
    this->waitCounter = 180;
}

int Puck::update(Stick lStick, Stick rStick)
{
    if(this->state == WAIT)
    {
        this->waitCounter--;
        if(waitCounter<=0)
            this->state = MOVE;
        return 0;
    }
    else if (this->state == MOVE)
    {
        this->posx += this->velocityx;
        this->posy += this->velocityy;
        int result = checkCollision(lStick, rStick);
        if (result==-1 | result==1) // Means a score
        {
            this->waitCounter = 180;
            this->state = WAIT;
            this->posx = 400 - this->width/2;
            this->posy = 300 - this->height/2;
            if(result==1)
            {
                this->velocityx = 5;
                this->velocityy = 5;
            }
            else
            {
                this->velocityx = -5;
                this->velocityy = 5;
            }
        }    
        return result;
    }
    else
    {
        return 0;
    }
    
    
}

int Puck::checkCollision(Stick lStick, Stick rStick)
{
    if(this->posy<0)
        this->velocityy = -this->velocityy;

    if((this->posy + this->height)>600)
        this->velocityy = -this->velocityy;
    
    if(this->posx < (lStick.posx+lStick.width) & this->posy <= (lStick.posy+lStick.height) & (this->posy + this->height) >= lStick.posy )
    { 
        this->posx = lStick.posx+lStick.width;
        this->velocityx = -this->velocityx;
        this->velocityy = this->velocityy+2.5f*lStick.lastMoveDir;
        float curRatio = this->speed/sqrtf(this->velocityx*this->velocityx+this->velocityy*this->velocityy);
        //this->velocityx = curRatio * this->velocityx;
        //this->velocityy = curRatio * this->velocityy;
    }
    if((this->posx + this->width) > (rStick.posx) & this->posy <= (rStick.posy+rStick.height) & (this->posy + this->height) >= rStick.posy )
    {
        this->posx = rStick.posx-rStick.width;
        this->velocityx = -this->velocityx;
        this->velocityy = this->velocityy+2.5f*rStick.lastMoveDir;
        float curRatio = this->speed/sqrtf(this->velocityx*this->velocityx+this->velocityy*this->velocityy);
        //this->velocityx = curRatio * this->velocityx;
        //this->velocityy = curRatio * this->velocityy;
    }


    if(this->posx<0)
        return -1;

    if((this->posx + this->height)>800)
        return 1;

    return 0;
}
