#include "./protected_game_list.h"

void ProtectedGameList::add_new_game(Game* game){
    std::lock_guard<std::mutex> lock(m);
    games.push_back(game);
}

int ProtectedGameList::games_size(){
    std::lock_guard<std::mutex> lock(m);
    return games.size();
}

bool ProtectedGameList::game_name_exist(const std::string& game_name){
    std::lock_guard<std::mutex> lock(m);
    for (Game *game : games){
        if (game->compare_game_name(game_name))
            return true;
    }
    return false;
}

Game* ProtectedGameList::game_code_exist(const int32_t& codigo) {
    Game* return_game = nullptr;
    std::lock_guard<std::mutex> lock(m);
    for (Game *game: games){
        if (game->compare_code(codigo))
            return_game = game;
    }
    return return_game;
}

void ProtectedGameList::join_games() {
    for (Game *game : games){
        game->stop_playing();
        game->join();
        delete game;
    }
    games.clear();
}

bool ProtectedGameList::delete_player(int32_t& player_id) {
    for (Game *game: games){
        if (game->delete_player(player_id)){
            if (game->is_empty()){  //Chequeo si no hay mas jugadores en la partida.
                game->join();
                delete game;
                games.remove(game);
                return true;
            }
            break;
        }
    }

}

void ProtectedGameList::reap_dead() {
    games.remove_if([](Game *g) {
    if (g->is_not_playing()) {
        g->join();  //Si se murio le hago un join al game
        delete g;   //Elimino el game
        return true;
    }
    return false; });
}