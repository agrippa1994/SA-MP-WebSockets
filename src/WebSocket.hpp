#pragma once
#define _WEBSOCKETPP_CPP11_THREAD_
#define _WEBSOCKETPP_CPP11_FUNCTIONAL_
#define _WEBSOCKETPP_CPP11_SYSTEM_ERROR_
#define _WEBSOCKETPP_CPP11_RANDOM_DEVICE_
#define _WEBSOCKETPP_CPP11_MEMORY_

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/client.hpp>
#include <websocketpp/server.hpp>

typedef websocketpp::connection_hdl WebsocketConnection;

typedef websocketpp::client<websocketpp::config::asio> WebsocketClient;
typedef WebsocketClient::message_ptr WebsocketMessage;

typedef websocketpp::server<websocketpp::config::asio> WebsocketServer;
typedef WebsocketServer::message_ptr WebsocketMessage;
typedef WebsocketServer::connection_ptr WebsocketConnectionPtr;
