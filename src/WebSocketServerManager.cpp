#include "WebSocketServerManager.hpp"

WebSocketServerManager &WebSocketServerManager::sharedWebSocketServerManager() {
    static WebSocketServerManager singleTon;
    return singleTon;
}

int WebSocketServerManager::create(AMX *amx,
        const std::string &connectName,
        const std::string &disconnectName,
        const std::string &messageName) {

    return m_servers += std::make_shared<WebSocketServer>(amx,
                connectName,
                disconnectName,
                messageName);
}

bool WebSocketServerManager::destroy(int id) {
    return m_servers -= id;
}

void WebSocketServerManager::destroyAll() {
    m_servers.clear();
}

WebSocketServerManager::WebSocketServerPointer WebSocketServerManager::getServer(int id) {
    return m_servers.at(id);
}

const IndexedVector<WebSocketServerManager::WebSocketServerPointer>& WebSocketServerManager::getServers() const {
    return m_servers;
}

WebSocketServerManager::WebSocketServerManager() { }
