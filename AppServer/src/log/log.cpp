#include "log.h"

Log *Log::log = 0;

/** The logger is a Singleton. This function gets the static instance.
 *
 *	\return The instance of the logger.
 */
Log* Log::instance() {
	if (!log){
		log = new Log;
		log->printNewLogger();
	}
	return log;
}


/** Releases the static instance of logger.
 *
 */
void Log::closeLog() {
	if(log)
		delete log;

	log = nullptr;
}


/** Appends a message in the log file.
 *
 * 	\param msg Is the message to append in the log file.
 * 	\param logType Is the log level of the message.
 */
void Log::append(std::string msg, LOG_TYPE logType) {

	std::string fileName(LOG_FILE);
	std::ofstream out(fileName, std::ios_base::app);

	if(logType >= loggerLevel)
		out << timestamp() + logTypeToString(logType) + msg + "\n";

	out.close();
}


/** Gets a timestamp with the format used by logger.
 *
 * 	\return The string object.
 */
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


/** Prints a initial message in log file.
 *
 */
void Log::printNewLogger(){
	std::string fileName(LOG_FILE);
	std::ofstream out(fileName, std::ios_base::app);

	out << "*&------------------------------------------------------------------------------------------------------*&\n";
	out << "*&                               Inicio de Servidor "+ timestamp() + "                            *&\n";
	out << "*&------------------------------------------------------------------------------------------------------*&\n";
	out.close();
}
