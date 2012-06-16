#include "data_connection.hpp"

sqlite_connection::sqlite_connection(const std::string &nomeFile) : ppdb(NULL)
{
  if (sqlite3_open(nomeFile.c_str(), &ppdb) != SQLITE_OK) {
    throw sqlite_exception(str(boost::format(Sqlite_Error_Message) % nomeFile));
  }
}

sqlite_connection::~sqlite_connection() throw ()
{
  if (ppdb!=NULL) {
    sqlite3_close(ppdb);
  }
}

std::string sqlite_connection::sql_into(const std::string &sql)
{
  sqlite3_stmt *stmt;
  int status;

  status = sqlite3_prepare(ppdb, sql.c_str(), sql.size(), &stmt, NULL);
  if (status!=SQLITE_OK) {
    sqlite3_reset(stmt);
    throw new sqlite_exception(str(boost::format(Sqlite_Query_Error) % sql));
  }

  std::string result;

  while (true) {
    status = sqlite3_step(stmt);

    if (status==SQLITE_DONE) {
      break;
    } else if (status==SQLITE_ROW) {
      const char *txt = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
      if (txt==NULL) {
	result = "";
      } else {
	result = txt;
      }
    } else {
      sqlite3_reset (stmt);
      throw new sqlite_exception(str(boost::format(Sqlite_Query_Error) % sql));
    }
  }

  sqlite3_reset (stmt);
  return result;
}

void sqlite_connection::sql_exec(const std::string &sql) 
{
  int status = sqlite3_exec(ppdb, sql.c_str(), NULL, NULL, NULL);

  if (status!=SQLITE_OK) {
    throw sqlite_exception(str(boost::format(Sqlite_Query_Error) % sql));
  }
}

std::tr1::shared_ptr<db_recordset> sqlite_connection::sql_retrieve(const std::string &sql)
{
  sqlite3_stmt *stmt;
  int status;

  status = sqlite3_prepare(ppdb, sql.c_str(), sql.size(), &stmt, NULL);
  if (status!=SQLITE_OK) {
    sqlite3_reset(stmt);
    throw sqlite_exception(str(boost::format(Sqlite_Query_Error) % sql));
  }

  return std::tr1::shared_ptr<db_recordset>(new sqlite_result_set(stmt, sql));
}

bool sqlite_result_set::next() {
  while (true) {
    int status = sqlite3_step (stmt);
    if (status==SQLITE_ROW) {
      return true;
    } else if (status==SQLITE_DONE) {
      return false;
    } else {
      throw sqlite_exception(str(boost::format(Sqlite_Getting_Result) % sql));
    }
  }
}
