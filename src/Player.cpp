#include "Player.h"

#include <algorithm>
#include <functional>

#include "Types.h"

namespace scrabble {

Player::Player(const std::string& name) : name_(name), score_(0) {}

const std::string& Player::getName() const { return name_; }
int Player::getScore() const { return score_; }
const std::vector<Tile>& Player::getRack() const { return rack_; }

bool Player::addTiles(const std::vector<Tile>& tiles) {
    if (rack_.size() + tiles.size() > static_cast<std::size_t>(RACK_SIZE)) {
        return false;
    }
    rack_.insert(rack_.end(), tiles.begin(), tiles.end());
    return true;
}

bool Player::removeTilesAt(const std::vector<int>& positions, std::vector<Tile>& removed) {
    // 1. Check everything first.
    std::vector<int> sorted = positions;
    std::sort(sorted.begin(), sorted.end());
    for (std::size_t i = 0; i < sorted.size(); ++i) {
        if (sorted[i] < 0 || sorted[i] >= static_cast<int>(rack_.size())) return false;
        if (i > 0 && sorted[i] == sorted[i - 1]) return false;   // duplicate
    }
    // 2. Collect in the caller's order.
    std::vector<Tile> result;
    for (int p : positions) result.push_back(rack_[static_cast<std::size_t>(p)]);
    // 3. Erase from the highest position down.
    std::sort(sorted.begin(), sorted.end(), std::greater<int>());
    for (int p : sorted) rack_.erase(rack_.begin() + p);
    removed = result;
    return true;
}

void Player::addScore(int points) { score_ += points; }

int Player::rackPoints() const {
    int total = 0;
    for (const Tile& t : rack_) total += t.getPoints();
    return total;
}

}  // namespace scrabble
