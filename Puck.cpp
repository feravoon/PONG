#include "Puck.h"
#include <math.h>

Puck::Puck()
{
    this->width = 16;
    this->height = 16;
    this->posx = 400 - this->width/2;
    this->posy = 300 - this->height/2;
    this->velocityx = 10;
    this->velocityy = 10;
    this->speed = sqrtf(this->velocityx*this->velocityx+this->velocityy*this->velocityy);
    this->state = WAIT;
    this->waitCounter = 180;
}

PuckHitType Puck::update(Stick lStick, Stick rStick)
{
    if(this->state == WAIT) // if the puck is in the waiting state
    {
        this->waitCounter--; // decrease counter
        if(waitCounter<=0)
            this->state = MOVE; // if the counter zeroes, change the state to move
        return NO_HIT;
    }
    else if (this->state == MOVE) // if the puck is in the moving state
    {
        this->posx += this->velocityx; // update x coordinate with the velocity
        this->posy += this->velocityy; // update y coordinate with the velocity
        PuckHitType result = checkCollision(lStick, rStick); // check collisions (also checks if either side has scored)
        if (result==RIGHT_SCORE | result==LEFT_SCORE) // Means a score
        {
            // Change the puck state to WAIT and set the counter to 180 iterations (3 seconds for 60Hz refresh rate)
            this->waitCounter = 180;
            this->state = WAIT;
            // Move the puck to center position
            this->posx = 400 - this->width/2;
            this->posy = 300 - this->height/2;

            // The velocities below determines the direction of the puck movement after the WAIT
            if(result==1)
            {
                this->velocityx = 10;
                this->velocityy = 10;
            }
            else
            {
                this->velocityx = -10;
                this->velocityy = 10;
            }
        }   
        return result; // Return score info
    }
    else
    {
        return NO_HIT;
    }  
}

PuckHitType Puck::checkCollision(Stick lStick, Stick rStick)
{
    if(this->posy<0) // Ball touches to the top
    {    
        this->velocityy = -this->velocityy;
        return SIDE_HIT;
    }
    if((this->posy + this->height)>600) // Ball touches to the bottom
    {    
        this->velocityy = -this->velocityy;
        return SIDE_HIT;
    }
    // Ball touches to the left stick
    if(this->posx < (lStick.posx+lStick.width) & this->posy <= (lStick.posy+lStick.height) & (this->posy + this->height) >= lStick.posy )
    { 
        this->posx = lStick.posx+lStick.width;
        this->velocityx = -this->velocityx;
        this->velocityy = this->velocityy+2.5f*lStick.lastMoveDir;
        float curRatio = this->speed/sqrtf(this->velocityx*this->velocityx+this->velocityy*this->velocityy);
        this->velocityx = curRatio * this->velocityx;
        this->velocityy = curRatio * this->velocityy;
        return STICK_HIT;
    }
    // Ball touches to the right stick
    if((this->posx + this->width) > (rStick.posx) & this->posy <= (rStick.posy+rStick.height) & (this->posy + this->height) >= rStick.posy )
    {
        this->posx = rStick.posx-rStick.width;
        this->velocityx = -this->velocityx;
        this->velocityy = this->velocityy+2.5f*rStick.lastMoveDir;
        float curRatio = this->speed/sqrtf(this->velocityx*this->velocityx+this->velocityy*this->velocityy);
        this->velocityx = curRatio * this->velocityx;
        this->velocityy = curRatio * this->velocityy;
        return STICK_HIT;
    }

    if(this->posx<0) // means a score for right stick
        return RIGHT_SCORE;

    if((this->posx + this->height)>800) // means a score for left stick
        return LEFT_SCORE; 

    return NO_HIT;
}
