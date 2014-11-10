#ifndef WEBSOCKETSERVER_HPP
#define WEBSOCKETSERVER_HPP

#include "WebSocket.hpp"
#include "IndexedVector.hpp"
#include "BasicManagerDelegate.hpp"
#include "Utils.hpp"

#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>

class WebSocketServer : public BasicManagerDelegate
{
	websocket_server m_server;
	IndexedVector<websocket_connection> m_clients;
	boost::thread m_asioThread;

    const std::string m_connectName;
    const std::string m_disconnectName;
    const std::string m_messageName;

    bool m_isListen = false;

public:
    WebSocketServer(const std::string& connectName, const std::string& disconnectName, const std::string& messageName);
    ~WebSocketServer();

    bool listen(const std::string &host, const std::string &port);
    bool stop_listen();
    const bool isListen() const;

    DISABLE_CPY_MOV_CTOR(WebSocketServer)

    Optional<websocket_connection_ptr> client_at(int idx);
    void for_each(boost::function<void (int, websocket_connection_ptr)> pred);

private:
	void openHandler(websocket_connection hdl);
	void closeHandler(websocket_connection hdl);
	void messageHandler(websocket_connection hdl, websocket_message msg);
};

#endif
