#include <iostream>
#include "bumotdb.hpp"
#include <boost/format.hpp>
#include <boost/foreach.hpp>

const int Max_Result_Size = 100;

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

inline std::string createLikeClause(const std::string &txt, bool extended) {
  if (!extended) {
    return txt + "%";
  } else {
    return "%" + txt + "%";
  }
}

std::vector<BuMotDb::BuMotRecord> BuMotDb::Find(const BuMotFindCriteria &criteria) {
  std::vector<BuMotDb::BuMotRecord> result;

  std::string sql = "SELECT rap, mot FROM dict WHERE 0=1";

  if (criteria.get_search_in_rap()) {
    sql += " OR finrap LIKE " + stosingle(createLikeClause(criteria.get_search_string(), criteria.get_extended_search()));
  }
 
  if (criteria.get_search_in_eng()) {
    sql += " OR mot LIKE " + stosingle(createLikeClause(criteria.get_search_string(), criteria.get_extended_search()));
  }
  
  try {
    std::tr1::shared_ptr<db_recordset> rs = 
      dbConnection->sql_retrieve(sql);

    while(rs->next()) {
      BuMotDb::BuMotRecord record(rs->get_string_field(0), 
				  rs->get_string_field(1));
      result.push_back(record);

      if (result.size()>Max_Result_Size) break;
    }
  } catch(const std::exception &exc) {
    std::cerr << exc.what() << std::endl;
  }

  return result;
}

BuMotDb& CurrentDatabase()
{
  static BuMotDb db;
  return db;
}
