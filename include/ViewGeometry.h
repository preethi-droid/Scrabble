#ifndef VIEW_GEOMETRY_H
#define VIEW_GEOMETRY_H

// DRAFT v0.1 - owner: Mirudhulaa. Pure maths, NO SFML, header-only,
// so it can be tested without a window (test_views_geometry).
// Screen positions are in pixels. Rows and columns start from 0 (board is 0..14).
#include <cmath>

#include "Types.h"

namespace scrabble {
namespace layout {

// Board: 15 x 15 squares.
constexpr float kBoardX = 20.0f;      // left edge of square (0,0)
constexpr float kBoardY = 40.0f;      // top edge of square (0,0); room above for A-O labels
constexpr float kCellSize = 40.0f;
constexpr float kBoardSide = kCellSize * BOARD_SIZE;   // 600

// Rack: 7 slots in a row below the board.
constexpr float kRackX = 20.0f;
constexpr float kRackY = kBoardY + kBoardSide + 30.0f; // 670
constexpr float kSlotSize = 50.0f;
constexpr float kSlotGap = 8.0f;

constexpr float kRackWidth = RACK_SIZE * kSlotSize + (RACK_SIZE - 1) * kSlotGap;

}  // namespace layout

struct RectF {
    float x = 0, y = 0, w = 0, h = 0;
};

// ---- Board ----

inline RectF boardCellRect(int row, int col) {
    return RectF{layout::kBoardX + col * layout::kCellSize,
                 layout::kBoardY + row * layout::kCellSize,
                 layout::kCellSize, layout::kCellSize};
}

// Which square is under the point? Returns false if outside the board.
// Uses floor (not integer cutting) so points left of / above the board
// do not wrongly map to square 0.
inline bool boardCellAt(float px, float py, int& row, int& col) {
    const float fx = std::floor((px - layout::kBoardX) / layout::kCellSize);
    const float fy = std::floor((py - layout::kBoardY) / layout::kCellSize);
    if (fx < 0.0f || fy < 0.0f || fx >= BOARD_SIZE || fy >= BOARD_SIZE) return false;
    col = static_cast<int>(fx);
    row = static_cast<int>(fy);
    return true;
}

// ---- Rack ----

inline RectF rackSlotRect(int slot) {
    return RectF{layout::kRackX + slot * (layout::kSlotSize + layout::kSlotGap),
                 layout::kRackY, layout::kSlotSize, layout::kSlotSize};
}

// Which rack slot is under the point? Returns false if none.
// The small gaps between slots count as "no slot".
inline bool rackSlotAt(float px, float py, int& slot) {
    if (py < layout::kRackY || py >= layout::kRackY + layout::kSlotSize) return false;
    const float step = layout::kSlotSize + layout::kSlotGap;
    const float fi = std::floor((px - layout::kRackX) / step);
    if (fi < 0.0f || fi >= RACK_SIZE) return false;
    const float inside = (px - layout::kRackX) - fi * step;   // 0 .. step
    if (inside >= layout::kSlotSize) return false;            // in the gap
    slot = static_cast<int>(fi);
    return true;
}

}  // namespace scrabble

#endif
