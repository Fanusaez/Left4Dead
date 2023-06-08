#ifndef GAMEOBJECTSTATE_H
#define GAMEOBJECTSTATE_H

enum SoldierObjectState
{
    IDLE_SOLDIER,
    SHOOTING,
    RELOADING,
    MOVING,
    SHOOTING_AND_MOVING
};

enum ZombieObjectState
{
    IDLE_ZOMBIE,
    DEAD,
    BEING_ATTACKED,
    WALKING,
    RUNNING,
    JUMPING,
    ATTACKING,
    SCREAMING,
    STUNNED
};

#endif