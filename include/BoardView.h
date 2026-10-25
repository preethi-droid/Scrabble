#ifndef BOARD_VIEW_H
#define BOARD_VIEW_H

// DRAFT v0.1 - owner: Mirudhulaa. SFML allowed (gui side).
// The view only draws what it is handed. It does not include Board.h:
// the caller (GameWindow) gives it a function that describes each square.
#include <SFML/Graphics.hpp>
#include <functional>

#include "Theme.h"
#include "ViewGeometry.h"

namespace scrabble {

// What the view needs to know about one square.
struct SquareView {
    int letterMultiplier = 1;   // 1, 2 or 3
    int wordMultiplier = 1;     // 1, 2 or 3
    bool hasTile = false;
    char letter = ' ';          // UPPERCASE, valid if hasTile
    int points = 0;             // valid if hasTile
    bool pending = false;       // tile dropped this turn but not submitted yet
};

class BoardView {
public:
    using SquareProvider = std::function<SquareView(int row, int col)>;

    explicit BoardView(const Theme& theme);

    // Draws squares, tiles and the A-O / 1-15 labels.
    void draw(sf::RenderWindow& window, const SquareProvider& square) const;

    // Mouse -> square. Returns false if outside the board.
    bool cellAt(float x, float y, int& row, int& col) const;

    // Top-left corner and size of a square, in pixels.
    RectF cellRect(int row, int col) const;

private:
    const Theme& theme_;
};

// Shared by BoardView and RackView: one lettered tile with its points.
void drawLetterTile(sf::RenderWindow& window, const Theme& theme, const RectF& area,
                    char letter, int points, bool highlighted = false);

}  // namespace scrabble

#endif
