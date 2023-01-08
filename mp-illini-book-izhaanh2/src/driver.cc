#include "illini_book.hpp"
#include <iostream>

int main() {
  IlliniBook* example = new IlliniBook("example/persons.csv", "example/relations.csv");
  std::set<int> people = example->GetPeople();
  std::map<int, std::list<std::pair<int, std::string>>> relations = example->GetRelations();
  std::vector<std::string> relations_vector;
  // relations_vector.push_back("");
  // relations_vector.push_back("128");
  relations_vector.push_back("124");
  std::map<int, int> distances = example->GetConnectedDistances(1, relations_vector);
  // std::queue<int> orders = example->Tester(3, relations_vector);
  // for (auto uin : people) {
  //   std::cout << uin << std::endl;
  // }
  // for (auto const& [key, value] : relations) {
  //   for (auto pair : value) {
  //     std::cout << key << ',' << pair.first << ',' << pair.second << std::endl;
  //   }
  // }
  // for (auto const& [key, value] : distances) {
  //   std::cout << key << ',' << value << std::endl;
  // }
  std::cout << example->AreRelated(1, 2, "124") << std::endl;
  return 0;
}
