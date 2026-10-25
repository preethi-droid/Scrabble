#ifndef TILE_H
#define TILE_H

// DRAFT v0.1 - to be typed and frozen together by the whole team. No SFML here.
namespace scrabble {

class Tile {
public:
    Tile();                              // empty tile: letter '?', 0 points
    Tile(char letter, int points);       // letter is stored UPPERCASE

    char getLetter() const;
    int getPoints() const;

    bool operator==(const Tile& other) const;

    // Standard point value of an uppercase letter A-Z (0 if not a letter).
    static int pointsForLetter(char letter);

private:
    char letter_;
    int points_;
};

}  // namespace scrabble

#endif
