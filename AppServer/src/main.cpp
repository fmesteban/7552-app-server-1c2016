#include "WebServer.h"
#include <iostream>
#include "log.h"


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
	// Set the log level	
	Log::instance()->loggerLevel = Log::INFO;
	/* just start the webserver's thread */
	WebServer server(argv[portPosition]);
	server.start();
	/* and wait for some input to end */
	getchar();
	server.stop();
	Log::instance()->append("Shutting down server.", Log::INFO);
	/* wait for server's thread */
	server.join();
	return 0;
}
