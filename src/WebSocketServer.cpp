#include "WebSocketServer.hpp"
#include "SynchronizationCall.hpp"

WebSocketServer::WebSocketServer(AMX *amx,
                                 const std::string &connectName,
                                 const std::string& disconnectName,
                                 const std::string &messageName)
    : m_amx(amx),
      m_connectName(connectName),
      m_disconnectName(disconnectName),
      m_messageName(messageName) {

    // Disable logging
	m_server.set_access_channels(websocketpp::log::alevel::none);
	m_server.set_error_channels(websocketpp::log::elevel::none);

    // Initialize ASIO
	m_server.init_asio();
	
    // Set handlers
    m_server.set_open_handler([&](WebsocketConnection hdl) {
        int clientID = (m_clients += hdl); // Add client
        int serverID = getID();
		AMX *amx = m_amx;
        std::string callbackName = m_connectName;

        SynchronizationCall::sharedSynronizationCall() += [amx, clientID, serverID, callbackName]() {
            int funcID = 0;
            if(!amx_FindPublic(amx, callbackName.c_str(), &funcID)) {
                amx_Push(amx, clientID);
                amx_Push(amx, serverID);
                amx_Exec(amx, NULL, funcID);
            }
        };
    });

    m_server.set_close_handler([&](WebsocketConnection hdl) {
        int clientID = -1;
        try {
            clientID = getClientIDByConnection(hdl);
            m_clients -= clientID; // Remove client
        } catch(...) { }

        int serverID = getID();
		AMX *amx = m_amx;
        std::string callbackName = m_disconnectName;

        SynchronizationCall::sharedSynronizationCall() += [amx, clientID, serverID, callbackName]() {
            int funcID = 0;
            if(!amx_FindPublic(amx, callbackName.c_str(), &funcID)) {
                amx_Push(amx, clientID);
                amx_Push(amx, serverID);
                amx_Exec(amx, NULL, funcID);
            }
        };
    });

    m_server.set_message_handler([&](WebsocketConnection hdl, WebsocketMessage msg) {
        try {
            int clientID = -1;
            auto str = msg->get_payload();

            try {
                clientID = getClientIDByConnection(hdl);
            } catch(...) { }

            int serverID = getID();
			AMX *amx = m_amx;
            std::string callbackName = m_messageName;

            SynchronizationCall::sharedSynronizationCall() += [str, clientID, serverID, amx, callbackName]() {
                int funcID = 0;
                if(!amx_FindPublic(amx, callbackName.c_str(), &funcID)) {
                    cell addr = 0;

                    amx_PushString(amx, &addr, NULL, str.c_str(), NULL, NULL);
                    amx_Push(amx, clientID);
                    amx_Push(amx, serverID);
                    amx_Exec(amx, NULL, funcID);
                    amx_Release(amx, addr);
                }
            };
        } catch(...) { }
    });
}

WebSocketServer::~WebSocketServer() {
    stopListen();
}

bool WebSocketServer::listen(const std::string& host, const std::string& port) {
    if(isListening())
        return false;

    try {
        m_server.listen(host, port);
        m_server.start_accept();

        m_asioThread = std::make_unique<asio::thread>(std::bind(&WebsocketServer::run, &m_server));

        m_isListen = true;
        return true;
    } catch(...) { return false; }
}

bool WebSocketServer::stopListen() {
    if(!isListening())
        return false;

    try {
        // Close all connections
        for(auto& client : m_clients) {
            try {
                getClient(client.first)->close(1000, "");
            } catch(...) { }
        }

        // Clear clients
        m_clients.clear();

        std::error_code ec;
        m_server.stop_listening(ec);
        m_server.stop();

        m_asioThread->join();

        m_isListen = false;
        return true;
    }
    catch(...) { return false; }
}

bool WebSocketServer::isListening() const {
    return m_isListen;
}

int WebSocketServer::getID() const {
    return m_id;
}

void WebSocketServer::setID(int id) {
    m_id = id;
}

WebsocketConnectionPtr WebSocketServer::getClient(int id) {
    websocketpp::connection_hdl hdl = m_clients.at(id);
    return m_server.get_con_from_hdl(hdl);
}

IndexedVector<WebsocketConnection> WebSocketServer::getClients() const {
    return m_clients;
}

int WebSocketServer::getClientIDByConnection(WebsocketConnection connection) {
    m_server.get_con_from_hdl(connection);

    for(const auto& i : m_clients) {
        try {
            if(m_server.get_con_from_hdl(i.second) == m_server.get_con_from_hdl(connection))
                return i.first;
        } catch(...) { }
    }

    return -1;
}
