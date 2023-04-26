#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_timer.h"
#include "Object.h"
#include "Puck.h"

class Renderer
{
    public:
        SDL_Window* win;
        SDL_Renderer* rend;
        SDL_Texture* tex;
        SDL_Texture* ballTex;
        SDL_Rect dest;
        Renderer();
        void render(GameObject* objects[], Puck puck, int lScore, int rScore);
};