#include "Renderer.h"
#include <SDL2/SDL_ttf.h>

Renderer::Renderer()
{
    // returns zero on success else non-zero
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }

    // creates a window
    this->win = SDL_CreateWindow("PONG", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
 
    // triggers the program that controls your graphics hardware and sets flags
    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
 
    // creates a renderer to render our images
    this->rend = SDL_CreateRenderer(win, -1, render_flags);

    SDL_ShowCursor(SDL_DISABLE);
    // creates a surface to load an image into the main memory
    SDL_Surface* surface;
    SDL_Surface* ballSurface;
 
    // load the image
    surface = IMG_Load("tex.png");
    ballSurface = IMG_Load("ball.png");
    // loads image to our graphics hardware memory.
    this->tex = SDL_CreateTextureFromSurface(rend, surface);
    this->ballTex = SDL_CreateTextureFromSurface(rend, ballSurface);
    // clears main-memory
    SDL_FreeSurface(surface);
    SDL_FreeSurface(ballSurface);
    // let us control our image position so that we can move it with our keyboard.
    SDL_Rect dest;
 
    // connects our texture with dest to control position
    SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);
}

void Renderer::render(GameObject* objects[], Puck puck, int lScore, int rScore)
{
    SDL_Rect dest;
    // set the background color
    if(puck.state==WAIT)
    {
        int grayVal = 32*abs(sin(puck.waitCounter/5.0));
        SDL_SetRenderDrawColor(rend,grayVal,grayVal,grayVal,SDL_ALPHA_OPAQUE);
    }
    else
    {
        SDL_SetRenderDrawColor(rend,0,0,0,SDL_ALPHA_OPAQUE);
    }
    int windowWidth,windowHeight;
    SDL_GetWindowSize(this->win,&windowWidth,&windowHeight);
    float windowHorRatio = 2*windowWidth/800.0f;
    float windowVerRatio = 2*windowHeight/600.0f;
    // clears the screen
    SDL_RenderClear(rend);

    // inits the font system
    TTF_Init();
    //this opens a font style and sets a size
    TTF_Font* Sans = TTF_OpenFont("Teko/Teko-Medium.ttf", 128);

    // this is the color in rgb (8-bit each channel) format
    SDL_Color White = {255, 255, 255};

    // as TTF_RenderText_Solid could only be used on
    // SDL_Surface then you have to create the surface first
    char rtext[20];
    snprintf(rtext,20,"%d",rScore);
    SDL_Surface* rSurfaceMessage = TTF_RenderText_Blended(Sans, rtext, White); 
    char ltext[20];
    snprintf(ltext,20,"%d",lScore);
    SDL_Surface* lSurfaceMessage = TTF_RenderText_Blended(Sans, ltext, White); 
    int wr,hr,wl,hl;
    TTF_SizeText(Sans, ltext, &wl, &hl);
    TTF_SizeText(Sans, rtext, &wr, &hr);
    wl /= 2;
    hl /= 2;
    wr /= 2;
    hr /= 2; 
    // now you can convert it into a texture
    SDL_Texture* lMessage = SDL_CreateTextureFromSurface(rend, lSurfaceMessage);
    SDL_Texture* rMessage = SDL_CreateTextureFromSurface(rend, rSurfaceMessage);

    SDL_Rect rMessage_rect, lMessage_rect; //create a rect
    lMessage_rect.x = (400 - 35 - wl)*windowHorRatio;  //controls the rect's x coordinate 
    lMessage_rect.y = 6*windowVerRatio; // controls the rect's y coordinte
    lMessage_rect.w = wl*windowHorRatio; // controls the width of the rect
    lMessage_rect.h = hl*windowHorRatio; // controls the height of the rect
    rMessage_rect.x = (400 + 35)*windowHorRatio;  //controls the rect's x coordinate 
    rMessage_rect.y = 6*windowVerRatio; // controls the rect's y coordinte
    rMessage_rect.w = wr*windowHorRatio; // controls the width of the rect
    rMessage_rect.h = hr*windowHorRatio; // controls the height of the rect

    SDL_RenderCopy(rend, rMessage, NULL, &rMessage_rect);
    SDL_RenderCopy(rend, lMessage, NULL, &lMessage_rect);
    // Don't forget to free your surface and texture
    SDL_FreeSurface(rSurfaceMessage);
    SDL_DestroyTexture(rMessage);
    SDL_FreeSurface(lSurfaceMessage);
    SDL_DestroyTexture(lMessage);
    TTF_CloseFont(Sans);
    TTF_Quit();

    // Middle line
    dest.w = 10*windowHorRatio;
    dest.h = 600*windowVerRatio;
    dest.x = (400 - 5)*windowHorRatio;
    dest.y = 0*windowVerRatio;
    SDL_RenderCopy(rend, tex, NULL, &dest);

    for(int i=0; i< 3; i++)
    {
        dest.w = objects[i]->width*windowHorRatio;
        if(i<2)
            dest.h = objects[i]->height*windowVerRatio;
        else // special case for the ball
            dest.h = objects[i]->height*windowHorRatio;
        dest.x = objects[i]->posx*windowHorRatio;
        dest.y = objects[i]->posy*windowVerRatio;
        if(i<2)
            SDL_RenderCopy(rend, tex, NULL, &dest);
        else // special case for the ball
            SDL_RenderCopy(rend, ballTex, NULL, &dest);
    }
    SDL_RenderPresent(rend);
}