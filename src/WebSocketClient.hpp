#pragma once
#include "WebSocket.hpp"
#include "Constructor.hpp"

#include <boost/thread.hpp>
#include <string>

class WebSocketClient
{
public:
    DISABLE_CPY_MOV_CTOR(WebSocketClient)
    WebSocketClient(const std::string& connectName,
                    const std::string& failName,
                    const std::string& disconnectName,
                    const std::string& messageName);
    ~WebSocketClient();

    bool connect(const std::string& ip);
    bool disconnect();
    bool isConnected() const;

    bool send(const std::string& text);

    int getID() const;
    void setID(int index);

private:
    int m_id = -1;
    bool m_connected = false;

    WebsocketClient m_client;
    websocketpp::connection_hdl m_connectionPtr;
    boost::thread m_asioThread;

    const std::string m_functionConnectName;
    const std::string m_functionFailName;
    const std::string m_functionDisconnectName;
    const std::string m_functionMessageName;
};
