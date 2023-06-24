#include "game_logic.h"
#include <iostream>
#include "../game_logic/weapons/idf.h"
#include "../game_logic/zombies/infected.h"
#include "../common/instructionsDTO/move_dto.h"
#include "../common/instructionsDTO/grenade_dto.h"
#include "../common/move_type.h"
#include <ctime>
#include <vector>
#include <utility>

GameLogic::GameLogic(GameMode& game_mode) {
    if(game_mode == SURVIVAL)
        game_map = new Survival(100, 47, 0);
    else
        game_map = new ClearTheZone(100, 47, 0);

}

void GameLogic::add_soldier_idf(const int32_t& player_id) {
    Soldier* soldier = game_map->get_soldier_with_idf();    
    playerSoldierMap[player_id] = soldier;
    timer = 0;
}

void GameLogic::add_soldier_scout(const int32_t& player_id) {
    Soldier* soldier = game_map->get_soldier_with_scout();    
    playerSoldierMap[player_id] = soldier;
    timer = 0;
}

void GameLogic::add_soldier_p90(const int32_t& player_id) {
    Soldier* soldier = game_map->get_soldier_with_p90();    
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
    case THROW_EXPLOSIVE_GRENADE:
        grenade(instruction);
        break;
    case THROW_SMOKE_GRENADE:
        smoke_grenade(instruction);
    case CALL_AIR_STRIKE:
        air_strake(instruction);
    case REVIVE:
        revive(instruction);
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
                                soldier->get_time_to_throw_explosive_grenade(),
                                soldier->get_time_to_throw_smoke_grenade(),
                                soldier->get_time_to_call_air_strike(),
                                soldier->get_state()->soldier_state ,soldier->get_weapon()->get_type(),
                                soldier->facing_left());
        game_dto.add_soldier(soldier_dto);
        if (ExplosiveGrenade* grenade = soldier->get_explosive_grenade()){
            if (grenade->get_state()->exploting()) {
                GrenadeObjectDTO grenade_dto(grenade->id,grenade->get_state()->get_x_explosion(),
                grenade->get_state()->get_y_explosion(),EXPLOSIVE_GRENADE);
                game_dto.add_element(grenade_dto);
            }
        }
        if (SmokeGrenade* grenade = soldier->get_smoke_grenade()){
            if (grenade->get_state()->exploting()) {
                GrenadeObjectDTO grenade_dto(grenade->id,grenade->get_state()->get_x_explosion(),
                grenade->get_state()->get_y_explosion(),SMOKE_GRENADE);
                game_dto.add_element(grenade_dto);
            }
        }
        if (AirStrike* air_strike = soldier->get_air_strike()){
            if (air_strike->exploding()) {
                std::vector<std::vector<int16_t>> matrix = air_strike->get_positions_for_explosion();
                int i = 0;
                for(const auto position: matrix){
                    //std::cout<<"Cargo granada"<<position[0]<<", "<<position[1]<<std::endl;
                    GrenadeObjectDTO grenade_dto(air_strike->id+i, position[0], position[1],EXPLOSIVE_GRENADE);
                    game_dto.add_element(grenade_dto);
                    i++;
                }
            }
        }
        game_dto.add_game_stats(GameStats(soldier->get_total_bullets_shot(),game_map->get_total_zombies_dead()));
    }
    //Obtenemos y recorremos los zombies del mapa
    std::vector<Zombie*>* zombies = game_map->get_zombies();
    for (const auto& zombie: *zombies){
        ZombieObjectDTO zombieDTO(zombie->get_id(), zombie->get_health(), zombie->get_x_pos(),
                                    zombie->get_y_pos(), zombie->get_state()->zombie_state,
                                    zombie->get_type(), zombie->facing_left());
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

void GameLogic::grenade(InstructionsDTO* instruction) {
    GrenadeDTO* grenade_dto = dynamic_cast<GrenadeDTO*>(instruction);
    Soldier* soldier = playerSoldierMap[instruction->get_player_id()];
    soldier->throw_explosive_grenade(timer, grenade_dto->get_time());
}

void GameLogic::smoke_grenade(InstructionsDTO* instruction) {
    GrenadeDTO* grenade_dto = dynamic_cast<GrenadeDTO*>(instruction);
    Soldier* soldier = playerSoldierMap[instruction->get_player_id()];
    soldier->throw_smoke_grenade(timer, grenade_dto->get_time());
}

void GameLogic::air_strake(InstructionsDTO* instruction) {
    GrenadeDTO* grenade_dto = dynamic_cast<GrenadeDTO*>(instruction);
    Soldier* soldier = playerSoldierMap[instruction->get_player_id()];
    soldier->call_air_strike(timer);
}

void GameLogic::revive(InstructionsDTO* instruction) {
    Soldier* soldier = playerSoldierMap[instruction->get_player_id()];
    soldier->revive_partner(timer);
}

void GameLogic::udpate_game(){
    for (const auto& piar: playerSoldierMap){
        piar.second->update(timer);
    }
    game_map->update(timer);
    timer += 0.05; //Rate del server loop
}

bool GameLogic::game_over() {
    return game_map->is_game_over();
}

GameLogic::~GameLogic() {
    delete game_map;
}