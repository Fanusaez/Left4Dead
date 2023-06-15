#ifndef GAMEOBJECTSTATE_H
#define GAMEOBJECTSTATE_H

enum SoldierObjectState : char {
    IDLE_SOLDIER,
    SHOOTING,
    RELOADING,
    MOVING,
    SOLDIER_DEAD,
    SOLDIER_HURT,
    SHOOTING_AND_MOVING
};

enum ZombieObjectState : char {
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
