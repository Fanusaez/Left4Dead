#ifndef PROTECTEDGAMELIST_H
#define PROTECTEDGAMELIST_H

#include "../server/game.h"

#include <list>

class ProtectedGameList {
private:
    std::mutex m;   //Lo usamos para controlar la lista de games. Podria ser un objeto.

    std::list<Game* > games;    //Lista con todas las partidas que tendra el servidor.
public:

    void add_new_game(Game* game);

    int games_size();

    bool game_name_exist(const std::string& game_name);

    Game* game_code_exist(const int32_t& game_name);

    void join_games();

    bool delete_player(int32_t& player_id);

    void reap_dead();
};
#endif
