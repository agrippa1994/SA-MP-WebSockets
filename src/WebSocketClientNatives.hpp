#pragma once
#include "PAWN.hpp"

cell AMX_NATIVE_CALL CreateWSClient(AMX *amx, cell *params);
cell AMX_NATIVE_CALL DestroyWSClient(AMX *amx, cell *params);
cell AMX_NATIVE_CALL WSClientConnect(AMX *amx, cell *params);
cell AMX_NATIVE_CALL WSClientDisconnect(AMX *amx, cell *params);
cell AMX_NATIVE_CALL WSClientIsConnected(AMX *amx, cell *params);
cell AMX_NATIVE_CALL WSClientSend(AMX *amx, cell *params);

void UnloadWSClients();
