#include "game.h"

Game::Game(Queue<std::vector<char>> *queue_sender, std::atomic<bool> &keep_playing) : queue_entrante(10000), keep_playing(keep_playing){
    queue_salientes.push_back(queue_sender);
}

void Game::run(){
    //Logica del juego
    while (keep_playing){
        std::vector<char> bytes;
        bool could_pop = queue_entrante.try_pop(bytes);
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