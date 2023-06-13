#ifndef MATCHMANANGER_H
#define MATCHMANANGER_H

#include "../common/queue.h"
#include "game.h"

#include <map>
#include <list>
#include <vector>
#include <string>
#include <atomic>

class Player;

class MatchMananger{
private:    
    int32_t game_counter;   //Lleva la cuenta de las partidas creadas. Corresponde con el game_code.

    std::mutex m;   //Lo usamos para controlar la lista de games. Podria ser un objeto.

    std::list<Game* > games;    //Lista con todas las partidas que tendra el servidor.

    Game *game_code_exist(const int& codigo);

    bool game_name_exist(const std::string& escenario);

public:
    MatchMananger();

    Queue<InstructionsDTO*> *create_game(Queue<GameDTO> *queue_sender, std::string& escenario, 
                                        int& player_id, int32_t& game_code);

    Queue<InstructionsDTO*> *join(Queue<GameDTO> *queue_sender, int32_t& codigo, int& player_id);

    void joinGames();

    void delete_player(int& player_id);
};
#endif

    
