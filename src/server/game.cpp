#include "game.h"

Game::Game(Queue<std::vector<char>> *queue_sender) : queue_entrante(10000), queue_saliente(queue_sender){}

void Game::run(){
    //Logica del juego
}

Queue<std::vector<char>> *Game::getQueue(){
    return &queue_entrante;
}