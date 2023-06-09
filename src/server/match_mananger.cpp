#include "match_mananger.h"
#include <iostream>
#include <utility>
#include <algorithm> 

MatchMananger::MatchMananger(){
    contador = 0;
}

Queue<InstructionsDTO*> *MatchMananger::create_game(Queue<GameDTO> *queue_sender, std::string *escenario, int *player_id, int32_t *game_code)
{
    if(!game_name_exist(escenario)){   //Si el escenario no existe crearlo
        Game *new_game = new Game(queue_sender,&contador,escenario, player_id);
        games.push_back(new_game);
        *game_code = contador;
        contador++;
        Queue<InstructionsDTO*> *aux = new_game->getQueue();
        new_game->start();
        return (aux);
    }
    else {
        std::cout<<"Existe la partida"<<games.size()<<std::endl;
        return nullptr;
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

Queue<InstructionsDTO*> *MatchMananger::join(Queue<GameDTO> *queue_sender, int *codigo, int *player_id)
{
    Game* game = game_code_exist(codigo);
    if (game){
        game->addPlayer(queue_sender, player_id);
        return game->getQueue();
    }
    return NULL;
}

void MatchMananger::joinGames(){
    for (Game *game : games){
        game->stop_playing();
        game->join();
        delete game;
    }
    games.clear();
}

void MatchMananger::delete_player(int* player_id) {
    m.lock();
    for (Game *game: games){
        if (game->find_player(player_id)){
            if(game->is_empty()){
                game->join();
                delete game;
                games.remove(game);
                contador--;
            }
            break;
        }
    }
    m.unlock();
}