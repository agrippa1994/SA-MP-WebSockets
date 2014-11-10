#include <a_samp>
#include <websocket_client>

forward onConnect(ws_client:ws);
forward onFail(ws_client:ws);
forward onDisconnect(ws_client:ws);
forward onMessage(ws_client:ws, message[]);

// Our variable which holds a handle to the websocket
new ws_client:mainWS;

// Will be called, if the connection has been successfully established
public onConnect(ws_client:ws)
{
	printf("Connection established");
	
	// Send any message to the server
	WSClientSend(ws, "hello");
}

// Will be called, if the connection attempt has been failed
public onFail(ws_client:ws)
{
	printf("Connection couldn't be constructed!");
}

// Will be called, if the server or the client closes the connection
public onDisconnect(ws_client:ws)
{
	printf("Connection closed");
}

// Will be called, if an incoming message has been received
public onMessage(ws_client:ws, message[])
{
	printf("Data received (%d): %s", strlen(message), message);
	
	// Create random string
	new buffer[512 + 1];
	for(new i = 0; i < sizeof(buffer) - 1; i++)
	    buffer[i] = 'a' + random('z'-'a');
	buffer[sizeof(buffer) - 1] = '\0';

	// Send the random string
	WSClientSend(ws, buffer);
}

main()
{
	// Create a client. The four parameters indicate the names of the callbacks
    mainWS = CreateWSClient("onConnect", "onFail", "onDisconnect", "onMessage");
	printf("ID: %d", mainWS);

	// Connect to the remote endpoint
 	new result = WSClientConnect(mainWS, "ws://echo.websocket.org/");
	printf("WSClientConnect: %d", result);
}
