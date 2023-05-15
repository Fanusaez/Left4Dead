#include "server.h"

int main(int argc, char *argv[]) {
    Server server(argv[1]); //Puerto en el cual escucharemos
    server.run();
    return 0;
}
