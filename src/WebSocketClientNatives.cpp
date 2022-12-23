#include "WebSocketClientNatives.hpp"
#include "WebSocketClientManager.hpp"

cell AMX_NATIVE_CALL CreateWSClient(AMX *amx, cell *params) {
    try {
        auto& manager = WebSocketClientManager::sharedWebSocketClientManager();
        int id = manager.create(
			        amx,
                    PAWN::CellToString(params[1], amx),
                    PAWN::CellToString(params[2], amx),
                    PAWN::CellToString(params[3], amx),
                    PAWN::CellToString(params[4], amx));

        if(id != -1)
            manager.getClient(id)->setID(id);

        return id;
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
                ->connect(PAWN::CellToString(params[2], amx));
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
                ->send(PAWN::CellToString(params[2], amx));
        return 1;
    } catch(...) { return 0; }
}

void UnloadWSClients() {
    try {
        WebSocketClientManager::sharedWebSocketClientManager()
                .destroyAll();
    } catch(...) { }
}
