#include "Dictionary.h"
#include <fstream>
#include <algorithm>
#include <iostream>

namespace scrabble {

bool Dictionary::loadFromFile(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "[Error] Cannot open dictionary file: " << filepath << std::endl;
        return false;
    }

    words_.clear();
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }

        std::string cleaned = "";
        bool valid = true;
        for (char c : line) {
            if (std::isalpha(static_cast<unsigned char>(c))) {
                cleaned += static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
            } else if (!std::isspace(static_cast<unsigned char>(c))) {
                valid = false;
                break;
            }
        }

        if (valid && !cleaned.empty()) {
            words_.insert(cleaned);
        }
    }

    std::cout << "[Dictionary] Loaded " << words_.size() << " words from " << filepath << std::endl;
    return !words_.empty();
}

bool Dictionary::contains(const std::string& word) const {
    std::string upperWord = "";
    for (char c : word) {
        upperWord += static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
    }
    return words_.find(upperWord) != words_.end();
}

size_t Dictionary::size() const {
    return words_.size();
}

}