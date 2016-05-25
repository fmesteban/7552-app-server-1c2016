#ifndef WEB_SERVER_DATABASE_DATABASE_H_
#define WEB_SERVER_DATABASE_DATABASE_H_

#include <cstdio>
#include <string>

#include "rocksdb/db.h"
#include "rocksdb/slice.h"
#include "rocksdb/options.h"
#include "log.h"

class Database {
private:
	std::string kDBPath;
	rocksdb::DB* db;
	rocksdb::Options options;
	rocksdb::Status s;
	void wrapKeys(std::string& resultKey,
			const std::string& keyFirstLevel,
			const std::string& keySecondLevel);
public:
	Database();
	void putKeyValue(const std::string& key, const std::string& value);
	void putTwoLvlKeyValue(
			const std::string& keyFirstLevel,
			const std::string& keySecondLevel,
			const std::string& value);
	bool getValue(const std::string& key, std::string& value);
	bool getTwoLvlValue(
			const std::string& keyFirstLevel,
			const std::string& keySecondLevel,
			std::string& value);
	void eraseKey(const std::string& key);
	~Database();
};

#endif
