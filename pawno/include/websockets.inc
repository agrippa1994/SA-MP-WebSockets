// WebSocketClient
// connectName: forward onConnect(ws_client:ws);
// failName: forward onFail(ws_client:ws);
// disconnectName: forward onDisconnect(ws_client:ws);
// messageName: forward onMessage(ws_client:ws, message[]);

native ws_client:CreateWSClient(const connectName[], const failName[], const disconnectName[], const messageName[]);
native DestroyWSClient(ws_client:ws);

native WSClientConnect(ws_client:ws, const host[]);
native WSClientDisconnect(ws_client:ws);
native WSClientIsConnected(ws_client:ws);
native WSClientSend(ws_client:ws, const message[]);



// WebSocketServer
// Callback-Prototypes
// connectName: forward onConnect(ws_server:ws, ws_connection:con);
// disconnectName: forward onDisconnect(ws_server:ws, ws_connection:con);
// messageName: forward onMessage(ws_server:ws, ws_connection:con, message[]);

native ws_server:CreateWSServer(const connectName[], const disconnectName[], const messageName[]);
native DestroyWSServer(ws_server:ws);

native WSServerStartListen(ws_server:ws, const host[], const service[]);
native WSServerStopListen(ws_server:ws);
native WSServerIsListen(ws_server:ws);
native WSServerConnected(ws_server:ws, ws_connection:con);
native WSServerSend(ws_server:ws, ws_connection:con, const message[]);
native WSServerSentToAll(ws_server:ws, const message[]);
native WSServerGetIP(ws_server:ws, ws_connection:con, ip[], max_size);
native WSServerKick(ws_server:ws, ws_connection:con, code, const reason[]);