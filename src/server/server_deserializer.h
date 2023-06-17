#ifndef INSTRUCTIONDESERIALIZER_H
#define INSTRUCTIONDESERIALIZER_H

#include "../common/instructionsDTO/instructions_dto.h"
#include "../common/instructionsDTO/create_dto.h"
#include "../common/instructionsDTO/join_dto.h"
#include "../common/instructionsDTO/move_dto.h"
#include "../common/instructionsDTO/grenade_dto.h"
#include "../common/instructions_type.h"
#include "../common/socket.h"
#include <string>
#include <vector>

class ServerDeserializer {
private:
    Socket *socket;

    CreateDTO* deserialize_create(bool *was_closed, int32_t& player_id);

    JoinDTO* deserialize_join(bool *was_closed, int32_t& player_id);

    MoveDTO* deserialize_move(bool *was_closed, int32_t& player_id);

    InstructionsDTO* deserialize_reloading(bool *was_closed, int32_t& player_id);

    InstructionsDTO* deserialize_shooting(bool *was_closed, int32_t& player_id);

    GrenadeDTO* deserialize_grenede(bool *was_closed, int32_t& player_id);

    InstructionsDTO* deserialize_start(bool *was_closed, int32_t& player_id);

public:
    explicit ServerDeserializer(Socket *socket);

    InstructionsDTO* obtener_instruccion(bool *was_closed, int32_t& player_id);
};
#endif
