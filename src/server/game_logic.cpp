#include "game_logic.h"
#include <iostream>
#include "../game_logic/weapons/idf.h"
#include "../common/move.h"
#include <ctime>

GameLogic::GameLogic() : game_map(10000,10000) {}

void GameLogic::add_soldier(int* player_id) {
    Weapon* idf = new Idf;
    std::srand(std::time(0));
    int16_t pos_x = std::rand() % 15 + 1;
    while (!game_map.check_free_position(pos_x,15)){
        int16_t pos_x = std::rand() % 100 + 1;
    }
    Soldier* soldier = new Soldier(idf,game_map,pos_x,15);
    game_map.add_soldier(soldier,pos_x,15);
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
        //std::cout<<piar.second->get_x_position()<<","<<piar.second->get_y_position()<<std::endl;
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
    timer += 0.04;
}

void GameLogic::delete_soldier(int* player_id){
    for (const auto& piar: playerSoldierMap){
        if (piar.first == *player_id)
            playerSoldierMap.erase(*player_id);
    }
}

