#include "PAWN.hpp"
#include "WebSocketClient.hpp"

#include <boost/bind.hpp>

WebSocketClient::WebSocketClient(const std::string& connectName, const std::string& failName, const std::string& disconnectName, const std::string& messageName)
    : m_functionConnectName(connectName), m_functionFailName(failName), m_functionDisconnectName(disconnectName), m_functionMessageName(messageName)
{
    m_client.set_access_channels(websocketpp::log::alevel::none);
    m_client.set_error_channels(websocketpp::log::alevel::none);

    m_client.set_open_handler(boost::bind(&WebSocketClient::openHandler, this));
    m_client.set_fail_handler(boost::bind(&WebSocketClient::failHandler, this));
    m_client.set_close_handler(boost::bind(&WebSocketClient::closeHandler, this));
    m_client.set_message_handler(boost::bind(&WebSocketClient::messageHandler, this, _2));

    m_client.init_asio();
}

WebSocketClient::~WebSocketClient()
{
    disconnect();
}

bool WebSocketClient::connect(const std::string &ip)
{
    if(isConnected())
        return false;

    try
    {
        websocketpp::lib::error_code ec;
        auto ptr = m_client.get_connection(ip, ec);

        m_connectionPtr = ptr->get_handle();
        m_client.connect(ptr);

        m_asioThread = boost::thread(boost::bind(&websocket_client::run, &m_client));
        return true;
    }
    catch(...)
    {
        return false;
    }
}

bool WebSocketClient::disconnect()
{
    if(!isConnected())
        return false;

    try
    {
        m_client.stop();
        if(m_asioThread.joinable())
            m_asioThread.join();

        m_connected = false;
        return m_client.stopped();
    }
    catch(...)
    {
        return false;
    }
}

bool WebSocketClient::isConnected() const
{
    return m_connected;
}

bool WebSocketClient::send(const std::string &text)
{
    if(!isConnected())
        return false;

    try
    {
        if(m_client.get_con_from_hdl(m_connectionPtr)->send(text, websocketpp::frame::opcode::text))
            return false;

        return true;
    }
    catch(...)
    {
        return false;
    }
}

void WebSocketClient::openHandler()
{
    m_connected = true;

    int idx = index(); std::string func = m_functionConnectName;
    SynchronizationCall::instance() += [idx, func]() {
        int funcIDX = 0;
        if(!amx_FindPublic(g_pAMX, func.c_str(), &funcIDX))
        {
            amx_Push(g_pAMX, idx);
            amx_Exec(g_pAMX, NULL, funcIDX);
        }
    };
}

void WebSocketClient::failHandler()
{
    m_connected = false;

    int idx = index(); std::string func = m_functionFailName;

    SynchronizationCall::instance() += [idx, func]() {
        int funcIDX = 0;
        if(!amx_FindPublic(g_pAMX, func.c_str(), &funcIDX))
        {
            amx_Push(g_pAMX, idx);
            amx_Exec(g_pAMX, NULL, funcIDX);
        }
    };
}

void WebSocketClient::closeHandler()
{
    m_connected = false;

    int idx = index(); std::string func = m_functionDisconnectName;
    SynchronizationCall::instance() += [idx, func]() {
        int funcIDX = 0;
        if(!amx_FindPublic(g_pAMX, func.c_str(), &funcIDX))
        {
            amx_Push(g_pAMX, idx);
            amx_Exec(g_pAMX, NULL, funcIDX);
        }
    };
}

void WebSocketClient::messageHandler(websocket_message msg)
{
    std::string data;
    try
    {
        data = msg->get_payload();

        int idx = index(); std::string func = m_functionMessageName;
        SynchronizationCall::instance() += [idx, func, data]()
        {
            int funcIDX = 0;
            if(!amx_FindPublic(g_pAMX, func.c_str(), &funcIDX))
            {
                cell addr = 0;

                amx_PushString(g_pAMX, &addr, NULL, data.c_str(), NULL, NULL);
                amx_Push(g_pAMX, idx);
                amx_Exec(g_pAMX, NULL, funcIDX);
                amx_Release(g_pAMX, addr);
            }
        };
    }
    catch(...)
    {

    }
}

