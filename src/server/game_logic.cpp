#include "game_logic.h"
#include <iostream>
#include "../game_logic/weapons/idf.h"
#include "../common/move.h"

GameLogic::GameLogic() : game_map(100,100) {
    std::cout<<"Entro al constructor de game logic" << std::endl;
}

void GameLogic::add_soldier(int* player_id) {
    Weapon* idf = new Idf;
    Soldier* soldier = new Soldier(idf,game_map,5,5);
    game_map.add_soldier(soldier,5,5);
    playerSoldierMap[*player_id] = soldier;
    timer = 0;
}

void GameLogic::new_instruction(InstructionsDTO instruction) {
    switch (instruction.get_instruction()) {
    case MOVE:
        move(static_cast<Move>(instruction.get_parameters().front()), instruction.get_player_id());
        break;
    case RELOAD:
                
        break;
    case SHOOT:
                
        break;
    case GRANEDE:
                
        break;
    }
}

GameDTO GameLogic::get_game() {
    GameDTO game_dto;
    for (const auto& piar: playerSoldierMap){
        SoldierObjectDTO soldier(piar.first, piar.second->get_x_position(), piar.second->get_y_position(), MOVING , IDF);
        game_dto.add_soldier(soldier);
        std::cout<<"pos x: "<<piar.second->get_x_position()<<" pos y: "<<piar.second->get_y_position()<<std::endl;
    }
    return game_dto;
}

void GameLogic::move (Move move, int player_id) {
    Soldier* soldier = playerSoldierMap[player_id];
    switch (move) {
    case 0:
        soldier->move_right(timer);
        std::cout<<"RIGTH"<<std::endl;
        break;
    case 1:
        soldier->move_left(timer);
        std::cout<<"LEFT"<<std::endl;
        break;
    case 2:
        soldier->move_up(timer);
        std::cout<<"UP"<<std::endl;
        break;
    case 3:
        soldier->move_down(timer);
        std::cout<<"DOWN"<<std::endl;
        break;
    }
}

void GameLogic::udpate_game(){
    timer += 0.01;
}

void GameLogic::delete_soldier(int* player_id){
    for (const auto& piar: playerSoldierMap){
        if (piar.first == *player_id)
            playerSoldierMap.erase(*player_id);
    }
}

