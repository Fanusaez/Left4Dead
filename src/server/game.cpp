#include "game.h"
#include "../common/move.h"
#include <unistd.h>
#include <chrono>

Game::Game(Queue<GameDTO> *queue_sender, int32_t *code, std::string *game_name, int* player_id) : 
    queue_entrante(10000), code(*code), game_name(*game_name), game_logic(), keep_playing(true)
{
    game_logic.add_soldier(player_id);
    queue_salientes[*player_id] = queue_sender;
}

void Game::run(){   
    InstructionsDTO instructionDTO;
    bool could_pop;
    double rate = 0.04;
    while (keep_playing)
    {
        auto t_start = std::chrono::high_resolution_clock::now();
        could_pop = queue_entrante.try_pop(instructionDTO);
        int count = 0;
        while(could_pop){ //Controlar por cantidad y si no pudo popear mas
            game_logic.new_instruction(instructionDTO);
            could_pop = queue_entrante.try_pop(instructionDTO);
            count++;
        }
        game_logic.udpate_game();
        GameDTO game_dto = game_logic.get_game();
        m.lock();   
        for (const auto &queue : queue_salientes) {
            queue.second->try_push(game_dto);
        }
        m.unlock();
        auto t_end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(t_end - t_start);
        double sleep_time = rate - duration.count();
        if (sleep_time > 0)
            std::this_thread::sleep_for(std::chrono::duration<double>(sleep_time));
    }
}

Queue<InstructionsDTO> *Game::getQueue(){
    return &queue_entrante;
}

void Game::addPlayer(Queue<GameDTO> *queue_sender,int* player_id){
    m.lock();
    game_logic.add_soldier(player_id);
    queue_salientes[*player_id] = queue_sender;
    m.unlock();
}

bool Game::compare_code(int32_t *code_to_compare){
    return (code == (*code_to_compare));
}

bool Game::compare_game_name(std::string *game_name_to_compare){
    return (game_name == (*game_name_to_compare));
}

bool Game::find_player(int* player_id){
    for (const auto &queue : queue_salientes){
        if (queue.first == *player_id) {
            queue_salientes.erase(*player_id);
            game_logic.delete_soldier(player_id);
            return true;    
        }
    }
    return false;
}

bool Game::is_empty(){
    if (queue_salientes.empty()){
        keep_playing = false;
        return true;
    }
    return false;
}

void Game::stop_playing(){
    keep_playing = false;
}