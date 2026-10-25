#ifndef TYPES_H
#define TYPES_H

#include <string>

// Shared types and constants. DRAFT v0.1 - no SFML here (core rule).
namespace scrabble {

constexpr int BOARD_SIZE = 15;     // board is 0..14 in code
constexpr int RACK_SIZE = 7;       // tiles per rack
constexpr int TOTAL_TILES = 98;    // no blank tiles
constexpr int TOTAL_TILE_POINTS = 187;

// Errors are returned as values, never thrown between modules.
struct ActionResult {
    bool ok = false;
    std::string message;           // error text when ok == false

    static ActionResult success() { return ActionResult{true, ""}; }
    static ActionResult failure(const std::string& text) { return ActionResult{false, text}; }
};

}  // namespace scrabble

#endif
