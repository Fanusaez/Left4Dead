#include "server.h"

int main(int argc, char *argv[]) {
    try{
        if (argc != 2)
            throw std::runtime_error("Cantidad invalida de argumentos");
        Server server(argv[1]); //Puerto en el cual escucharemos
        server.run();
        return 0;
    } catch (const std::runtime_error &e) {
        std::cout<<e.what()<<std::endl;
        return 1;
    }
}
