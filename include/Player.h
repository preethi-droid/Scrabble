#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>

#include "Tile.h"

// DRAFT v0.1 - no SFML here.
namespace scrabble {

class Player {
public:
    explicit Player(const std::string& name);

    const std::string& getName() const;
    int getScore() const;
    const std::vector<Tile>& getRack() const;

    // Adds tiles to the rack. Refuses (returns false, changes nothing)
    // if the rack would go past 7 tiles.
    bool addTiles(const std::vector<Tile>& tiles);

    // Removes tiles at the given rack positions. Checks everything first:
    // no duplicate positions, none out of range. If anything is wrong,
    // returns false and changes nothing. Removes from the highest position
    // down so the other positions do not shift. Removed tiles go in `removed`
    // in the same order as `positions`.
    bool removeTilesAt(const std::vector<int>& positions, std::vector<Tile>& removed);

    void addScore(int points);
    int rackPoints() const;      // sum of points of tiles left in the rack

private:
    std::string name_;
    int score_;
    std::vector<Tile> rack_;
};

}  // namespace scrabble

#endif
