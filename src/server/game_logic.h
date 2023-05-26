#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "../common/game_dto.h"
#include "../common/instructions_dto.h"
#include "../common/move.h"
#include <map>

class GameLogic {
private:

    //std::map<int,Soldier*> playerSoldierMap;

    void move (Move move, int player_id);

public:

    void add_soldier(int* player_id);

    void new_instruction(InstructionsDTO instruction);

    GameDTO get_game();
};
#endif