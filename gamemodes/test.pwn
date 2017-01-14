#include <a_samp>
#include <websockets>

new gExitCode = 0;

#if !defined print
native print(const string[]);
#endif

#if !defined printf
native printf(const format[], {Float,_}:...);
#endif

stock exit_process(code)
{
	printf("EXIT_CODE: %d", code);
	SendRconCommand("exit");
}

stock verify(result, const text[])
{
	if(!result)
	    gExitCode++;

	if(result) {
		printf("PASS: %s", text);
	} else {
	    printf("FAIL: %s", text);
	}
}

stock compare(expected, actual, const text[])
{
	if(expected != actual)
		gExitCode++;

	if(expected == actual)
	    printf("PASS: %s", text);
	else
	    printf("FAIL: %s [%d != %d]", text, expected, actual);
}

stock test_is_listen()
{
	new ws_server:serverID = CreateWSServer("onWSClientConnect", "onWSClientDisconnect", "onWSClientMessage");
	verify(serverID >= 0, "Server created");
	
	new isListen = WSServerStartListen(serverID, "127.0.0.1", "7777");
	compare(1, isListen, "Server is listening");
	
	compare(1, WSServerIsListen(serverID), "Server is listening");
	compare(1, DestroyWSServer(serverID), "Server destroyed");
}
main()
{
	test_is_listen();
	exit_process(gExitCode);
}


