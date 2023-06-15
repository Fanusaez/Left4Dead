#include "match_mananger.h"
#include <iostream>
#include <utility>
#include <algorithm> 

MatchMananger::MatchMananger() {
    game_counter = 0;
}

Queue<InstructionsDTO*> *MatchMananger::create_game(Queue<GameDTO> *queue_sender, 
                    std::string& escenario, int32_t& player_id, int32_t& game_code)
{
    if (!game_name_exist(escenario)){   //Si el escenario no existe crearlo
        //Le paso la queue a la cual va a tener que pushear el game
        //Tambien es necesario el game_counter que sera el codigo que tendra junto con el nombre
        //y el primer jugador que tendra.
        Game *new_game = new Game(queue_sender,game_counter,escenario, player_id);
        games.push_back(new_game);
        game_code = game_counter;
        game_counter++;
        Queue<InstructionsDTO*> *aux = new_game->getQueue();
        new_game->start();
        return (aux);
    } else {
        //Podria ser una excepcion esto
        std::cout<<"Existe la partida"<<games.size()<<std::endl;
        return nullptr;
    }
}

bool MatchMananger::game_name_exist(const std::string& game_name){
    bool exist = false;
    m.lock();
    for (Game *game : games){
        if (game->compare_game_name(game_name))
            exist = true;
    }
    m.unlock();
    return exist;
}

Game* MatchMananger::game_code_exist(const int32_t& codigo){
    Game* return_game = NULL;
    m.lock();
    for (Game *game: games){
        if (game->compare_code(codigo))
            return_game = game;
    }
    m.unlock();
    return return_game;
}

Queue<InstructionsDTO*> *MatchMananger::join(Queue<GameDTO> *queue_sender, 
                                            int32_t& codigo, int32_t& player_id) {
    Game* game = game_code_exist(codigo);
    if (game){
        game->addPlayer(queue_sender, player_id);
        return game->getQueue();
    }
    return nullptr; //Se podria lanzar una excepcion
}

void MatchMananger::joinGames(){
    for (Game *game : games){
        game->stop_playing();
        game->join();
        delete game;
    }
    games.clear();
}

void MatchMananger::delete_player(int32_t& player_id) {
    m.lock();
    for (Game *game: games){
        if (game->delete_player(player_id)){
            if (game->is_empty()){  //Chequeo si no hay mas jugadores en la partida.
                game->join();
                delete game;
                games.remove(game);
                game_counter--;
            }
            break;
        }
    }
    m.unlock();
}
