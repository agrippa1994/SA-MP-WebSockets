#ifndef WEBSOCKET_HPP
#define WEBSOCKET_HPP

#define _WEBSOCKETPP_CPP11_THREAD_
#define _WEBSOCKETPP_CPP11_FUNCTIONAL_
#define _WEBSOCKETPP_CPP11_SYSTEM_ERROR_
#define _WEBSOCKETPP_CPP11_RANDOM_DEVICE_
#define _WEBSOCKETPP_CPP11_MEMORY_

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/client.hpp>
#include <websocketpp/server.hpp>

typedef websocketpp::connection_hdl websocket_connection;

typedef websocketpp::client<websocketpp::config::asio> websocket_client;
typedef websocket_client::message_ptr websocket_message;

typedef websocketpp::server<websocketpp::config::asio> websocket_server;
typedef websocket_server::message_ptr websocket_message;
typedef websocket_server::connection_ptr websocket_connection_ptr;

#endif
