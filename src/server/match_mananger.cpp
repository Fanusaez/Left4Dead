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
        protected_game_list.add_new_game(new_game);
        game_code = game_counter;
        game_counter++;
        Queue<InstructionsDTO*> *aux = new_game->getQueue();
        new_game->start();
        return (aux);
    } else {
        //Podria ser una excepcion esto
        std::cout<<"Existe la partida"<<protected_game_list.games_size()<<std::endl;
        return nullptr;
    }
}

bool MatchMananger::game_name_exist(const std::string& game_name){
    return protected_game_list.game_name_exist(game_name);
}

Game* MatchMananger::game_code_exist(const int32_t& codigo){
    return protected_game_list.game_code_exist(codigo);
}

Queue<InstructionsDTO*> *MatchMananger::join(Queue<GameDTO> *queue_sender, 
                                            int32_t& codigo, int32_t& player_id) {
    Game* game = game_code_exist(codigo);
    if (game && !game->is_playing()){
        game->addPlayer(queue_sender, player_id);
        return game->getQueue();
    }
    return nullptr; //Se podria lanzar una excepcion
}

void MatchMananger::joinGames(){
    protected_game_list.join_games();
}

void MatchMananger::delete_player(int32_t& player_id) {
    //Si al alimintar me qeude sin jugadores elimino el juego
    if (protected_game_list.delete_player(player_id)) 
        game_counter--;
}
