#include "match_mananger.h"
#include <iostream>
#include <utility>
#include <algorithm> 

MatchMananger::MatchMananger(){
    contador = 0;
}

Queue<std::vector<char>> * MatchMananger::crear(Queue<std::vector<char>> *queue_sender, std::string *escenario){
    if(crear_escenario(escenario) != -1){
        Game* new_game = new Game(queue_sender);
        games.push_back(new_game);
        Queue<std::vector<char>> *aux = new_game->getQueue();
        new_game->start();
        return (aux);
    }
    else {
        return NULL;
    }
}

int32_t MatchMananger::crear_escenario(std::string *escenario){
    m.lock();
    auto it = escenarios.find(*escenario);

    if (it != escenarios.end()) {
        //Error
        m.unlock();
        return -1;
    } else {
        escenarios.insert(std::make_pair(*escenario, contador));
        contador++;
        m.unlock();
        return (contador-1);
    }
}

bool MatchMananger::existe_escenario(int codigo){
    m.lock();
    bool exist = std::any_of(escenarios.begin(), escenarios.end(),
                       [=](const auto &elem)
                       { return elem.second == codigo; });
    m.unlock();
    return exist;
}

bool MatchMananger::join(int codigo){
    return (existe_escenario(codigo));
}
