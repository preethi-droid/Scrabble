// Window-free test for the screen maths of BoardView and RackView.
// Only needs ViewGeometry.h and Types.h (no SFML).
#include <iostream>

#include "ViewGeometry.h"

using namespace scrabble;

static int failures = 0;

#define CHECK(cond)                                                        \
    do {                                                                   \
        if (!(cond)) {                                                     \
            std::cout << "FAIL line " << __LINE__ << ": " #cond << "\n";   \
            ++failures;                                                    \
        }                                                                  \
    } while (0)

int main() {
    int row = -1, col = -1, slot = -1;

    // ---- Board: every square's centre maps back to itself ----
    for (int r = 0; r < BOARD_SIZE; ++r) {
        for (int c = 0; c < BOARD_SIZE; ++c) {
            const RectF rc = boardCellRect(r, c);
            CHECK(boardCellAt(rc.x + rc.w / 2, rc.y + rc.h / 2, row, col));
            CHECK(row == r && col == c);
            // Top-left corner belongs to this square, bottom-right edge to the next one.
            CHECK(boardCellAt(rc.x, rc.y, row, col) && row == r && col == c);
            CHECK(boardCellAt(rc.x + rc.w - 0.01f, rc.y + rc.h - 0.01f, row, col) &&
                  row == r && col == c);
        }
    }

    // ---- Board: points just outside must NOT map to square 0 (floor, not int cut) ----
    CHECK(!boardCellAt(layout::kBoardX - 0.5f, layout::kBoardY + 10, row, col));   // just left
    CHECK(!boardCellAt(layout::kBoardX + 10, layout::kBoardY - 0.5f, row, col));   // just above
    CHECK(!boardCellAt(layout::kBoardX - 30, layout::kBoardY - 30, row, col));
    CHECK(!boardCellAt(layout::kBoardX + layout::kBoardSide, layout::kBoardY + 5, row, col));
    CHECK(!boardCellAt(layout::kBoardX + 5, layout::kBoardY + layout::kBoardSide, row, col));
    CHECK(!boardCellAt(-100, -100, row, col));

    // Last square is (14,14).
    CHECK(boardCellAt(layout::kBoardX + layout::kBoardSide - 1,
                      layout::kBoardY + layout::kBoardSide - 1, row, col));
    CHECK(row == 14 && col == 14);

    // Centre square (7,7) sits in the middle of the board.
    const RectF centre = boardCellRect(7, 7);
    CHECK(centre.x == layout::kBoardX + 7 * layout::kCellSize);
    CHECK(centre.y == layout::kBoardY + 7 * layout::kCellSize);

    // ---- Rack: slot centres map back to themselves ----
    for (int i = 0; i < RACK_SIZE; ++i) {
        const RectF rc = rackSlotRect(i);
        CHECK(rackSlotAt(rc.x + rc.w / 2, rc.y + rc.h / 2, slot));
        CHECK(slot == i);
        CHECK(rackSlotAt(rc.x, rc.y, slot) && slot == i);
        CHECK(rackSlotAt(rc.x + rc.w - 0.01f, rc.y + rc.h - 0.01f, slot) && slot == i);
    }

    // Gaps between slots are not slots.
    for (int i = 0; i + 1 < RACK_SIZE; ++i) {
        const RectF rc = rackSlotRect(i);
        CHECK(!rackSlotAt(rc.x + rc.w + layout::kSlotGap / 2, rc.y + 5, slot));
    }

    // Outside the rack.
    CHECK(!rackSlotAt(layout::kRackX - 0.5f, layout::kRackY + 5, slot));            // just left
    CHECK(!rackSlotAt(layout::kRackX + 5, layout::kRackY - 0.5f, slot));            // just above
    CHECK(!rackSlotAt(layout::kRackX + 5, layout::kRackY + layout::kSlotSize, slot)); // just below
    CHECK(!rackSlotAt(layout::kRackX + layout::kRackWidth + 1, layout::kRackY + 5, slot));

    // Rack is below the board and does not overlap it.
    CHECK(layout::kRackY > layout::kBoardY + layout::kBoardSide);

    if (failures == 0) std::cout << "ALL TESTS PASSED\n";
    else std::cout << failures << " TEST(S) FAILED\n";
    return failures == 0 ? 0 : 1;
}
