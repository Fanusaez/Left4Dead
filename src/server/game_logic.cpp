#include "game_logic.h"
#include <iostream>

void GameLogic::add_soldier(int* player_id) {
    //playerSoldierMap[*player_id] = new Soldier();
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

}

void GameLogic::move (Move move, int player_id) {
    //Soldier soldier = playerSoldierMap[player_id];
    switch (move) {
    case RIGHT:
        //soldier.move_rigth();
        std::cout<<"RIGTH"<<std::endl;
        break;
    case LEFT:
        std::cout<<"LEFT"<<std::endl;
        break;
    case UP:
        std::cout<<"UP"<<std::endl;
        break;
    case DOWN:
        std::cout<<"DOWN"<<std::endl;
        break;
    }
}