#include "game.h"

Game::Game(Queue<std::vector<char>> *queue_sender, std::atomic<bool> &keep_playing, int32_t *code, std::string *game_name) : 
    queue_entrante(10000), keep_playing(keep_playing), code(*code), game_name(*game_name)
{
    queue_salientes.push_back(queue_sender);
}

void Game::run(){
    //Logica del juego
    while (keep_playing){
        std::vector<char> bytes;
        bool could_pop = queue_entrante.try_pop(bytes);
        //Proceso los bytes
        //Actualizo el juego
        //Saco screen
        if (could_pop){
            for (const auto &queue : queue_salientes){
                queue->push(bytes);
            }
        }
    }
}

Queue<std::vector<char>> *Game::getQueue(){
    return &queue_entrante;
}

void Game::addPlayer(Queue<std::vector<char>> *queue_sender){
    queue_salientes.push_back(queue_sender);
}

bool Game::compare_code(int32_t *code_to_compare){
    return (code == (*code_to_compare));
}

bool Game::compare_game_name(std::string *game_name_to_compare){
    return (game_name == (*game_name_to_compare));
}