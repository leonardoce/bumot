#include "bumotdb.hpp"
#include <boost/format.hpp>
#include <boost/foreach.hpp>

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

std::string stosingle(const std::string &query) {
  std::string result;

  result += '\'';

  BOOST_FOREACH(char c, query) {
    if (c=='\'') {
      result += '\'';
      result += '\'';      
    } else {
      result += c;
    }
  }

  result += '\'';

  return result;
}

std::vector<BuMotDb::BuMotRecord> BuMotDb::Find(const std::string &findStr) {
  std::vector<BuMotDb::BuMotRecord> result;

  std::string sql = "SELECT rap, mot FROM dict WHERE rap " 
    "ILIKE %1% OR mot ILIKE %2%";
  
  std::string formattedSql = 
    str( boost::format(sql) 
	 % stosingle("%" + findStr + "%") 
	 % stosingle("%" + findStr + "%") );
  
  std::tr1::shared_ptr<db_recordset> rs = 
    dbConnection->sql_retrieve(sql);
  
  while(rs->next()) {
    BuMotDb::BuMotRecord record(rs->get_string_field(0), 
				rs->get_string_field(1));
    result.push_back(record);
  }

  return result;
}

BuMotDb& CurrentDatabase()
{
  static BuMotDb db;
  return db;
}
