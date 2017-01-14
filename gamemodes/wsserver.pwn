#include <a_samp>
#include <websockets>
#include <sscanf2>

// WebSocket Definition
#define MAX_WS_CLIENTS 128

// CP API Definitions
#define cpcmd(%1,%2,%3) if (!strcmp((%3)[1], #%1, true, (%2)) && ((((%3)[(%2) + 1] == '\0') && (cpcmd_%1(ws, con, ""))) || (((%3)[(%2) + 1] == ' ') && (cpcmd_%1(ws, con, (%3)[(%2) + 2]))))) return 1
#define CPCMD: cpcmd_

// API Communication
#define CP_NOT_LOGGED_IN 		"CP_NOT_LOGGED_IN"
#define CP_LOGIN_SUCCESS 		"CP_LOGIN_SUCCESS"
#define CP_LOGIN_FAILED 		"CP_LOGIN_FAILED"
#define CP_INVALID_COMMAND 		"CP_INVALID_COMMAND"
#define CP_INVALID_ARGUMENTS 	"CP_INVALID_ARGUMENTS"
#define CP_INVALID_PLAYERID 	"CP_INVALID_PLAYERID"
#define CP_SUCCESS              "CP_SUCCESS"

// API Enumeration
enum pEnumCP
{
	pUsername[MAX_PLAYER_NAME],
	pLoggedIn
};

// API Globals
new CPInfo[MAX_WS_CLIENTS][pEnumCP];
new ws_server:mainWS;

// Callbacks
forward onWSClientConnect(ws_server:ws, ws_connection:con);
forward onWSClientDisconnect(ws_server:ws, ws_connection:con);
forward onWSClientMessage(ws_server:ws, ws_connection:con, message[]);

public onWSClientConnect(ws_server:ws, ws_connection:con)
{
	CPInfo[con][pLoggedIn] = false;
}

public onWSClientDisconnect(ws_server:ws, ws_connection:con)
{
    CPInfo[con][pLoggedIn] = false;
}

CPCMD:login(ws_server:ws, ws_connection:con, params[])
{
	new name[128];
	if(sscanf(params, "s[128]", name)) {
	    WSServerSend(ws, con, CP_INVALID_ARGUMENTS);
	    return;
	}

	new success = (strcmp(name, "uwe") == 0);
	if(success)
		WSServerSend(ws, con, CP_LOGIN_SUCCESS);
	else
	    WSServerSend(ws, con, CP_LOGIN_SUCCESS);

	CPInfo[con][pLoggedIn] = success;
}

CPCMD:kick(ws_server:ws, ws_connection:con, params[])
{
	if(!CPInfo[con][pLoggedIn]) {
 		WSServerSend(ws, con, CP_NOT_LOGGED_IN);
   		return;
	}

	new kickid, reason[256];
	if(sscanf(params, "us[256]", kickid, reason)) {
	    WSServerSend(ws, con, CP_INVALID_ARGUMENTS);
	    return;
	}
	
	WSServerSend(ws, con, reason);
	if(kickid == INVALID_PLAYER_ID) {
	    WSServerSend(ws, con, CP_INVALID_PLAYERID);
	    return;
	}

	WSServerSend(ws, con, CP_SUCCESS);
	Kick(kickid);
}

public onWSClientMessage(ws_server:ws, ws_connection:con, message[])
{
	cpcmd(login, 5, message);
	cpcmd(kick, 4, message);
	WSServerSend(ws, con, CP_INVALID_COMMAND);
	return 1;
}

main()
{
	// Create a server. The three parameters indicate the names of the callbacks
    mainWS = CreateWSServer("onWSClientConnect", "onWSClientDisconnect", "onWSClientMessage");
    
	printf("ID: %d", mainWS);

	// Connect to the remote endpoint
 	printf("Listen ? %d", WSServerStartListen(mainWS, "0.0.0.0", "7771"));
}
