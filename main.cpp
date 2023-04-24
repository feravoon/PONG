#include "Renderer.h"
#include "Stick.h"
#include "Puck.h"
#include <iostream>
#include <math.h>
 
int main(int argc, char *argv[])
{
    Renderer renderer;
    Stick lStick(LEFT);
    Stick rStick(RIGHT);
    Puck puck;
    GameObject* objects[3] = {&lStick, &rStick, &puck};
    int lScore = 0;
    int rScore = 0;
    int puckResult = 0;
    // controls animation loop
    int close = 0;
 
    // speed of box
    //int speed = 3;
    SDL_Event event;
    const Uint8* keystate;
    // animation loop
    while (!close) {
        // Events management
        if(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                close = true;
                break;
            }
        }

        keystate = SDL_GetKeyboardState(NULL);

        if(keystate[SDL_SCANCODE_UP] | keystate[SDL_SCANCODE_W])
            lStick.moveUp();
        else if(keystate[SDL_SCANCODE_DOWN] | keystate[SDL_SCANCODE_S])
            lStick.moveDown();
        else
            lStick.lastMoveDir = 0;

        if((puck.posy+puck.height/2)>(rStick.posy+rStick.height/2+15))
            rStick.moveDown();
        else if(((puck.posy+puck.height/2)<(rStick.posy+rStick.height/2-15)))
            rStick.moveUp();
        else
            rStick.lastMoveDir = 0;

        puckResult = puck.update(lStick, rStick);

        if(puckResult==1)
            lScore++;

        if(puckResult==-1)
            rScore++;

        rStick.speed = puck.posx/150.0f;
        /*
        if(keystate[SDL_SCANCODE_LEFT] | keystate[SDL_SCANCODE_A])
            dest.x -= speed;
        if(keystate[SDL_SCANCODE_RIGHT] | keystate[SDL_SCANCODE_D])
            dest.x += speed;
        */
       renderer.render(objects,puck,lScore, rScore);
    }
    // destroy texture
    SDL_DestroyTexture(renderer.tex);
 
    // destroy renderer
    SDL_DestroyRenderer(renderer.rend);
 
    // destroy window
    SDL_DestroyWindow(renderer.win);
     
    // close SDL
    SDL_Quit();
 
    return 0;
}