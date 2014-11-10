#ifndef WEBSOCKETSERVERNATIVES_HPP
#define WEBSOCKETSERVERNATIVES_HPP

#include "PAWN.hpp"

cell AMX_NATIVE_CALL CreateWSServer(AMX *amx, cell *params);
cell AMX_NATIVE_CALL DestroyWSServer(AMX *amx, cell *params);
cell AMX_NATIVE_CALL WSServerStartListen(AMX *amx, cell *params);
cell AMX_NATIVE_CALL WSServerStopListen(AMX *amx, cell *params);
cell AMX_NATIVE_CALL WSServerConnected(AMX *amx, cell *params);
cell AMX_NATIVE_CALL WSServerSend(AMX *amx, cell *params);
cell AMX_NATIVE_CALL WSServerSentToAll(AMX *amx, cell *params);
cell AMX_NATIVE_CALL WSServerGetIP(AMX *amx, cell *params);

void UnloadWSServers();

#endif
