#ifndef GAMEOBJECTSTATE_H
#define GAMEOBJECTSTATE_H

enum SoldierObjectState
{
    IDLE,
    SHOOTING,
    RELOADING,
    MOVING,
    SHOOTING_AND_MOVING
};

enum ZombieObjectState
{
    WALKING,
    RUNNING,
    JUMPING,
    ATTACKING,
    SCREAMING,
    STUNNED
};

#endif