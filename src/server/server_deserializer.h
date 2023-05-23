#ifndef INSTRUCTIONDESERIALIZER_H
#define INSTRUCTIONDESERIALIZER_H

#include "../common/instructions_dto.h"
#include "../common/instructions.h"
#include "../common/socket.h"
#include <string>
#include <vector>

class ServerDeserializer {

private:
    Socket *socket;

public:
    ServerDeserializer(Socket *socket);

    Instructions obtener_instruccion(bool *was_closed);

    std::string deserialize_create(bool *was_closed);

    int32_t deserialize_join(bool *was_closed);

    InstructionsDTO deserialize_move(bool *was_closed, int *player_id);

    InstructionsDTO deserialize_reloading(bool *was_closed);

    InstructionsDTO deserialize_shooting(bool *was_closed);

    InstructionsDTO deserialize_grenede(bool *was_closed);
};
#endif
