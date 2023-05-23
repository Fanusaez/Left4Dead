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
    int contador;

    std::mutex m;

    std::list<Game* > games;

    std::atomic<bool> keep_playing;

    Game *game_code_exist(int *codigo);

    bool game_name_exist(std::string *escenario);

public:
    MatchMananger();

    Queue<InstructionsDTO> *create_game(Queue<GameDTO> *queue_sender, std::string *escenario, int *player_id);

    Queue<InstructionsDTO> *join(Queue<GameDTO> *queue_sender, int *codigo, int* player_id);

    void joinGames();
};
#endif

    
