#ifndef WEB_SERVER_CONFIGURATION_H_
#define WEB_SERVER_CONFIGURATION_H_

/** Include area. */
#include "json/json.h"
#include <iostream>
#include <fstream>
#include <string>
#include "log.h"


class Configuration {
private:
    Json::Value root;
    Json::CharReaderBuilder builder;
    std::ifstream test;
    std::string errs;
    std::string encoding;
	explicit Configuration(const std::string &fileName);
	Configuration(Configuration const&);
	void operator=(Configuration const&);

public:
    std::string urlShared;
	static Configuration &getInstance();
};

#endif
