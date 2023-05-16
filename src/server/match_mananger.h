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

    std::map<std::string, int> escenarios;

    std::list<Game* > games;    //Falta funcion que les haga un join a todas estas partidas

    std::atomic<bool> keep_playing;

    bool existe_escenario(int codigo);

public:
    MatchMananger();

    Queue<std::vector<char>> *getQueueGame(Queue<std::vector<char>> *queue_sender, std::string *escenario);

    int crear_escenario(std::string *escenario);

    bool join(int codigo);

    void joinMatchs();
};
#endif

    
