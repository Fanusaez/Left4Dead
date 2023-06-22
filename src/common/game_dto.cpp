#include "game_dto.h"
#include <iostream>

GameDTO::GameDTO() : soldiers(), zombies(), elements(), end_game(false), game_stats(0,0) {}

GameDTO::GameDTO(std::vector<SoldierObjectDTO> soldiers, std::vector<ZombieObjectDTO> zombies)
 : soldiers(soldiers), zombies(zombies), end_game(false), game_stats(0,0){}

void GameDTO::add_soldier(SoldierObjectDTO soldier){
    soldiers.push_back(soldier);
}

void GameDTO::add_zombie(ZombieObjectDTO zombie){
    zombies.push_back(zombie);
}

void GameDTO::add_element(GrenadeObjectDTO element){
    elements.push_back(element);
}

std::vector<SoldierObjectDTO> GameDTO::get_soldiers(){
    return soldiers;
}

std::vector<ZombieObjectDTO> GameDTO::get_zombies(){
    return zombies;
}

std::vector <GrenadeObjectDTO> GameDTO::get_elements()
{
	return elements;
}

GameStats GameDTO::get_game_stats() {
    return game_stats;
}

bool GameDTO::is_end_game() {
    return end_game;
}

void GameDTO::add_game_stats(GameStats game_stats) {
    this->game_stats = game_stats;
}  

void GameDTO::set_end_game(bool end_game) {
    this->end_game = end_game;
}