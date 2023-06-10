#include "game.h"
#include "../common/move_type.h"
#include <unistd.h>
#include <chrono>
#include <string>

double rate = 0.05;

Game::Game(Queue<GameDTO> *queue_sender, int32_t *code, std::string *game_name, int* player_id) : 
    queue_entrante(10000), code(*code), game_name(*game_name), game_logic(), keep_playing(true)
{
    game_logic.add_soldier(player_id);
    queue_salientes[*player_id] = queue_sender;
}

void Game::run(){   
    InstructionsDTO* instructionDTO;
    InstructionsDTO* start;
    bool could_pop;
    for (int i = 0 ; i < queue_salientes.size() ; i++) {
        start = queue_entrante.pop();  //Espero a popoear la señal de start
    }
    while (keep_playing)
    {
        auto t_start = std::chrono::high_resolution_clock::now();
        could_pop = queue_entrante.try_pop(instructionDTO);
        int count = 0;
        while (could_pop) { //Controlar por cantidad y si no pudo popear mas
            game_logic.new_instruction(instructionDTO);
            delete instructionDTO;
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
        std::chrono::duration<double> duration = t_end - t_start;
		double seconds = duration.count();
		double rest = rate - seconds;
		if(rest < 0) {
			double behind = -rest;
        	double lost = behind - std::fmod(behind, rate);
        	t_start += std::chrono::duration_cast<std::chrono::high_resolution_clock::duration>
                                                        (std::chrono::duration<double>(lost));
		} else {
			std::this_thread::sleep_for(std::chrono::duration<double>(rest));
		}
    }
}

Queue<InstructionsDTO*> *Game::getQueue(){
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
    auto it = queue_salientes.find(*player_id);
    if (it != queue_salientes.end()){
        game_logic.delete_soldier(player_id);
        queue_salientes.erase(it);
        return true;    
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

int32_t Game::get_game_code(){
    return code;
}

int Game::get_players(){
    return queue_salientes.size();
}
