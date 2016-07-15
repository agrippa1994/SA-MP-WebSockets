#pragma once
#include "PAWN.hpp"

cell AMX_NATIVE_CALL CreateWSServer(AMX *amx, cell *params);
cell AMX_NATIVE_CALL DestroyWSServer(AMX *amx, cell *params);
cell AMX_NATIVE_CALL WSServerStartListen(AMX *amx, cell *params);
cell AMX_NATIVE_CALL WSServerStopListen(AMX *amx, cell *params);
cell AMX_NATIVE_CALL WSServerIsListen(AMX *amx, cell *params);
cell AMX_NATIVE_CALL WSServerIsConnected(AMX *amx, cell *params);
cell AMX_NATIVE_CALL WSServerSend(AMX *amx, cell *params);
cell AMX_NATIVE_CALL WSServerSendToAll(AMX *amx, cell *params);
cell AMX_NATIVE_CALL WSServerGetIP(AMX *amx, cell *params);
cell AMX_NATIVE_CALL WSServerKick(AMX *amx, cell *params);

void UnloadWSServers();
