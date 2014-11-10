#include "WebSocketServer.hpp"
#include "PAWN.hpp"

WebSocketServer::WebSocketServer(const std::string &connectName, const std::string& disconnectName, const std::string &messageName)
    : m_connectName(connectName), m_disconnectName(disconnectName), m_messageName(messageName)
{	
	m_server.set_access_channels(websocketpp::log::alevel::none);
	m_server.set_error_channels(websocketpp::log::elevel::none);

	m_server.init_asio();
	
    m_server.set_open_handler(boost::bind(&WebSocketServer::openHandler, this, _1));
    m_server.set_close_handler(boost::bind(&WebSocketServer::closeHandler, this, _1));
    m_server.set_message_handler(boost::bind(&WebSocketServer::messageHandler, this, _1, _2));
}

WebSocketServer::~WebSocketServer()
{
    stop_listen();
}

bool WebSocketServer::listen(const std::string& host, const std::string& port)
{
    if(isListen())
        return false;

    try
    {
        m_server.listen(host, port);
        m_server.start_accept();

        m_asioThread = boost::thread(boost::bind(&websocket_server::run, &m_server));

        m_isListen = true;
        return true;
    }

    catch(...)
    {
        return false;
    }
}

bool WebSocketServer::stop_listen()
{
    if(!isListen())
        return false;

    try
    {
        for_each([&](int, websocket_connection_ptr ptr)
        {
            try
            {
                ptr->close(1000, "");
            }
            catch(...)
            {
            }
        });

        std::error_code ec;
        m_server.stop_listening(ec);
        m_server.stop();

        if(m_asioThread.joinable())
            m_asioThread.join();

        m_isListen = false;
        return true;
    }
    catch(...)
    {
        return false;
    }
}

const bool WebSocketServer::isListen() const
{
    return m_isListen;
}

Optional<websocket_connection_ptr> WebSocketServer::client_at(int idx)
{
	try
	{
		return m_server.get_con_from_hdl(m_clients[idx]);
	}
	catch(...)
	{
		return nullptr;
	}
}

void WebSocketServer::for_each(boost::function<void (int, websocket_connection_ptr)> pred)
{
    for(auto& i : m_clients)
    {
        if(auto ptr = client_at(i.first))
            pred(i.first, *ptr);
    }
}

void WebSocketServer::openHandler(websocket_connection hdl)
{
    int client_idx = m_clients += hdl;
    int server_idx = index();
    std::string funcName = m_connectName;

    SynchronizationCall::instance() += [client_idx, server_idx, funcName]() {
		int funcIDX = 0;
        if(!amx_FindPublic(g_pAMX, funcName.c_str(), &funcIDX)) {
            amx_Push(g_pAMX, client_idx);
            amx_Push(g_pAMX, server_idx);
			amx_Exec(g_pAMX, NULL, funcIDX);
		}
	};
}

void WebSocketServer::closeHandler(websocket_connection hdl)
{
    int client_idx = -1;

	if(auto key = m_clients.index_of([&](websocket_connection i){
		return m_server.get_con_from_hdl(i) == m_server.get_con_from_hdl(hdl);
	})) {
        client_idx = *key;
        m_clients -= client_idx;
	} 

    int server_idx = index();
    std::string funcName = m_disconnectName;

    SynchronizationCall::instance() += [client_idx, server_idx, funcName]() {
        int funcIDX = 0;
        if(!amx_FindPublic(g_pAMX, funcName.c_str(), &funcIDX)) {
            amx_Push(g_pAMX, client_idx);
            amx_Push(g_pAMX, server_idx);
            amx_Exec(g_pAMX, NULL, funcIDX);
        }
    };
}

void WebSocketServer::messageHandler(websocket_connection hdl, websocket_message msg)
{
	try {
        int client_idx = -1;
		auto str = msg->get_payload();

		if(auto key = m_clients.index_of([&](websocket_connection i){
			return m_server.get_con_from_hdl(i) == m_server.get_con_from_hdl(hdl);
		})) {
            client_idx = *key;
		} 

        int server_idx = index();
        std::string funcName = m_messageName;

        SynchronizationCall::instance() += [str, client_idx, server_idx, funcName]() {
			int funcIDX = 0;
            if(!amx_FindPublic(g_pAMX, funcName.c_str(), &funcIDX)) {
				cell addr = 0;

				amx_PushString(g_pAMX, &addr, NULL, str.c_str(), NULL, NULL);
                amx_Push(g_pAMX, client_idx);
                amx_Push(g_pAMX, server_idx);
				amx_Exec(g_pAMX, NULL, funcIDX);

				amx_Release(g_pAMX, addr);
			}
		};
	} catch(...) { }
}
