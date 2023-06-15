#ifndef PROTECTEDOUTPUTSQUEUE_H
#define PROTECTEDOUTPUTSQUEUE_H

#include "../common/queue.h"
#include "../common/game_dto.h"

#include <map>

class ProtectedOutputsQueue {
private:
    std::mutex m;   //Para proteger el map de las queue_salientes
 
    // Este map almacena <player_id,queue_saliente>. Voy a mandar por toda las queue el GameDTO.
    std::map<int,Queue<GameDTO> *> queue_salientes;
public:
    void push_game(GameDTO& game_dto);

    void add_queue(Queue<GameDTO>* queue_sender,int32_t& player_id);

    int number_of_players();

    bool delete_player(int32_t& player_id);
};
#endif
