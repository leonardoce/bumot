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

class BuMotFindCriteria {
private:
  std::string searchString;
  bool searchInRap;
  bool searchInEng;
  bool extendedSearch;

public:
  void set_search_string(const std::string &theSearchString) {  searchString = theSearchString; };
  const std::string &get_search_string() const { return searchString; };

  void set_search_in_rap(bool mustSearchInRap) { searchInRap=mustSearchInRap; };
  bool get_search_in_rap() const { return searchInRap; };

  void set_search_in_eng(bool mustSearchInEng) { searchInEng=mustSearchInEng; };
  bool get_search_in_eng() const { return searchInEng; };

  void set_extended_search(bool mustDoExtendedSearch) { extendedSearch = mustDoExtendedSearch; };
  bool get_extended_search() const { return extendedSearch; };
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
  std::vector<BuMotRecord> Find(const BuMotFindCriteria &criteria);
};

BuMotDb& CurrentDatabase();

#endif
