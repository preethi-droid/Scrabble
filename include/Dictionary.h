#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <string>
#include <unordered_set>

namespace scrabble {

class Dictionary {
public:
    bool loadFromFile(const std::string& filepath);
    bool contains(const std::string& word) const;
    size_t size() const;

private:
    std::unordered_set<std::string> words_;
};

}

#endif