#pragma once
#include "Object.h"
#include "Stick.h"

enum PuckState
{
    WAIT = 0,
    MOVE = 1,
    PAUSE = 2
};

enum PuckHitType
{   
    NO_HIT = 0,
    SIDE_HIT = 72,
    STICK_HIT = 67,
    LEFT_SCORE = 1,
    RIGHT_SCORE = -1
};

class Puck : public GameObject
{
    public:
        float velocityx, velocityy;
        PuckState state;
        int waitCounter;
        PuckHitType update(Stick lStick, Stick rStick);
        PuckHitType checkCollision(Stick lStick, Stick rStick);
        Puck();
};