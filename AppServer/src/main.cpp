#include "WebServer.h"

int main(int argc, char *argv[]) {
	/* just start the webserver's thread */
	WebServer server;
	server.start();
	/* and wait for some input to end */
	getchar();
	server.stop();
	/* wait for server thread */
	server.join();
	return 0;
}
