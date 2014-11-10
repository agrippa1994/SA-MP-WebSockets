#include "WebSocketClientNatives.hpp"
#include "WebSocketClientManager.hpp"

WebSocketClientManager g_wsClientManager;

#define GET_CLIENT(client, idx) \
    auto client = g_wsClientManager[params[idx]]; \
    if(!client) return 0; \
    if(!*client) return 0; \

cell AMX_NATIVE_CALL CreateWSClient(AMX *amx, cell *params)
{
    auto connectName = string_from_cell(amx, params[1]);
    auto failName = string_from_cell(amx, params[2]);
    auto disconnectName = string_from_cell(amx, params[3]);
    auto messageName = string_from_cell(amx, params[4]);

    if(!connectName || !failName || !disconnectName || !messageName)
        return -1;

    return g_wsClientManager.create(*connectName, *failName, *disconnectName, *messageName);
}

cell AMX_NATIVE_CALL DestroyWSClient(AMX *amx, cell *params)
{
    return g_wsClientManager.destroy(params[1]);
}

cell AMX_NATIVE_CALL WSClientConnect(AMX *amx, cell *params)
{
    GET_CLIENT(client, 1)

    auto ip = string_from_cell(amx, params[2]);
    if(!ip)
        return 0;

    return (*client)->connect(*ip);
}

cell AMX_NATIVE_CALL WSClientDisconnect(AMX *amx, cell *params)
{
    GET_CLIENT(client, 1)

    return (*client)->disconnect();
}

cell AMX_NATIVE_CALL WSClientIsConnected(AMX *amx, cell *params)
{
    GET_CLIENT(client, 1)

    return (*client)->isConnected();
}

cell AMX_NATIVE_CALL WSClientSend(AMX *amx, cell *params)
{
    GET_CLIENT(client, 1)

    if(auto text = string_from_cell(amx, params[2]))
        return (*client)->send(*text);

    return 0;
}

void UnloadWSClients()
{
    g_wsClientManager.clear();
}
