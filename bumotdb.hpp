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
public:
  class BuMotRecord {
  private:
    std::string rapmot;
    std::string engmot;
  public:
    const std::string &get_rapmot() const { return rapmot; };
    const std::string &get_engmot() const { return engmot; };
    BuMotRecord(const std::string &theRapMot, const std::string &theEngMot)
      : rapmot(theRapMot), engmot(theEngMot) {};
  };

private:
  std::tr1::shared_ptr<db_connection> dbConnection;

public:
  BuMotDb();
  ~BuMotDb() throw ();

  void Init();
  std::vector<BuMotRecord> Find(const std::string &findStr);
};

BuMotDb& CurrentDatabase();

#endif
