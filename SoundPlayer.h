#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"

class SoundPlayer
{
    public:
        Mix_Chunk *boop;
        Mix_Chunk *wallHit;
        Mix_Chunk *score;
        SoundPlayer();
        void playStickHitEffect();
        void playSideHitEffect();
        void playScoreEffect();
};