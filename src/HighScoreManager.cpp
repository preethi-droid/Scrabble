#include "HighScoreManager.h"
#include <fstream>
#include <algorithm>

namespace scrabble {

bool HighScoreManager::load(const std::string& scoresFile) {
    highScores_.clear();
    std::ifstream file(scoresFile);
    if (!file.is_open()) return false;

    std::string line;
    while (std::getline(file, line)) {
        size_t delimPos = line.find(';');
        if (delimPos == std::string::npos) continue;

        std::string scoreStr = line.substr(0, delimPos);
        std::string name = line.substr(delimPos + 1);

        try {
            int score = std::stoi(scoreStr);
            highScores_.push_back({score, name});
        } catch (...) {
            continue;
        }
    }

    std::sort(highScores_.begin(), highScores_.end(), [](auto& a, auto& b) {
        return a.first > b.first;
    });

    if (highScores_.size() > 10) {
        highScores_.resize(10);
    }
    return true;
}

bool HighScoreManager::saveScore(const std::string& scoresFile, const std::string& historyFile, const std::string& playerName, int score) {
    std::ofstream hist(historyFile, std::ios::app);
    if (hist.is_open()) {
        hist << score << ";" << playerName << "\n";
    }

    highScores_.push_back({score, playerName});
    std::sort(highScores_.begin(), highScores_.end(), [](auto& a, auto& b) {
        return a.first > b.first;
    });
    if (highScores_.size() > 10) {
        highScores_.resize(10);
    }

    std::ofstream file(scoresFile);
    if (!file.is_open()) return false;

    for (const auto& entry : highScores_) {
        file << entry.first << ";" << entry.second << "\n";
    }
    return true;
}

const std::vector<std::pair<int, std::string>>& HighScoreManager::getHighScores() const {
    return highScores_;
}

}