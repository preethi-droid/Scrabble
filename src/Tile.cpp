#include "Tile.h"

#include <cctype>

namespace scrabble {

Tile::Tile() : letter_('?'), points_(0) {}

Tile::Tile(char letter, int points)
    : letter_(static_cast<char>(std::toupper(static_cast<unsigned char>(letter)))),
      points_(points) {}

char Tile::getLetter() const { return letter_; }
int Tile::getPoints() const { return points_; }

bool Tile::operator==(const Tile& other) const {
    return letter_ == other.letter_ && points_ == other.points_;
}

int Tile::pointsForLetter(char letter) {
    switch (std::toupper(static_cast<unsigned char>(letter))) {
        case 'A': case 'E': case 'I': case 'O': case 'U':
        case 'L': case 'N': case 'R': case 'S': case 'T': return 1;
        case 'D': case 'G': return 2;
        case 'B': case 'C': case 'M': case 'P': return 3;
        case 'F': case 'H': case 'V': case 'W': case 'Y': return 4;
        case 'K': return 5;
        case 'J': case 'X': return 8;
        case 'Q': case 'Z': return 10;
        default: return 0;
    }
}

}  // namespace scrabble
