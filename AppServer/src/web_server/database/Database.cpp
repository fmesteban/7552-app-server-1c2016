#include "Database.h"
#include <string>
#include <iostream>

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
	Log::instance()->append("DB openes correctly.", Log::INFO);
}

// TODO: don't use assert, throw exceptions instead
void Database::putKeyValue(const std::string& key, const std::string& value){
	s = db->Put(rocksdb::WriteOptions(), key, value);
	std::cerr << s.ToString() << std::endl;
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
	std::cerr << s.ToString();
	//assert(s.ok());
	if (s.IsNotFound())
		Log::instance()->append("Key not found: " + key + " in DB.", Log::ERROR);
	else
		Log::instance()->append("Key found: " + key + ", value: " + value +" in DB.", Log::INFO);
	return !s.IsNotFound();
}

void Database::eraseKey(const std::string& key){
	s = db->Delete(rocksdb::WriteOptions(), key);
	//assert(s.ok());
	if (s.ok())
		Log::instance()->append("Deleted key: " + key + " from DB.", Log::INFO);
	else
		Log::instance()->append("Key not deleted: " + key + " in DB.", Log::ERROR);
}

void Database::wrapKeys(std::string& resultKey,
			const std::string& keyFirstLevel,
			const std::string& keySecondLevel){
	resultKey = keyFirstLevel + "&" + keySecondLevel;
}

Database::~Database(){
	Log::instance()->append("Closing DB.", Log::INFO);
	delete db;
}
