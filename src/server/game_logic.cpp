#include "game_logic.h"
#include <iostream>
#include "../game_logic/weapons/idf.h"
#include "../game_logic/zombies/infected.h"
#include "../common/instructionsDTO/move_dto.h"
#include "../common/move_type.h"
#include <ctime>
#include <vector>
#include <utility>

GameLogic::GameLogic() : game_map(400, 47, 0) {}

void GameLogic::add_soldier(const int32_t& player_id) {
    Soldier* soldier = game_map.get_soldier_with_idf();    
    playerSoldierMap[player_id] = soldier;
    timer = 0;
}

void GameLogic::new_instruction(InstructionsDTO* instruction) {
    switch (instruction->get_instruction()) {
    case MOVE:
        move(instruction);
        break;
    case RELOAD:
        reload(instruction);
        break;
    case SHOOT:
        shoot(instruction);
        break;
    default:
        break;
    }
}

GameDTO GameLogic::get_game() {
    GameDTO game_dto;
    //Recorremos los soldados que hay dentro del mapa
    for (const auto& piar: playerSoldierMap){
        Soldier *soldier = piar.second;
        SoldierObjectDTO soldier_dto(piar.first,soldier->get_id(), soldier->get_health(), 
                                soldier->get_x_pos(), soldier->get_y_pos(), 
                                soldier->get_weapon()->get_bullets(),
                                soldier->get_state()->soldier_state ,IDF, soldier->facing_left());
        game_dto.add_soldier(soldier_dto);
    }
    //Obtenemos y recorremos los zombies del mapa
    std::vector<Zombie*>* zombies = game_map.get_zombies();
    for (const auto& zombie: *zombies){
        ZombieObjectDTO zombieDTO(zombie->get_id(), zombie->get_x_pos(), zombie->get_y_pos(), 
                                    zombie->get_state()->zombie_state, zombie->get_type(), zombie->facing_left());
        game_dto.add_zombie(zombieDTO);
    }
    return game_dto;
}

void GameLogic::move(InstructionsDTO* instruction) {
    MoveDTO* move_dto = dynamic_cast<MoveDTO*>(instruction);
    Soldier* soldier = playerSoldierMap[move_dto->get_player_id()];
    switch (move_dto->get_move_type()) {
    case 0:
        soldier->move_right(timer);
        break;
    case 1:
        soldier->move_left(timer);
        break;
    case 2:
        soldier->move_up(timer);
        break;
    case 3:
        soldier->move_down(timer);
        break;
    case 4:
        soldier->stop_action();
        break;
    }
}

void GameLogic::reload(InstructionsDTO* instruction) {
    Soldier* soldier = playerSoldierMap[instruction->get_player_id()];
    soldier->reload(timer);
}

void GameLogic::shoot(InstructionsDTO* instruction) {
    Soldier* soldier = playerSoldierMap[instruction->get_player_id()];
    soldier->shoot(timer);
}

void GameLogic::udpate_game(){
    for (const auto& piar: playerSoldierMap){
        piar.second->update(timer);
    }
    game_map.update(timer);
    timer += 0.05; //Rate del server loop
}
