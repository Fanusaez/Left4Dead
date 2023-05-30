#include "game.h"
#include "../common/move.h"
#include <unistd.h>
#include <chrono>

Game::Game(Queue<GameDTO> *queue_sender, std::atomic<bool> &keep_playing, int32_t *code, std::string *game_name, int* player_id) : 
    queue_entrante(10000), keep_playing(keep_playing), code(*code), game_name(*game_name), game_logic()
{
    game_logic.add_soldier(player_id);
    queue_salientes[*player_id] = queue_sender;
}

void Game::run(){   
    //InstructionsDTO instructionDTO = queue_entrante.pop(); //Hasta no recibir
    InstructionsDTO instructionDTO;
    auto t1 = std::chrono::high_resolution_clock::now();
    auto t2 = std::chrono::high_resolution_clock::now();
    while (keep_playing)
    {
        bool could_pop = queue_entrante.try_pop(instructionDTO);
        if (could_pop) {
            game_logic.new_instruction(instructionDTO);
        }
        game_logic.udpate_game();
        GameDTO game_dto = game_logic.get_game();
        t2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = t2 - t1;
		double seconds = duration.count();
        usleep(20000);
        if (seconds >= 0.04){
            m.lock();
            for (const auto &queue : queue_salientes) {
                queue.second->try_push(game_dto);
            }
            m.unlock();
            t1 = std::chrono::high_resolution_clock::now();
        }
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