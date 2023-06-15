#include "./protected_outputs_queue.h"
#include <iostream>
    
void ProtectedOutputsQueue::push_game(GameDTO& game_dto) {
    std::lock_guard<std::mutex> lock(m);
    for (const auto &queue : queue_salientes) {
        queue.second->try_push(game_dto);
    }
}

void ProtectedOutputsQueue::add_queue(Queue<GameDTO>* queue_sender,int32_t& player_id) {
    std::lock_guard<std::mutex> lock(m);
    queue_salientes[player_id] = queue_sender;
}

int ProtectedOutputsQueue::number_of_players() {
    std::lock_guard<std::mutex> lock(m);
    return queue_salientes.size();
}

bool ProtectedOutputsQueue::delete_player(int32_t& player_id) {
    std::lock_guard<std::mutex> lock(m);
    auto it = queue_salientes.find(player_id);
    if (it != queue_salientes.end()){
        queue_salientes.erase(it);
        return true;    
    }
    return false;
}