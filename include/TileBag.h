#ifndef TILE_BAG_H
#define TILE_BAG_H

#include <random>
#include <vector>

#include "Tile.h"

// DRAFT v0.1 - no SFML here.
namespace scrabble {

class TileBag {
public:
    explicit TileBag(unsigned int seed = 0);   // same seed -> same order (for tests)

    // Takes up to `count` tiles from the back. Returns fewer if the bag runs out.
    std::vector<Tile> draw(int count);

    // Puts tiles back and reshuffles.
    void returnTiles(const std::vector<Tile>& tiles);

    int remaining() const;
    bool isEmpty() const;

private:
    std::vector<Tile> tiles_;
    std::mt19937 rng_;
};

}  // namespace scrabble

#endif
