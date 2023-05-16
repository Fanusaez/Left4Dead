#ifndef ACCEPTOR_H
#define ACCEPTOR_H

#include "../common/thread.h"
#include "../common/socket.h"
#include "match_mananger.h"
#include "player.h"

#include <list>

class Acceptor : public Thread{
private:
    Socket* server;

    std::list <Player *> players;

    MatchMananger match_mananger;

public:
    explicit Acceptor(Socket* server);

    void run() override;

    void reap_dead();

    void kill_all();

    ~Acceptor() override;
};
#endif
