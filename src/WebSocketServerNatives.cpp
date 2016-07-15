#include "WebSocketServerNatives.hpp"
#include "WebSocketServerManager.hpp"

cell AMX_NATIVE_CALL CreateWSServer(AMX *amx, cell *params) {
    try {
        auto& manager = WebSocketServerManager::sharedWebSocketServerManager();
        int id = manager.create(
                    PAWN::CellToString(params[1]),
                    PAWN::CellToString(params[2]),
                    PAWN::CellToString(params[3]));

        if(id != -1)
            manager.getServer(id)->setID(id);

        return id;
    }
    catch(...) { return 0; }
}

cell AMX_NATIVE_CALL DestroyWSServer(AMX *amx, cell *params) {
    try {
        return WebSocketServerManager::sharedWebSocketServerManager()
                .destroy(params[1]);
    } catch(...) { return 0; }
}

cell AMX_NATIVE_CALL WSServerStartListen(AMX *amx, cell *params) {
    try {
        return WebSocketServerManager::sharedWebSocketServerManager()
                .getServer(params[1])
                ->listen(
                    PAWN::CellToString(params[2]),
                    PAWN::CellToString(params[3]));
    } catch(...) { return 0; }
}

cell AMX_NATIVE_CALL WSServerStopListen(AMX *amx, cell *params) {
    try {
        return WebSocketServerManager::sharedWebSocketServerManager()
                .getServer(params[1])
                ->stopListen();
    } catch(...) { return 0; }
}

cell AMX_NATIVE_CALL WSServerIsListen(AMX *amx, cell *params) {
    try {
        return WebSocketServerManager::sharedWebSocketServerManager()
                .getServer(params[1])
                ->isListening();
    } catch(...) { return 0; }
}

cell AMX_NATIVE_CALL WSServerConnected(AMX *amx, cell *params) {
    try {
        WebSocketServerManager::sharedWebSocketServerManager()
                .getServer(params[1])
                ->getClient(params[2]);
        return 1;
    } catch(...) { return 0; }
}

cell AMX_NATIVE_CALL WSServerSend(AMX *amx, cell *params) {
    try {
        return (cell)(bool)WebSocketServerManager::sharedWebSocketServerManager()
                .getServer(params[1])
                ->getClient(params[2])
                ->send(PAWN::CellToString(params[3]));
    } catch(...) { return 0; }
}

cell AMX_NATIVE_CALL WSServerSentToAll(AMX *amx, cell *params) {
    int clientsSent = 0;
    try {
        const auto& server = WebSocketServerManager::sharedWebSocketServerManager()
                .getServer(params[1]);
        const auto message = PAWN::CellToString(params[2]);
        for(const auto& client: server->getClients()) {
            try {
                server->getClient(client.first)->send(message);
                clientsSent++;
            } catch(...) { }
        }

    } catch(...) { }

    return clientsSent;
}

cell AMX_NATIVE_CALL WSServerGetIP(AMX *amx, cell *params) {
    try {
        auto ip = WebSocketServerManager::sharedWebSocketServerManager()
                .getServer(params[1])
                ->getClient(params[2])
                ->get_socket()
                .remote_endpoint()
                .address()
                .to_string();

        cell *addr = NULL;
        amx_GetAddr(amx, params[3], &addr);
        amx_SetString(addr, ip.c_str(), 0, 0, params[4]);
        return 1;
    } catch(...) { return 0; }
}

cell AMX_NATIVE_CALL WSServerKick(AMX *amx, cell *params) {
    try {
        WebSocketServerManager::sharedWebSocketServerManager()
                .getServer(params[1])
                ->getClient(params[2])
                ->close(params[3], PAWN::CellToString(params[4]));
        return 1;
    }
    catch(...) { return 0; }
}

void UnloadWSServers() {
    try {
        WebSocketServerManager::sharedWebSocketServerManager()
                .destroyAll();
    } catch(...) { }
}
