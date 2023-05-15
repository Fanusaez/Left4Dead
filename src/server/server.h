#ifndef SERVER_H
#define SERVER_H

#include "acceptor.h"
#include "../common/socket.h"

class Server{
private:    
    Socket server;

    Acceptor acceptor;

public:
    explicit Server(char *port);

    void run();    
};
#endif
