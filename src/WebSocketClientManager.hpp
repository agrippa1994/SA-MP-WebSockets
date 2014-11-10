#ifndef WEBSOCKETCLIENTMANAGER_HPP
#define WEBSOCKETCLIENTMANAGER_HPP
#include "WebSocketClient.hpp"
#include "IndexedVector.hpp"

#include <boost/optional.hpp>
#include <memory>

class WebSocketClientManager
{
    typedef std::shared_ptr<WebSocketClient> WebSocketClientPtr;

    IndexedVector<WebSocketClientPtr> m_clients;

public:
    int createWebSocket(const std::string& connectName, const std::string& failName, const std::string& disconnectName, const std::string& messageName);
    bool destroyWebSocket(int index);

    void clear();

    boost::optional<WebSocketClientPtr> operator[](int index);
};

#endif
