#ifndef WEAPON_H_
#define WEAPON_H_

class Weapon {
 private:

 public:
virtual std::uint16_t shoot(std::uint16_t zomb_y_pos) = 0;
};
#endif  // WEAPON_H_
