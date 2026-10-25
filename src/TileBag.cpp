#include "TileBag.h"

#include <algorithm>

namespace scrabble {

namespace {
// Letter counts for the 98 tiles (no blanks). Order is A..Z.
constexpr int kCounts[26] = {
    9, 2, 2, 4, 12, 2, 3, 2, 9, 1, 1, 4, 2,   // A-M
    6, 8, 2, 1, 6, 4, 6, 4, 2, 2, 1, 2, 1     // N-Z
};
}  // namespace

TileBag::TileBag(unsigned int seed) : rng_(seed) {
    for (int i = 0; i < 26; ++i) {
        const char letter = static_cast<char>('A' + i);
        for (int n = 0; n < kCounts[i]; ++n) {
            tiles_.emplace_back(letter, Tile::pointsForLetter(letter));
        }
    }
    std::shuffle(tiles_.begin(), tiles_.end(), rng_);
}

std::vector<Tile> TileBag::draw(int count) {
    std::vector<Tile> drawn;
    while (count > 0 && !tiles_.empty()) {
        drawn.push_back(tiles_.back());
        tiles_.pop_back();
        --count;
    }
    return drawn;
}

void TileBag::returnTiles(const std::vector<Tile>& tiles) {
    tiles_.insert(tiles_.end(), tiles.begin(), tiles.end());
    std::shuffle(tiles_.begin(), tiles_.end(), rng_);
}

int TileBag::remaining() const { return static_cast<int>(tiles_.size()); }
bool TileBag::isEmpty() const { return tiles_.empty(); }

}  // namespace scrabble
