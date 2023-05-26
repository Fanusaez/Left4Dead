#include "game.h"
#include "../common/move.h"
#include <unistd.h>

Game::Game(Queue<GameDTO> *queue_sender, std::atomic<bool> &keep_playing, int32_t *code, std::string *game_name, int* player_id) : 
    queue_entrante(10000), keep_playing(keep_playing), code(*code), game_name(*game_name)
{
    //game_logic.add_soldier(player_id);
    queue_salientes.push_back(queue_sender);
}

void Game::run(){
    // Logica del juego
    GameDTO game_dto;
    SoldierObjectDTO soldier(13, 10, 10, RELOADING , P90);
    SoldierObjectDTO soldier2(100, 10.78, 10.85, RELOADING , P90);
    ZombieObjectDTO zombie(20, 30.55, 45.3, STUNNED);
    game_dto.add_soldier(soldier);
    game_dto.add_soldier(soldier2);
    game_dto.add_zombie(zombie);

    while (keep_playing)
    {
        InstructionsDTO instructionDTO;
        bool could_pop = queue_entrante.try_pop(instructionDTO);
        if (could_pop) {
            //game_logic.new_instruction(instructionDTO);
        }
        // Actualizo el juego

        m.lock();
        for (const auto &queue : queue_salientes)
        {
            queue->try_push(game_dto);
        }
        m.unlock();
    }
}

Queue<InstructionsDTO> *Game::getQueue(){
    return &queue_entrante;
}

void Game::addPlayer(Queue<GameDTO> *queue_sender,int* player_id){
    m.lock();
    //game_logic.add_soldier(player_id);
    queue_salientes.push_back(queue_sender);
    m.unlock();
}

bool Game::compare_code(int32_t *code_to_compare){
    return (code == (*code_to_compare));
}

bool Game::compare_game_name(std::string *game_name_to_compare){
    return (game_name == (*game_name_to_compare));
}