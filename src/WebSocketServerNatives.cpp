#include "WebSocketServerNatives.hpp"
#include "WebSocketServerManager.hpp"

#define GET_SERVER(server, idx) \
    auto server = g_wsServerManager[params[idx]]; \
    if(!server) return 0; \
    if(!*server) return 0; \

WebSocketServerManager g_wsServerManager;

cell AMX_NATIVE_CALL CreateWSServer(AMX *amx, cell *params)
{
    auto connectName = string_from_cell(amx, params[1]);
    auto disconnectName = string_from_cell(amx, params[2]);
    auto messageName = string_from_cell(amx, params[3]);

    if(!connectName || !disconnectName || !messageName)
        return 0;

    return g_wsServerManager.create(*connectName, *disconnectName, *messageName);
}

cell AMX_NATIVE_CALL DestroyWSServer(AMX *amx, cell *params)
{
    return g_wsServerManager.destroy(params[1]);
}

cell AMX_NATIVE_CALL WSServerStartListen(AMX *amx, cell *params)
{
    GET_SERVER(server, 1)

    auto host = string_from_cell(amx, params[2]);
    auto port = string_from_cell(amx, params[3]);

    if(!host || !port)
        return 0;

    return (*server)->listen(*host, *port);
}

cell AMX_NATIVE_CALL WSServerStopListen(AMX *amx, cell *params)
{
    GET_SERVER(server, 1)

    return (*server)->stop_listen();
}

cell AMX_NATIVE_CALL WSServerIsListen(AMX *amx, cell *params)
{
    GET_SERVER(server, 1)

    return (*server)->isListen();
}

cell AMX_NATIVE_CALL WSServerConnected(AMX *amx, cell *params)
{
    GET_SERVER(server, 1)

    return (cell)(bool)(*server)->client_at(params[2]);
}

cell AMX_NATIVE_CALL WSServerSend(AMX *amx, cell *params)
{
    if(!WSServerConnected(amx, params))
        return 0;

    try
    {
        if(auto client = (*g_wsServerManager[params[1]])->client_at(params[2]))
        {
            auto text = string_from_cell(amx, params[3]);
            if(text)
            {
                (*client)->send(*text);
                return 1;
            }
        }
    }
    catch(...)
    {
    }

    return 0;
}

cell AMX_NATIVE_CALL WSServerSentToAll(AMX *amx, cell *params)
{
    GET_SERVER(server, 1)

    auto text = string_from_cell(amx, params[2]);
    if(!text)
        return 0;

    int clientsSent = 0;
    (*server)->for_each([&](int, websocket_connection_ptr ptr)
    {
        ptr->send(*text);
        clientsSent++;
    });

    return clientsSent;
}

cell AMX_NATIVE_CALL WSServerGetIP(AMX *amx, cell *params)
{
    if(!WSServerConnected(amx, params))
        return 0;

    try
    {
        if(auto client = (*g_wsServerManager[params[1]])->client_at(params[2]))
        {
            auto ip = (*client)->get_socket().remote_endpoint().address().to_string();

            cell *addr = NULL;
            amx_GetAddr(amx, params[3], &addr);
            amx_SetString(addr, ip.c_str(), 0, 0, params[4]);
            return 1;
        }
    }
    catch(...)
    {
    }

    return 0;
}

cell AMX_NATIVE_CALL WSServerKick(AMX *amx, cell *params)
{
    if(!WSServerConnected(amx, params))
        return 0;

    try
    {
        if(auto client = (*g_wsServerManager[params[1]])->client_at(params[2]))
        {
            auto reason = string_from_cell(amx, params[4]);
            (*client)->close(params[3], reason ? *reason : "");
            return 1;
        }
    }
    catch(...)
    {
    }

    return 0;
}

void UnloadWSServers()
{
    g_wsServerManager.clear();
}
