#include "Renderer.h"
#include <SDL2/SDL_ttf.h>

Renderer::Renderer()
{
    // returns zero on success else non-zero
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }
    this->win = SDL_CreateWindow("PONG", // creates a window
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       800, 600, 0);
 
    // triggers the program that controls your graphics hardware and sets flags
    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
 
    // creates a renderer to render our images
    this->rend = SDL_CreateRenderer(win, -1, render_flags);

    // creates a surface to load an image into the main memory
    SDL_Surface* surface;
 
    // load the image
    surface = IMG_Load("tex.png");
    // loads image to our graphics hardware memory.
    this->tex = SDL_CreateTextureFromSurface(rend, surface);
 
    // clears main-memory
    SDL_FreeSurface(surface);
 
    // let us control our image position so that we can move it with our keyboard.
    SDL_Rect dest;
 
    // connects our texture with dest to control position
    SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);
}

void Renderer::render(GameObject* objects[], Puck puck, int lScore, int rScore)
{
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
    
    // clears the screen
    SDL_RenderClear(rend);
    TTF_Init();
    //this opens a font style and sets a size
    TTF_Font* Sans = TTF_OpenFont("/Library/Fonts/Arial Unicode.ttf", 48);

    // this is the color in rgb format,
    // maxing out all would give you the color white,
    // and it will be your text's color
    SDL_Color White = {128, 128, 128};

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
    // now you can convert it into a texture
    SDL_Texture* lMessage = SDL_CreateTextureFromSurface(rend, lSurfaceMessage);
    SDL_Texture* rMessage = SDL_CreateTextureFromSurface(rend, rSurfaceMessage);

    SDL_Rect rMessage_rect, lMessage_rect; //create a rect
    lMessage_rect.x = 35;  //controls the rect's x coordinate 
    lMessage_rect.y = 10; // controls the rect's y coordinte
    lMessage_rect.w = wl; // controls the width of the rect
    lMessage_rect.h = hl; // controls the height of the rect
    rMessage_rect.x = 800 - wr - 35;  //controls the rect's x coordinate 
    rMessage_rect.y = 10; // controls the rect's y coordinte
    rMessage_rect.w = wr; // controls the width of the rect
    rMessage_rect.h = hr; // controls the height of the rect

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
    dest.w = 10;
    dest.h = 600;
    dest.x = 400 - 5;
    dest.y = 0;
    SDL_RenderCopy(rend, tex, NULL, &dest);

    for(int i=0; i< 3; i++)
    {
        dest.w = objects[i]->width;
        dest.h = objects[i]->height;
        dest.x = objects[i]->posx;
        dest.y = objects[i]->posy;
        SDL_RenderCopy(rend, tex, NULL, &dest);
    }
    SDL_RenderPresent(rend);
}