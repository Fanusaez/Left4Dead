#include "game.h"

Game::Game(Queue<std::vector<char>> *queue_sender) : queue_entrante(10000){
    this->queue_saliente = queue_sender;
}

void Game::run(){
    //Logica del juego
    while (true){
        std::vector<char> recibo = queue_entrante.pop();
        queue_saliente->push(recibo);
    }
}

Queue<std::vector<char>> *Game::getQueue(){
    return &queue_entrante;
}