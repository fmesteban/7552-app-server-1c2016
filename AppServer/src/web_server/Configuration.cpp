#include "Configuration.h"
#include <string>

Configuration::Configuration(const std::string &fileName) :
	test(fileName, std::ifstream::binary){
	bool ok = Json::parseFromStream(builder, test, &root, &errs);
	if ( !ok ){
		Log::instance()->append(
				"Shared URL was not set. Errors on parsing " + fileName + ":" + errs,
				Log::ERROR);
	}

	std::string encoding = root.get("encoding", "UTF-8").asString();
	std::cout << encoding << std::endl;

	urlShared = root["url_shared"].asString();

	Log::instance()->append(
			"Shared URL was correctly set.",
			Log::INFO);
}

Configuration &Configuration::getInstance(){
	static Configuration instance("config.json");
	return instance;
}
