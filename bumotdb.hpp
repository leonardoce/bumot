#ifndef __BUMOTDB_HPP
#define __BUMOTDB_HPP

#include <string>
#include "data_connection.hpp"

class Exception : public std::exception {
private:
  const std::string theMessage;
public:
  Exception(const std::string &msg) : theMessage(msg) {};
  ~Exception() throw () {};

  const char *what() { return theMessage.c_str(); };
};

class BuMotDb {
private:
  std::tr1::shared_ptr<db_connection> dbConnection;

public:
  BuMotDb();
  ~BuMotDb() throw ();

  void Init();
};

BuMotDb& CurrentDatabase();

#endif
