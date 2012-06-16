#include "bumotdb.hpp"

BuMotDb::BuMotDb() 
{
}

BuMotDb::~BuMotDb() throw ()
{
}

void BuMotDb::Init() {
  if(!dbConnection) {
    dbConnection.reset(new sqlite_connection("bumotdb.db"));
  }
}

BuMotDb& CurrentDatabase()
{
  static BuMotDb db;
  return db;
}
