#ifndef __BUMOTDB_HPP
#define __BUMOTDB_HPP

#include <string>

class Exception : public std::exception {
private:
  const std::string theMessage;
public:
  Exception(const std::string &theMessage) : msg(theMessage) {};
  ~Exception() throw () {};

  const char *what() { return theMessage.c_str(); };
};

class BuMotDb {
public:
  BuMotDb();
  ~BuMotDb();

  void Init();
};

BuMotDb& CurrentDatabase();

#endif
