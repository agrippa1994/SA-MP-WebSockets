#include <a_samp>
#include <websockets>

new ws_server:mainWS;

// Callbacks
forward onWSClientConnect(ws_server:ws, ws_connection:con);
forward onWSClientDisconnect(ws_server:ws, ws_connection:con);
forward onWSClientMessage(ws_server:ws, ws_connection:con, message[]);

public onWSClientConnect(ws_server:ws, ws_connection:con)
{
	new ip[32];
	WSServerGetIP(ws, con, ip, sizeof(ip));
	printf("Incomming connection from %s", ip);
}

public onWSClientDisconnect(ws_server:ws, ws_connection:con)
{
	printf("Connection closed");
}

public onWSClientMessage(ws_server:ws, ws_connection:con, message[])
{
    printf("A connection sent a message: %s", message);
    
    if(!strcmp(message, "kickme", true))
        WSServerKick(ws, con, 1000, "Bye ;)");
        
	if(!strcmp(message, "stopserver", true))
	    WSServerStopListen(ws);
}


main()
{
	// Create a server. The three parameters indicate the names of the callbacks
    mainWS = CreateWSServer("onWSClientConnect", "onWSClientDisconnect", "onWSClientMessage");
	printf("ID: %d", mainWS);

	// Connect to the remote endpoint
 	printf("Listen ? %d", WSServerStartListen(mainWS, "0.0.0.0", "8080"));
}
