/** Include area. */
#include "Database.h"
#include <string>
#include <iostream>

/*------------------------------------------------------------------------
 * 	Member Functions Implementations
 * ---------------------------------------------------------------------*/


/** DB Constructor. Opens the database file, or creates it if doesn't exist.
 *
 */
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


/** Adds a key-value pair in the database.
 *
 *	\param key Is the key of the pair.
 *	\param value Is the value of the pair.
 */
void Database::putKeyValue(const std::string& key, const std::string& value){
	s = db->Put(rocksdb::WriteOptions(), key, value);
	assert(s.ok());
}


/**	Gets a value of the database, for the corresponding key.
 *
 *	\param key Is the key to want in the db.
 *	\param value Is a refference what the function will fill with the wanted value.
 *
 *	\return True if the key was found, False otherwise.
 */
bool Database::getValue(const std::string& key, std::string& value){
	s = db->Get(rocksdb::ReadOptions(), key, &value);
	if (s.IsNotFound())
		Log::instance()->append("Key not found: " + key + " in DB.", Log::ERROR);
	else
		Log::instance()->append("Key found: " + key +
				", value: " + value +" in DB.", Log::INFO);
	return !s.IsNotFound();
}


/**	Releases the memory used by DB and destroys the logger.
 *
 */
Database::~Database(){
	Log::instance()->append("Closing DB.", Log::INFO);
	delete db;
}
