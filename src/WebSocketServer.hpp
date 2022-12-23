#pragma once
#include "WebSocket.hpp"
#include "IndexedVector.hpp"
#include "Constructor.hpp"
#include "PAWN.hpp"

#include <asio/thread.hpp>
#include <functional>
#include <memory>

class WebSocketServer {
public:
    DISABLE_CPY_MOV_CTOR(WebSocketServer)
    WebSocketServer(AMX *amx,
		            const std::string& connectName,
                    const std::string& disconnectName,
                    const std::string& messageName);
    ~WebSocketServer();

    bool listen(const std::string &host, const std::string &port);
    bool stopListen();
    bool isListening() const;

    int getID() const;
    void setID(int id);

    WebsocketConnectionPtr getClient(int id);

    IndexedVector<WebsocketConnection> getClients() const;

    int getClientIDByConnection(WebsocketConnection connection);

private:
    WebsocketServer m_server;
    IndexedVector<WebsocketConnection> m_clients;
    std::unique_ptr<asio::thread> m_asioThread;

    int m_id = -1;
	AMX * const m_amx;
    const std::string m_connectName;
    const std::string m_disconnectName;
    const std::string m_messageName;

    bool m_isListen = false;
};
