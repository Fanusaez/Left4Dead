#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "../common/game_dto.h"
#include "../common/instructionsDTO/instructions_dto.h"
#include "../common/move_type.h"
#include "../game_logic/map.h"
#include "../game_logic/soldier.h"
#include "../game_logic/zombies/zombie.h"
#include "../game_logic/playing_modes/clear_the_zone.h"
#include "../game_logic/playing_modes/survival.h"
#include <map>
#include <utility>

#define SIZE_X  10
#define SIZE_Y  10

class GameLogic {
private:
    float timer;    //Usamos el timer para las animaciones y para los update del juego

    Survival game_map;  //Estilo de juego

    //Este mapa guardara los usuarios asociandolos a un soldado con la forma <player_id,soldier>
    std::map<int,Soldier*> playerSoldierMap; 

    void move(InstructionsDTO* instruction);  

    void reload(InstructionsDTO* instruction);

    void shoot(InstructionsDTO* instruction); 

    void grenade(InstructionsDTO* instruction); 

    void smoke_grenade(InstructionsDTO* instruction); 

    void revive(InstructionsDTO* instruction);

public:
    GameLogic();

    void add_soldier_idf(const int32_t& player_id);  

    void add_soldier_scout(const int32_t& player_id);  
    
    void add_soldier_p90(const int32_t& player_id);  
    
    void new_instruction(InstructionsDTO* instruction);

    GameDTO get_game();

    void udpate_game();

    bool game_over();

    void send_stats();
};
#endif
