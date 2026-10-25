#include "BoardView.h"

#include <string>

namespace scrabble {

namespace {

sf::Color squareColor(const Theme& theme, const SquareView& sq) {
    if (sq.wordMultiplier == 3) return theme.tripleWordColor;
    if (sq.wordMultiplier == 2) return theme.doubleWordColor;
    if (sq.letterMultiplier == 3) return theme.tripleLetterColor;
    if (sq.letterMultiplier == 2) return theme.doubleLetterColor;
    return theme.normalCellColor;
}

const char* bonusLabel(const SquareView& sq) {
    if (sq.wordMultiplier == 3) return "TW";
    if (sq.wordMultiplier == 2) return "DW";
    if (sq.letterMultiplier == 3) return "TL";
    if (sq.letterMultiplier == 2) return "DL";
    return "";
}

void drawCenteredText(sf::RenderWindow& window, const Theme& theme, const std::string& str,
                      unsigned int size, const RectF& area, sf::Color color) {
    sf::Text text(theme.font, str, size);
    text.setFillColor(color);
    const sf::FloatRect b = text.getLocalBounds();
    text.setPosition({area.x + (area.w - b.size.x) / 2.0f - b.position.x,
                      area.y + (area.h - b.size.y) / 2.0f - b.position.y});
    window.draw(text);
}

}  // namespace

void drawLetterTile(sf::RenderWindow& window, const Theme& theme, const RectF& area,
                    char letter, int points, bool highlighted) {
    sf::RectangleShape tile({area.w - 4.0f, area.h - 4.0f});
    tile.setPosition({area.x + 2.0f, area.y + 2.0f});
    tile.setFillColor(theme.tileColor);
    tile.setOutlineColor(highlighted ? sf::Color(220, 40, 40) : theme.tileBorderColor);
    tile.setOutlineThickness(highlighted ? 3.0f : 2.0f);
    window.draw(tile);

    const unsigned int big = static_cast<unsigned int>(area.h * 0.5f);
    drawCenteredText(window, theme, std::string(1, letter), big, area, theme.textColor);

    // Points in the bottom-right corner.
    const unsigned int small = static_cast<unsigned int>(area.h * 0.24f);
    sf::Text pts(theme.font, std::to_string(points), small);
    pts.setFillColor(theme.textColor);
    const sf::FloatRect b = pts.getLocalBounds();
    pts.setPosition({area.x + area.w - b.size.x - b.position.x - 6.0f,
                     area.y + area.h - b.size.y - b.position.y - 6.0f});
    window.draw(pts);
}

BoardView::BoardView(const Theme& theme) : theme_(theme) {}

bool BoardView::cellAt(float x, float y, int& row, int& col) const {
    return boardCellAt(x, y, row, col);
}

RectF BoardView::cellRect(int row, int col) const { return boardCellRect(row, col); }

void BoardView::draw(sf::RenderWindow& window, const SquareProvider& square) const {
    // Board background.
    sf::RectangleShape back({layout::kBoardSide + 8.0f, layout::kBoardSide + 8.0f});
    back.setPosition({layout::kBoardX - 4.0f, layout::kBoardY - 4.0f});
    back.setFillColor(theme_.boardBackground);
    window.draw(back);

    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            const SquareView sq = square(row, col);
            const RectF r = boardCellRect(row, col);

            sf::RectangleShape cell({r.w - 2.0f, r.h - 2.0f});
            cell.setPosition({r.x + 1.0f, r.y + 1.0f});
            cell.setFillColor(squareColor(theme_, sq));
            window.draw(cell);

            if (sq.hasTile) {
                drawLetterTile(window, theme_, r, sq.letter, sq.points, sq.pending);
            } else if (*bonusLabel(sq) != '\0') {
                drawCenteredText(window, theme_, bonusLabel(sq), 12, r, theme_.textColor);
            }
        }
    }

    // Labels: A-O above, 1-15 on the left (code uses 0..14).
    for (int i = 0; i < BOARD_SIZE; ++i) {
        const RectF c = boardCellRect(0, i);
        drawCenteredText(window, theme_, std::string(1, static_cast<char>('A' + i)), 16,
                         RectF{c.x, layout::kBoardY - 30.0f, c.w, 24.0f}, theme_.textColor);
        const RectF rr = boardCellRect(i, 0);
        drawCenteredText(window, theme_, std::to_string(i + 1), 16,
                         RectF{layout::kBoardX - 22.0f, rr.y, 18.0f, rr.h}, theme_.textColor);
    }
}

}  // namespace scrabble
