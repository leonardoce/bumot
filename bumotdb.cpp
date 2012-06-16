#include "bumotdb.hpp"

BuMotDb& CurrentDatabase()
{
  static BuMotDb db;
  return db;
}
