#include "WebSocketClientNatives.hpp"
#include "WebSocketClientManager.hpp"

cell AMX_NATIVE_CALL CreateWSClient(AMX *amx, cell *params) {
    try {
        return WebSocketClientManager::sharedWebSocketClientManager().create(
                    PAWN::CellToString(params[1]),
                    PAWN::CellToString(params[2]),
                    PAWN::CellToString(params[3]),
                    PAWN::CellToString(params[4]));
    } catch(...) { return 0; }
}

cell AMX_NATIVE_CALL DestroyWSClient(AMX *amx, cell *params) {
    try {
        return WebSocketClientManager::sharedWebSocketClientManager()
                .destroy(params[1]);
    } catch(...) { return 0; }
}

cell AMX_NATIVE_CALL WSClientConnect(AMX *amx, cell *params) {
    try {
        WebSocketClientManager::sharedWebSocketClientManager()
                .getClient(params[1])
                ->connect(PAWN::CellToString(params[2]));
    } catch(...) { return 0; }
}

cell AMX_NATIVE_CALL WSClientDisconnect(AMX *amx, cell *params) {
    try {
        WebSocketClientManager::sharedWebSocketClientManager()
                .getClient(params[1])
                ->disconnect();
    } catch(...) { return 0; }
}

cell AMX_NATIVE_CALL WSClientIsConnected(AMX *amx, cell *params) {
    try {
        WebSocketClientManager::sharedWebSocketClientManager()
                .getClient(params[1])
                ->isConnected();
    } catch(...) { return 0; }
}

cell AMX_NATIVE_CALL WSClientSend(AMX *amx, cell *params) {
    try {
        WebSocketClientManager::sharedWebSocketClientManager()
                .getClient(params[1])
                ->send(PAWN::CellToString(params[2]));
    } catch(...) { return 0; }
}

void UnloadWSClients() {
    try {
        WebSocketClientManager::sharedWebSocketClientManager()
                .destroyAll();
    } catch(...) { }
}
