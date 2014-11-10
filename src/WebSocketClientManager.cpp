#include "WebSocketClientManager.hpp"
#include "WebSocketClient.hpp"

int WebSocketClientManager::createWebSocket(const std::string& connectName, const std::string& failName, const std::string& disconnectName, const std::string& messageName)
{
    auto ptr = std::make_shared<WebSocketClient>(connectName, failName, disconnectName, messageName);

    int index = m_clients += ptr;
    ptr->setIndex(index);

    return index;
}

bool WebSocketClientManager::destroyWebSocket(int index)
{
    return m_clients -= index;
}

void WebSocketClientManager::clear()
{
    m_clients.clear();
}

boost::optional<WebSocketClientManager::WebSocketClientPtr> WebSocketClientManager::operator[](int index)
{
    try
    {
        return m_clients.at(index);
    }
    catch(...)
    {
        return nullptr;
    }
}
