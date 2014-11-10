#ifndef WEBSOCKETCLIENT_HPP
#define WEBSOCKETCLIENT_HPP
#include "WebSocket.hpp"

#include <boost/thread.hpp>
#include <string>

class WebSocketClient
{
    int m_index = -1;
    bool m_connected = false;

    websocket_client m_client;
    websocketpp::connection_hdl m_connectionPtr;
    boost::thread m_asioThread;

    const std::string m_functionConnectName;
    const std::string m_functionFailName;
    const std::string m_functionDisconnectName;
    const std::string m_functionMessageName;

public:
    WebSocketClient(const std::string& connectName, const std::string& failName, const std::string& disconnectName, const std::string& messageName);

    WebSocketClient(const WebSocketClient&) = delete;
    WebSocketClient(WebSocketClient&&) = delete;
    WebSocketClient& operator=(const WebSocketClient&) = delete;

    ~WebSocketClient();

    bool connect(const std::string& ip);
    bool disconnect();
    bool isConnected() const;

    const int index() const;
    void setIndex(int idx);

    bool send(const std::string& text);
protected:
    virtual void openHandler();
    virtual void failHandler();
    virtual void closeHandler();
    virtual void messageHandler(websocket_message msg);
};

#endif
