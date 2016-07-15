#pragma once
#include "WebSocketServer.hpp"
#include "IndexedVector.hpp"
#include <string>
#include <memory>

class WebSocketServerManager {
    typedef std::shared_ptr<WebSocketServer> WebSocketServerPointer;

public:
    static WebSocketServerManager& sharedWebSocketServerManager();

    int create(const std::string& connectName, const std::string& disconnectName, const std::string& messageName);
    bool destroy(int id);
    void destroyAll();

    WebSocketServerPointer getServer(int id);

    const IndexedVector<WebSocketServerPointer>& getServers() const;

private:
    IndexedVector<WebSocketServerPointer> m_servers;

    explicit WebSocketServerManager();
};
