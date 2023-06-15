#ifndef MATCHMANANGER_H
#define MATCHMANANGER_H

#include "../common/queue.h"
#include "./protected_game_list.h"
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

    ProtectedGameList protected_game_list;
    
    Game *game_code_exist(const int& codigo);

    bool game_name_exist(const std::string& escenario);

public:
    MatchMananger();

    Queue<InstructionsDTO*> *create_game(Queue<GameDTO> *queue_sender, std::string& escenario, 
                                        int32_t& player_id, int32_t& game_code);

    Queue<InstructionsDTO*> *join(Queue<GameDTO> *queue_sender, int32_t& codigo, int32_t& player_id);

    void joinGames();

    void delete_player(int32_t& player_id);
};
#endif

    
