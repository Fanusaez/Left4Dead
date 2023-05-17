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

    Queue<std::vector<char>> *create_game(Queue<std::vector<char>> *queue_sender, std::string *escenario);

    Queue<std::vector<char>> *join(Queue<std::vector<char>> *queue_sender, int *codigo);

    void joinGames();
};
#endif

    
