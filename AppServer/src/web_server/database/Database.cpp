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
	assert(s.ok());
}

bool Database::getValue(const std::string& key, std::string& value){
	s = db->Get(rocksdb::ReadOptions(), key, &value);
	if (s.IsNotFound())
		Log::instance()->append("Key not found: " + key + " in DB.", Log::ERROR);
	else
		Log::instance()->append("Key found: " + key +
				", value: " + value +" in DB.", Log::INFO);
	return !s.IsNotFound();
}

Database::~Database(){
	Log::instance()->append("Closing DB.", Log::INFO);
	delete db;
}
