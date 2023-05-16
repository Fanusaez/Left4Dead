#ifndef GAME_H
#define GAME_H

#include "../common/queue.h"
#include "../common/thread.h"

#include <list>
#include <atomic>

class Game : public Thread {
private:
    //Juego juego

    // La queue donde el player_receiver va a pushear es eta
    Queue<std::vector<char>> queue_entrante;
 
    // Tengo una referencia  a la queue del sender
    std::list<Queue<std::vector<char>> *> queue_salientes;

    std::atomic<bool> &keep_playing;

public:
    Game(Queue<std::vector<char>> *queue_sender, std::atomic<bool> &keep_playing);

    void run() override;

    Queue<std::vector<char>> *getQueue();
};
#endif
