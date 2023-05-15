#ifndef ACCEPTOR_H
#define ACCEPTOR_H

#include "../common/thread.h"
#include "../common/socket.h"

#include <list>

class Acceptor : public Thread{
private:
    Socket* server;

public:
    explicit Acceptor(Socket* server);

    void run() override;

     ~Acceptor() override;
};
#endif
