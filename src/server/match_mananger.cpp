#include "match_mananger.h"
#include <iostream>
#include <utility>
#include <algorithm> 

MatchMananger::MatchMananger(){
    contador = 0;
}

Queue<InstructionsDTO> * MatchMananger::create_game(Queue<GameDTO> *queue_sender, std::string *escenario){
    if(!game_name_exist(escenario)){   //Si el escenario no existe crearlo
        Game *new_game = new Game(queue_sender, std::ref(keep_playing),&contador,escenario);
        games.push_back(new_game);
        contador++;
        Queue<InstructionsDTO> *aux = new_game->getQueue();
        new_game->start();
        return (aux);
    }
    else {
        return NULL;
    }
}

bool MatchMananger::game_name_exist(std::string *game_name){
    bool exist = false;
    m.lock();
    for (Game *game : games){
        if (game->compare_game_name(game_name))
            exist = true;
    }
    m.unlock();
    return exist;
}

Game* MatchMananger::game_code_exist(int *codigo){
    Game* return_game = NULL;
    m.lock();
    for (Game *game: games){
        if (game->compare_code(codigo))
            return_game = game;
    }
    m.unlock();
    return return_game;
}

Queue<InstructionsDTO> *MatchMananger::join(Queue<GameDTO> *queue_sender, int *codigo)
{
    Game* game = game_code_exist(codigo);
    if (game){
        game->addPlayer(queue_sender);
        return game->getQueue();
    }
    return NULL;
}

void MatchMananger::joinGames(){
    for (Game *game : games){
        keep_playing = false;
        game->join();
        delete game;
    }
    games.clear();
}