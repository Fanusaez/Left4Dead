#ifndef CLIENTSERIALIZER_H
#define CLIENTSERIALIZER_H

#include <vector>
#include <string>
#include <cstdint>

#include "../common/game_mode.h"
#include "../common/soldier_type.h"
#include "../common/move_type.h"

class ClientSerializer{
private:
public:
    /*----------------------Game message--------------------*/

    std::vector<char> serialize_start_playing();

    std::vector<char> serialize_move(const MoveType move);

    std::vector<char> serialize_reloading();

    std::vector<char> serialize_shooting();

    std::vector<char> serialize_throw_grenede(const uint8_t& time);
};
#endif
