#ifndef WEBSOCKETCLIENT_HPP
#define WEBSOCKETCLIENT_HPP

#include "WebSocket.hpp"
#include "BasicManagerDelegate.hpp"
#include "Utils.hpp"

#include <boost/thread.hpp>
#include <string>

class WebSocketClient : public BasicManagerDelegate
{
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
    ~WebSocketClient();

    DISABLE_CPY_MOV_CTOR(WebSocketClient)

    bool connect(const std::string& ip);
    bool disconnect();
    bool isConnected() const;

    bool send(const std::string& text);
protected:
    virtual void openHandler();
    virtual void failHandler();
    virtual void closeHandler();
    virtual void messageHandler(websocket_message msg);
};

#endif
