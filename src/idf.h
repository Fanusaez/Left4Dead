#ifndef  IDF_H_
#define  IDF_H_

#include <cstdint>
#include "walker.h"
#include "weapon.h"

class Idf {
 private:
    std::uint16_t bullets = 50;
    std::uint16_t close_range_damage = 30;
    std::uint16_t long_range_damage = 15;
void reload();

 public:

void shoot(Walker& walker);

};
#endif // IDF_H_
