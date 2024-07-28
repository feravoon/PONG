#include "Renderer.h"
#include "Stick.h"
#include "Puck.h"
#include "SoundPlayer.h"
#include <iostream>
#include <math.h>
 
int main(int argc, char *argv[])
{
    Renderer renderer;
    SoundPlayer soundPlayer;
    Stick lStick(LEFT);
    Stick rStick(RIGHT);
    Puck puck;
    GameObject* objects[3] = {&lStick, &rStick, &puck};
    float angle = 0, oldAngle = 0;
    int lScore = 0;
    int rScore = 0;
    PuckHitType puckResult = NO_HIT;
    // controls animation loop
    int close = 0;
 
    // speed of box
    //int speed = 3;
    SDL_Event event;
    const Uint8* keystate;
    PuckState prevState = puck.state;
    // animation loop
    while (!close) {
        // Events management
        if(SDL_PollEvent(&event))
        {
            keystate = SDL_GetKeyboardState(NULL);
            if(event.type == SDL_QUIT || keystate[SDL_SCANCODE_ESCAPE]) // Pressing escape also exits the game.
            {
                close = true;
                break;
            }
        }

        if(puck.state!=PAUSE)
        {
            if(keystate[SDL_SCANCODE_UP] | keystate[SDL_SCANCODE_W])
                lStick.moveUp();
            else if(keystate[SDL_SCANCODE_DOWN] | keystate[SDL_SCANCODE_S])
                lStick.moveDown();
            else
                lStick.lastMoveDir = 0;
        }

        if(keystate[SDL_SCANCODE_R])
        {
            // Change the puck state to WAIT and set the counter to 180 iterations (3 seconds for 60Hz refresh rate)
            puck.waitCounter = 180;
            puck.state = WAIT;
            // Move the puck to center position
            puck.posx = 400 - puck.width/2;
            puck.posy = 300 - puck.height/2;

            // The velocities below determines the direction of the puck movement after the WAIT
            puck.velocityx = 10;
            puck.velocityy = 10;

            // reset the scores
            lScore = 0;
            rScore = 0;

            lStick.posy = 300 - lStick.height/2;
            lStick.speed = 0;
            lStick.lastMoveDir = 0;
            lStick.acc = 0;

            rStick.posy = 300 - rStick.height/2;
            rStick.speed = 0;
            rStick.lastMoveDir = 0;
            rStick.acc = 0;
        }    

        if(keystate[SDL_SCANCODE_P] && event.type == SDL_KEYDOWN)
        {
            if(puck.state != PAUSE)
            {
                prevState = puck.state;
                puck.state = PAUSE;
            }    
            else
            {
                puck.state = prevState;
            }
                
        }

        // angle of the line connecting the ball and the right stick
        angle = -atan2(((float)(rStick.posy+rStick.height/2)-(puck.posy+puck.height/2)),(float)(800 - rStick.width/2 - (puck.posx + puck.width/2)));

        if(puck.state!=PAUSE)
            rStick.accUpdate(20.0f*(1.01f*angle-oldAngle)); // update the acceleration of the right stick (proportional to LOS rate)

        oldAngle = angle; // update old angle for the next iteration

        puckResult = puck.update(lStick, rStick); // update puck position and check for hits (collisions)

        // play appropriate sound effect
        if(puckResult==SIDE_HIT)
            soundPlayer.playSideHitEffect();

        if(puckResult==STICK_HIT)
            soundPlayer.playStickHitEffect();

        if(puckResult==LEFT_SCORE)
        {
            lScore++;
            soundPlayer.playScoreEffect();
        }
            
        if(puckResult==RIGHT_SCORE)
        {
            rScore++;
            soundPlayer.playScoreEffect();
        }
            
       renderer.render(objects,puck,lScore, rScore);
    }
    // destroy texture
    SDL_DestroyTexture(renderer.tex);
 
    // destroy renderer
    SDL_DestroyRenderer(renderer.rend);
 
    // destroy window
    SDL_DestroyWindow(renderer.win);

    // free the sound effects
    Mix_FreeChunk(soundPlayer.boop);
    Mix_FreeChunk(soundPlayer.score);
    Mix_FreeChunk(soundPlayer.wallHit);

    // close SDL
    SDL_Quit();
 
    return 0;
}