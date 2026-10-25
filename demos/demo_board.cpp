// demo_board: shows BoardView alone in a window, using FAKE data.
// It does not use Board.h. Move the mouse: the window title shows the square
// under the mouse (like "H8"). Close the window to quit.
// Run it from the folder that contains assets/ (build\Debug\).
#include <SFML/Graphics.hpp>
#include <iostream>
#include <optional>
#include <string>

#include "BoardView.h"
#include "Theme.h"

using namespace scrabble;

namespace {

// Fake bonus layout (standard Scrabble). Only for this demo.
SquareView fakeSquare(int row, int col) {
    SquareView sq;

    const int tw[][2] = {{0, 0}, {0, 7}, {0, 14}, {7, 0}, {7, 14}, {14, 0}, {14, 7}, {14, 14}};
    const int dw[][2] = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {1, 13}, {2, 12}, {3, 11}, {4, 10},
                         {10, 4}, {11, 3}, {12, 2}, {13, 1}, {10, 10}, {11, 11}, {12, 12},
                         {13, 13}, {7, 7}};
    const int tl[][2] = {{1, 5}, {1, 9}, {5, 1}, {5, 5}, {5, 9}, {5, 13},
                         {9, 1}, {9, 5}, {9, 9}, {9, 13}, {13, 5}, {13, 9}};
    const int dl[][2] = {{0, 3}, {0, 11}, {2, 6}, {2, 8}, {3, 0}, {3, 7}, {3, 14}, {6, 2},
                         {6, 6}, {6, 8}, {6, 12}, {7, 3}, {7, 11}, {8, 2}, {8, 6}, {8, 8},
                         {8, 12}, {11, 0}, {11, 7}, {11, 14}, {12, 6}, {12, 8}, {14, 3}, {14, 11}};

    for (const auto& p : tw) if (p[0] == row && p[1] == col) sq.wordMultiplier = 3;
    for (const auto& p : dw) if (p[0] == row && p[1] == col) sq.wordMultiplier = 2;
    for (const auto& p : tl) if (p[0] == row && p[1] == col) sq.letterMultiplier = 3;
    for (const auto& p : dl) if (p[0] == row && p[1] == col) sq.letterMultiplier = 2;

    auto put = [&](char letter, int points, bool pending) {
        sq.hasTile = true;
        sq.letter = letter;
        sq.points = points;
        sq.pending = pending;
    };

    // CAT across the centre, BAGEL down from (7,3): old tiles.
    if (row == 7 && col == 6) put('C', 3, false);
    if (row == 7 && col == 7) put('A', 1, false);
    if (row == 7 && col == 8) put('T', 1, false);
    if (col == 3 && row >= 3 && row <= 7) {
        const char word[] = "BAGEL";
        const int pts[] = {3, 1, 2, 1, 1};
        put(word[row - 3], pts[row - 3], false);
    }
    // Two pending tiles (red border) below the C.
    if (row == 8 && col == 6) put('A', 1, true);
    if (row == 9 && col == 6) put('B', 3, true);
    return sq;
}

}  // namespace

int main() {
    Theme theme;
    if (!theme.loadFont("assets/fonts/font.ttf")) {
        std::cout << "Cannot open assets/fonts/font.ttf. Run from the folder that contains assets/.\n";
        return 1;
    }

    sf::RenderWindow window(sf::VideoMode({900u, 780u}), "demo_board");
    window.setFramerateLimit(60);
    BoardView view(theme);

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            } else if (const auto* moved = event->getIf<sf::Event::MouseMoved>()) {
                int row = 0, col = 0;
                if (view.cellAt(static_cast<float>(moved->position.x),
                                static_cast<float>(moved->position.y), row, col)) {
                    window.setTitle(std::string("demo_board - ") +
                                    static_cast<char>('A' + col) + std::to_string(row + 1) +
                                    "  (row " + std::to_string(row) + ", col " +
                                    std::to_string(col) + ")");
                } else {
                    window.setTitle("demo_board - outside the board");
                }
            }
        }

        window.clear(theme.backgroundColor);
        view.draw(window, fakeSquare);
        window.display();
    }
    return 0;
}
