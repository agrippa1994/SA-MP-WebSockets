native ws_client:CreateWSClient(const connectName[], const failName[], const disconnectName[], const messageName[]);
native DestroyWSClient(ws_client:ws);

native WSClientConnect(ws_client:ws, const host[]);
native WSClientDisconnect(ws_client:ws);
native WSClientIsConnected(ws_client:ws);
native WSClientSend(ws_client:ws, const message[]);
