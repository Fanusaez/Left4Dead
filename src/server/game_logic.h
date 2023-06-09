#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "../common/game_dto.h"
#include "../common/instructionsDTO/instructions_dto.h"
#include "../common/move_type.h"
#include "../game_logic/map.h"
#include "../game_logic/soldier.h"
#include "../game_logic/zombies/zombie.h"
#include <map>

#define SIZE_X  10
#define SIZE_Y  10

class GameLogic {
private:
    float timer;

    GameMap game_map;

    std::map<int,Soldier*> playerSoldierMap;

    std::vector<Zombie*> zombies;

    void move (InstructionsDTO* instruction);

    void reload (int player_id);

    void shoot (int player_id);

public:
    GameLogic();

    void add_soldier(int* player_id);

    void new_instruction(InstructionsDTO* instruction);

    GameDTO get_game();

    void udpate_game();

    void delete_soldier(int* player_id);
};
#endif