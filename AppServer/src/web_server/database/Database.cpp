#include "Database.h"
#include <string>

Database::Database() :
kDBPath("./debug_db") {
	/** Optimize RocksDB. This is the easiest way to get RocksDB to perform well */
	options.IncreaseParallelism();
	options.OptimizeLevelStyleCompaction();
	/** create the DB if it's not already present */
	options.create_if_missing = true;
	/** open DB */
	s = rocksdb::DB::Open(options, kDBPath, &db);
	assert(s.ok());
}

// TODO: don't use assert, throw exceptions instead
void Database::putKeyValue(const std::string& key, const std::string& value){
	s = db->Put(rocksdb::WriteOptions(), key, value);
	assert(s.ok());
}

void Database::putTwoLvlKeyValue(
		const std::string& keyFirstLevel,
		const std::string& keySecondLevel,
		const std::string& value){
	std::string resultKey;
	wrapKeys(resultKey, keyFirstLevel, keySecondLevel);
	putKeyValue(resultKey, value);
}

bool Database::getTwoLvlValue(
		const std::string& keyFirstLevel,
		const std::string& keySecondLevel,
		std::string& value){
	std::string resultKey;
	wrapKeys(resultKey, keyFirstLevel, keySecondLevel);
	return getValue(resultKey, value);
}

bool Database::getValue(const std::string& key, std::string& value){
	s = db->Get(rocksdb::ReadOptions(), key, &value);
	assert(s.ok());
	return !s.IsNotFound();
}

void Database::eraseKey(const std::string& key){
	s = db->Delete(rocksdb::WriteOptions(), key);
	assert(s.ok());
}

void Database::wrapKeys(std::string& resultKey,
			const std::string& keyFirstLevel,
			const std::string& keySecondLevel){
	resultKey = keyFirstLevel + "&" + keySecondLevel;
}

Database::~Database(){
	delete db;
}
