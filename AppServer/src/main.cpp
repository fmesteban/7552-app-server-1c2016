#include "WebServer.h"
#include <iostream>


/* command line format */
typedef enum{
	/* ./AppServer */
	processName,

	/* eventually, add ordered parameter names here */
	portPosition,

	/* last enum value */
	commandLineRightSize
}ParameterPositions;


static bool verifyParameters(int argc, char *argv[]){
	return (argc == commandLineRightSize);
}


int main(int argc, char *argv[]) {
	if (!verifyParameters(argc, argv)){
		std::cerr << "usage: " << argv[processName] << " port" << std::endl;
		return 1;
	}
	/* just start the webserver's thread */
	WebServer server(argv[portPosition]);
	server.start();
	/* and wait for some input to end */
	getchar();
	server.stop();
	/* wait for server's thread */
	server.join();
	return 0;
}
