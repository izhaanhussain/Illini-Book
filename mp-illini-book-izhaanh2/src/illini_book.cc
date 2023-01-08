#include "illini_book.hpp"

IlliniBook::IlliniBook(const std::string &people_fpath, const std::string &relations_fpath) {
    ReadPeople(people_fpath);
    ReadRelations(relations_fpath);
}

void IlliniBook::ReadPeople(const std::string &people_fpath) {
    std::ifstream ifs(people_fpath);
    int uin = 0;
    while (ifs.good()) {
        if (ifs >> uin) {
            people_.insert(uin);
        }
    }
}

std::set<int> IlliniBook::GetPeople() {
    return people_;
}

void IlliniBook::ReadRelations(const std::string &relations_fpath) {
    std::ifstream ifs(relations_fpath);
    std::string line;
    int uin1 = 0;
    int uin2 = 0;
    std::string relation;
    std::vector<std::string> line_vector;
    while (ifs.good()) {
        if (ifs >> line) {
            std::pair<int, std::string> pair_temp;
            line_vector = utilities::Split(line, ',');
            uin1 = std::stoi(line_vector.at(0));
            uin2 = std::stoi(line_vector.at(1));
            relation = line_vector.at(2);
            pair_temp.first = uin2;
            pair_temp.second = relation;
            if (relations_.contains(uin1)) {
                relations_.at(uin1).push_back(pair_temp);
            } else {
                std::list<std::pair<int, std::string>> list_temp;
                list_temp.push_back(pair_temp);
                relations_.insert({uin1, list_temp});
            }
            pair_temp.first = uin1;
            if (relations_.contains(uin2)) {
                relations_.at(uin2).push_back(pair_temp);
            } else {
                std::list<std::pair<int, std::string>> list_temp;
                list_temp.push_back(pair_temp);
                relations_.insert({uin2, list_temp});
            }
        }
    }
    for (auto person : people_) {
        if (!relations_.contains(person)) {
            std::list<std::pair<int, std::string>> list_temp;
            relations_.insert({person, list_temp});
        }
    }
}

std::map<int, std::list<std::pair<int, std::string>>> IlliniBook::GetRelations() {
    return relations_;
}

std::map<int, int> IlliniBook::GetConnectedDistances(int uin, const std::vector<std::string>& relationships) const {
    std::map<int, int> ret;
    std::set<int> visited;
    std::queue<int> queue;
    bool found = false;
    visited.insert(uin);
    queue.push(uin);
    ret.insert({uin, 0});
    while (!queue.empty()) {
        int front = queue.front();
        queue.pop();
        for (auto const &pair : relations_.at(front)) {
            for (unsigned int i = 0; i < relationships.size(); ++i) {
                if (pair.second == relationships.at(i) || relationships.at(i).empty()) {
                    found = true;
                    break;
                }
            }
            if (found) {
                if (!visited.contains(pair.first)) {
                    queue.push(pair.first);
                    visited.insert(pair.first);
                } 
                ret.insert({pair.first, ret[front] + 1});
                found = false;
            }         
        }
    }
    return ret;
}

bool IlliniBook::AreRelated(int uin_1, int uin_2) const {
    return AreRelated(uin_1, uin_2, "");
}

bool IlliniBook::AreRelated(int uin_1, int uin_2, const std::string &relationship) const {
    std::vector<std::string> vec;
    vec.push_back(relationship);
    std::map<int, int> distances = GetConnectedDistances(uin_1, vec);
    return distances.contains(uin_2);
}

int IlliniBook::GetRelated(int uin_1, int uin_2) const {
    return GetRelated(uin_1, uin_2, "");
}

int IlliniBook::GetRelated(int uin_1, int uin_2, const std::string &relationship) const {
    std::vector<std::string> vec;
    vec.push_back(relationship);
    std::map<int, int> distances = GetConnectedDistances(uin_1, vec);
    if (!distances.contains(uin_2)) {
        return -1;
    } else {
        return distances.at(uin_2);
    }
}

std::vector<int> IlliniBook::GetSteps(int uin, int n) const {
    std::vector<int> ret;
    std::vector<std::string> vec;
    vec.push_back("");
    std::map<int, int> distances = GetConnectedDistances(uin, vec);
    for (auto const& [key, value] : distances) {
        if (value == n) {
            ret.push_back(key);
        }
    }
    return ret;
}

size_t IlliniBook::CountGroups() const {
    return CountGroups("");
}

size_t IlliniBook::CountGroups(const std::string &relationship) const {
    std::vector<std::string> vec;
    vec.push_back(relationship);
    return CountGroups(vec);
}

size_t IlliniBook::CountGroups(const std::vector<std::string> &relationships) const {
    size_t ret = 0;
    std::set<int> visited;
    for (auto person : people_) {
        if (!visited.contains(person)) {
            std::map<int, int> distances = GetConnectedDistances(person, relationships);
            for (auto const& [key, value] : distances) {
                visited.insert(key);
            }
            ret++;
        }
    }
    return ret;
}