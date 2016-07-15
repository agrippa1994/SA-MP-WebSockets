#include "WebSocketClientManager.hpp"


WebSocketClientManager &WebSocketClientManager::sharedWebSocketClientManager() {
    static WebSocketClientManager singleTon;
    return singleTon;
}

int WebSocketClientManager::create(const std::string &connectNameCallback,
                                   const std::string &failNameCallback,
                                   const std::string &disconnectNameCallabck,
                                   const std::string &messageNameCallback) {
    return m_clients += std::make_shared<WebSocketClient>(
                connectNameCallback,
                failNameCallback,
                disconnectNameCallabck,
                messageNameCallback);
}

bool WebSocketClientManager::destroy(int id) {
    return (m_clients -= id);
}

void WebSocketClientManager::destroyAll() {
    m_clients.clear();
}

WebSocketClientManager::WebSocketClientPointer WebSocketClientManager::getClient(int id) {
    return m_clients.at(id);
}

WebSocketClientManager::WebSocketClientManager() { }
