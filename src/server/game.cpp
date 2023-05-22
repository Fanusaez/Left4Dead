#include "game.h"
#include "../common/move.h"

Game::Game(Queue<GameDTO> *queue_sender, std::atomic<bool> &keep_playing, int32_t *code, std::string *game_name) : 
    queue_entrante(10000), keep_playing(keep_playing), code(*code), game_name(*game_name)
{
    queue_salientes.push_back(queue_sender);
}

void Game::run(){
    // Logica del juego
    GameDTO game_dto;
    while (keep_playing)
    {
        InstructionsDTO instructionDTO;
        bool could_pop = queue_entrante.try_pop(instructionDTO);
        //instructionDTO = queue_entrante.pop();
        if (could_pop)
        {
            // Proceso la instrcuccion
            if (instructionDTO.get_instruction() == MOVE){
                if (static_cast<Move>(instructionDTO.get_parameters().at(0)) == LEFT)
                    std::cout<<"Left"<<std::endl;
                if (static_cast<Move>(instructionDTO.get_parameters().at(0)) == RIGHT)
                    std::cout << "Right" << std::endl;
                if (static_cast<Move>(instructionDTO.get_parameters().at(0)) == UP)
                    std::cout << "Up" << std::endl;
                if (static_cast<Move>(instructionDTO.get_parameters().at(0)) == DOWN)
                    std::cout << "Down" << std::endl;
            }
        }
        // Actualizo el juego
        // Saco screen
        for (const auto &queue : queue_salientes)
        {
            queue->try_push(game_dto);
        }
    }
}

Queue<InstructionsDTO> *Game::getQueue(){
    return &queue_entrante;
}

void Game::addPlayer(Queue<GameDTO> *queue_sender){
    queue_salientes.push_back(queue_sender);
}

bool Game::compare_code(int32_t *code_to_compare){
    return (code == (*code_to_compare));
}

bool Game::compare_game_name(std::string *game_name_to_compare){
    return (game_name == (*game_name_to_compare));
}