#include "PAWN.hpp"
#include "WebSocketClientNatives.hpp"
#include "WebSocketServerNatives.hpp"
#include "SynchronizationCall.hpp"

extern void *pAMXFunctions;

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports() {
    return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES | SUPPORTS_PROCESS_TICK;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData) {
    pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
    return true;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload() {
    UnloadWSClients();
    UnloadWSServers();
}

AMX_NATIVE_INFO PluginNatives[] = {
    // WebSocketClient
    { "CreateWSClient", CreateWSClient },
    { "DestroyWSClient", DestroyWSClient },
    { "WSClientConnect", WSClientConnect },
    { "WSClientDisconnect", WSClientDisconnect },
    { "WSClientIsConnected", WSClientIsConnected },
    { "WSClientSend", WSClientSend },

    // WebSocketServer
    { "CreateWSServer", CreateWSServer },
    { "DestroyWSServer", DestroyWSServer },
    { "WSServerStartListen", WSServerStartListen },
    { "WSServerStopListen", WSServerStopListen },
    { "WSServerIsListen", WSServerIsListen },
    { "WSServerConnected", WSServerConnected },
    { "WSServerSend", WSServerSend },
    { "WSServerSentToAll", WSServerSentToAll },
    { "WSServerGetIP", WSServerGetIP },
    { "WSServerKick", WSServerKick},

    { 0, 0 }
};

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad( AMX *amx ) {
    PAWN::SetAMX(amx);
    return amx_Register(amx, PluginNatives, -1);
}

PLUGIN_EXPORT int PLUGIN_CALL AmxUnload( AMX *amx ) {
    return AMX_ERR_NONE;
}

PLUGIN_EXPORT void PLUGIN_CALL ProcessTick() {
    SynchronizationCall::sharedSynronizationCall().executeAllAndClear();
	return;
}
