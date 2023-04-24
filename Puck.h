#pragma once
#include "Object.h"
#include "Stick.h"

enum PuckState
{
    WAIT = 0,
    MOVE = 1
};

class Puck : public GameObject
{
    public:
        float velocityx, velocityy;
        PuckState state;
        int waitCounter;
        int update(Stick lStick, Stick rStick);
        int checkCollision(Stick lStick, Stick rStick);
        Puck();
};