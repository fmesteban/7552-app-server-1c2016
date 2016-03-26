#include "WebServer.h"
#include "rocksdb/c.h"

int main(void) {
	WebServer server;
	server.start();
	return 0;
}

/*
#include <cstdio>
#include <string>

#include "rocksdb/db.h"
#include "rocksdb/slice.h"
#include "rocksdb/options.h"

//using namespace rocksdb;

std::string kDBPath = "/tmp/rocksdb_simple_example";

int main() {
  rocksdb::DB* db;
  rocksdb::Options options;
  // Optimize RocksDB. This is the easiest way to get RocksDB to perform well
  options.IncreaseParallelism();
  options.OptimizeLevelStyleCompaction();
  // create the DB if it's not already present
  options.create_if_missing = true;

  // open DB
  rocksdb::Status s = rocksdb::DB::Open(options, kDBPath, &db);
  assert(s.ok());

  // Put key-value
  s = db->Put(rocksdb::WriteOptions(), "key1", "value");
  assert(s.ok());
  std::string value;
  // get value
  s = db->Get(rocksdb::ReadOptions(), "key1", &value);
  assert(s.ok());
  assert(value == "value");

  // atomically apply a set of updates
  {
	rocksdb::WriteBatch batch;
    batch.Delete("key1");
    batch.Put("key2", value);
    s = db->Write(rocksdb::WriteOptions(), &batch);
  }

  s = db->Get(rocksdb::ReadOptions(), "key1", &value);
  assert(s.IsNotFound());

  db->Get(rocksdb::ReadOptions(), "key2", &value);
  assert(value == "value");

  delete db;

  return 0;
}
*/
