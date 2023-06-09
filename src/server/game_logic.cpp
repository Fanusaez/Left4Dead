#include "game_logic.h"
#include <iostream>
#include "../game_logic/weapons/idf.h"
#include "../game_logic/zombies/infected.h"
#include "../common/instructionsDTO/move_dto.h"
#include "../common/move_type.h"
#include <ctime>

GameLogic::GameLogic() : game_map(100,30) {
    game_map.add_random_zombie();
    game_map.add_random_zombie();
    game_map.add_random_zombie();
    game_map.add_random_zombie();
}

void GameLogic::add_soldier(int* player_id) {
    Soldier* soldier = game_map.get_soldier_with_idf();    
    playerSoldierMap[*player_id] = soldier;
    timer = 0;  //Esto va aca?
}

void GameLogic::new_instruction(InstructionsDTO* instruction) {
    switch (instruction->get_instruction()) {
    case MOVE:
        move(instruction);
        break;
    case RELOAD:
        reload(instruction->get_player_id());
        break;
    case SHOOT:
        shoot(instruction->get_player_id());
        break;
    case GRANEDE:
                
        break;
    }
}

GameDTO GameLogic::get_game() {
    GameDTO game_dto;
    for (const auto& piar: playerSoldierMap){
        Soldier *soldier = piar.second;
        SoldierObjectDTO soldier_dto(piar.first,soldier->get_id(), soldier->get_health(), soldier->get_x_pos(), 
                                soldier->get_y_pos(), soldier->get_weapon()->get_bullets(),
                                soldier->get_state()->soldier_state ,IDF, soldier->facing_left());
        game_dto.add_soldier(soldier_dto);
        //piar.second->set_idle();
        //std::cout<<piar.second->get_x_pos()<<","<<piar.second->get_y_pos()<<std::endl;
    }
    std::vector<Zombie*>* zombies = game_map.get_zombies();
    for (const auto& zombie: *zombies){
        ZombieObjectDTO zombieDTO(zombie->get_id(), zombie->get_x_pos(), zombie->get_y_pos(), zombie->get_state()->zombie_state, zombie->facing_left());
        game_dto.add_zombie(zombieDTO);
        //std::cout<<zombie->get_x_pos()<<","<<zombie->get_y_pos()<<std::endl;
    
    }
    return game_dto;
}

void GameLogic::move (InstructionsDTO* instruction) {
    MoveDTO* move_dto = dynamic_cast<MoveDTO*>(instruction);
    Soldier* soldier = playerSoldierMap[move_dto->get_player_id()];
    switch (move_dto->get_move_type()) {
    case 0:
        soldier->move_right(timer);
        //std::cout<<"RIGTH"<<std::endl;
        break;
    case 1:
        soldier->move_left(timer);
        //std::cout<<"LEFT"<<std::endl;
        break;
    case 2:
        soldier->move_up(timer);
        //std::cout<<"UP"<<std::endl;
        break;
    case 3:
        soldier->move_down(timer);
        //std::cout<<"DOWN"<<std::endl;
        break;
    case 4:
        soldier->stop_action();
        break;
    }
}

void GameLogic::reload (int player_id) {
    Soldier* soldier = playerSoldierMap[player_id];
    soldier->reload(timer);
}

void GameLogic::shoot (int player_id) {
    Soldier* soldier = playerSoldierMap[player_id];
    soldier->shoot(timer);
}

void GameLogic::udpate_game(){
    for (const auto& piar: playerSoldierMap){
        piar.second->update(timer);
    }
    //for (const auto& zombie: zombies){
       // zombie->update(timer);
    //}
    game_map.update(timer);
    timer += 0.05;
}

void GameLogic::delete_soldier(int* player_id){
    auto it = playerSoldierMap.find(*player_id);
    if (it != playerSoldierMap.end()) {
        delete it->second;
        playerSoldierMap.erase(it);
    }
}

