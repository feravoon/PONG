#include "SoundPlayer.h"

SoundPlayer::SoundPlayer()
{

    //Initialize SDL_mixer
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );

    }

    Mix_Volume(-1, 32);

    //Load sound effects
    this->boop = Mix_LoadWAV( "bling.wav" );
    if( this->boop == NULL )
    {
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
    }
    //Load sound effects
    this->wallHit = Mix_LoadWAV( "wallball.wav" );
    if( this->wallHit == NULL )
    {
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
    }

    this->score = Mix_LoadWAV( "score.wav" );
    if( this->score == NULL )
    {
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
    }
}

void SoundPlayer::playEffect()
{
    Mix_PlayChannel( -1, this->boop, 0 );
}

void SoundPlayer::playWallHit()
{
    Mix_PlayChannel( -1, this->wallHit, 0 );
}

void SoundPlayer::playScore()
{
    Mix_PlayChannel( -1, this->score, 0 );
}

