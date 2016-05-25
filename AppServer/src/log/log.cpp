#include "log.h"

Log *Log::log = 0;

Log* Log::instance() {
	if (!log){
		log = new Log;
		log->printNewLogger();
	}

	return log;
}

void Log::closeLog() {
	if(log)
		delete log;

	log = nullptr;
}

void Log::append(std::string msg, LOG_TYPE logType) {

	std::string fileName(LOG_FILE);
	std::ofstream out(fileName, std::ios_base::app);

	if(logType >= loggerLevel)
		out << timestamp() + logTypeToString(logType) + msg + "\n";

	out.close();
}

std::string Log::timestamp() {
	time_t now = time(0);
	std::string dt = ctime(&now);
	return dt.substr(0, dt.size() - 1);
}

/**	-If loggerLevel = INFO all messages are logged
 *	-If loggerLevel = WARNING only WARNING and ERROR type messages are logged.
 *	-If loggerLevel = ERROR only ERROR type messages are logged.
 */
std::string Log::logTypeToString(LOG_TYPE logType){

	std::string strLogType;

	switch (logType) {
		case INFO: strLogType = ": INFO "; break;
		case WARNING: strLogType = ": WARNING "; break;
		case ERROR: strLogType = ": ERROR "; break;
	}

	return strLogType;
}

void Log::printNewLogger(){

	std::string fileName(LOG_FILE);
	std::ofstream out(fileName, std::ios_base::app);

	out << "*&------------------------------------------------------------------------------------------------------*&\n";
	out << "*&                               Inicio de Servidor "+ timestamp() + "                            *&\n";
	out << "*&------------------------------------------------------------------------------------------------------*&\n";
	out.close();

}