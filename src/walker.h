#ifndef WALKER_H_
#define WALKER_H_

#include <cstdint>
#include "game_object.h"

class Walker : public GameObject {
 private:
    std::uint16_t health = 100;
    bool dead = false;
 public:

void get_shot(std::uint16_t damage) override;

};

#endif  // WALKER_H_
