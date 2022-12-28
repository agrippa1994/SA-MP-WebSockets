#include <a_samp>
#include <ws>

forward onConnect(ws_client:ws);
forward onFail(ws_client:ws);
forward onDisconnect(ws_client:ws);
forward onMessage(ws_client:ws, message[]);

// Will be called, if the connection has been successfully established
public onConnect(ws_client:ws)
{
	printf("Connection established");
	
	// Send any message to the server
	printf("%d SendData-Success: %d", ws, WSClientSend(ws, "hello"));
}

// Will be called, if the connection attempt has been failed
public onFail(ws_client:ws)
{
	printf("Connection of %d couldn't be constructed!", ws);
}

// Will be called, if the server or the client closes the connection
public onDisconnect(ws_client:ws)
{
	printf("Connection closed");
}

// Will be called, if an incoming message has been received
public onMessage(ws_client:ws, message[])
{
	printf("Client %d received data, length(%d): %s", ws, strlen(message), message);
	
	// Create random string
	new buffer[1024 + 1];
	for(new i = 0; i < sizeof(buffer) - 1; i++)
	    buffer[i] = 'a' + random('z'-'a');
	buffer[sizeof(buffer) - 1] = '\0';

	// Send the random string
	WSClientSend(ws, buffer);
}

main()
{
	// Create some clients
	// The four parameters of CreateWSClient indicate the names of the callbacks
	for(new i = 0; i < 5; i++) {
	    new ws_client:id = CreateWSClient("onConnect", "onFail", "onDisconnect", "onMessage");
	    printf("WSClientConnect(%d): %d", id, WSClientConnect(id, "ws://echo.websocket.org/"));
	}
}
