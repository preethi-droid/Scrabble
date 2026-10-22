#ifndef HIGH_SCORE_MANAGER_H
#define HIGH_SCORE_MANAGER_H

#include <string>
#include <vector>
#include <utility>

namespace scrabble {

class HighScoreManager {
public:
    bool load(const std::string& scoresFile);
    bool saveScore(const std::string& scoresFile, const std::string& historyFile, const std::string& playerName, int score);
    const std::vector<std::pair<int, std::string>>& getHighScores() const;

private:
    std::vector<std::pair<int, std::string>> highScores_;
};

}

#endif