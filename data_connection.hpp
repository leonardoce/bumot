#ifndef __STUDIO_HPP
#define __STUDIO_HPP

#include <iostream>
#include <string>
#include <boost/format.hpp>
#include <boost/tr1/memory.hpp>
#include <boost/utility.hpp>
#include "sqlite3.h"

const char * const Sqlite_Error_Message = "Error opening SQLite database %1%"; 
const char * const Sqlite_Query_Error = "Error executing SQL: %1%";
const char * const Sqlite_Getting_Result = "Error getting result of SQL: %1%";

class sqlite_exception : public std::exception
{
private:
  std::string reason;

public:
  sqlite_exception(const std::string &theReason) : reason(theReason) {}
  sqlite_exception(const sqlite_exception &other) : reason(other.reason) {}
  ~sqlite_exception() throw () {};
  sqlite_exception &operator=(const sqlite_exception &rhs) {
    if (this == &rhs) return *this;
    reason = rhs.reason;

    return *this;
  };

  virtual const char *what() const throw () {
    return reason.c_str();
  }
};

class db_recordset : private boost::noncopyable {
public:
  virtual ~db_recordset() {};
  virtual bool next() = 0;
  virtual std::string get_string_field(int i) = 0;
  virtual int get_int_field(int i) = 0;
};

class db_connection : private boost::noncopyable {
public:
  virtual std::string sql_into(const std::string &sql) = 0;
  virtual void sql_exec(const std::string &sql) = 0;
  virtual std::tr1::shared_ptr<db_recordset>  sql_retrieve(const std::string &sql) = 0;

  db_connection() {};
  virtual ~db_connection() throw () {};
};

class sqlite_connection : public db_connection {
public:
  sqlite_connection(const std::string &nomeFile);
  ~sqlite_connection() throw ();

  std::string sql_into(const std::string &sql);
  void sql_exec(const std::string &sql);
  std::tr1::shared_ptr<db_recordset>  sql_retrieve(const std::string &sql);

private:
  sqlite3 *ppdb;
};

class sqlite_result_set : public db_recordset {
public:
  bool next();
  std::string get_string_field(int i) { return reinterpret_cast<const char *>(sqlite3_column_text(stmt, i)); };
  int get_int_field(int i) { return sqlite3_column_int(stmt, i); };
  ~sqlite_result_set() { sqlite3_reset(stmt); };

private:
  sqlite_result_set(sqlite3_stmt* theStatement, const std::string &theSql) : stmt(theStatement), sql(theSql) {};

private:
  sqlite3_stmt *stmt;
  std::string sql;

  friend class sqlite_connection;
};

#endif 
