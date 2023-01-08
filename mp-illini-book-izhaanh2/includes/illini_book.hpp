#ifndef ILLINI_BOOK_HPP
#define ILLINI_BOOK_HPP

#include <string>
#include <vector>
#include <set>
#include <list>
#include <fstream>
#include <map>
#include <queue>
#include "utilities.hpp"

class IlliniBook {
public:
  IlliniBook(const std::string &people_fpath, const std::string &relations_fpath);
  IlliniBook(const IlliniBook &rhs) = delete;
  IlliniBook &operator=(const IlliniBook &rhs) = delete;
  void ReadPeople(const std::string &people_fpath);
  std::set<int> GetPeople();
  void ReadRelations(const std::string &relations_fpath);
  std::map<int, std::list<std::pair<int, std::string>>> GetRelations();
  ~IlliniBook() = default;
  bool AreRelated(int uin_1, int uin_2) const;
  bool AreRelated(int uin_1, int uin_2, const std::string &relationship) const;
  int GetRelated(int uin_1, int uin_2) const;
  int GetRelated(int uin_1, int uin_2, const std::string &relationship) const;
  std::vector<int> GetSteps(int uin, int n) const;
  size_t CountGroups() const;
  size_t CountGroups(const std::string &relationship) const;
  size_t CountGroups(const std::vector<std::string> &relationships) const;
  std::map<int, int> GetConnectedDistances(int uin, const std::vector<std::string>& relationships) const;
private:
  std::set<int> people_;
  std::map<int, std::list<std::pair<int, std::string>>> relations_;
};

#endif
