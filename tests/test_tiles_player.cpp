// Standalone test for Tile, TileBag and Player. No window, no other module needed.
#include <iostream>
#include <map>

#include "Player.h"
#include "Tile.h"
#include "TileBag.h"
#include "Types.h"

using namespace scrabble;

static int failures = 0;

#define CHECK(cond)                                                        \
    do {                                                                   \
        if (!(cond)) {                                                     \
            std::cout << "FAIL line " << __LINE__ << ": " #cond << "\n";   \
            ++failures;                                                    \
        }                                                                  \
    } while (0)

static std::vector<Tile> makeRack(const char* letters) {
    std::vector<Tile> v;
    for (const char* c = letters; *c; ++c) v.emplace_back(*c, Tile::pointsForLetter(*c));
    return v;
}

int main() {
    // ---- Tile ----
    Tile lower('a', 1);
    CHECK(lower.getLetter() == 'A');            // stored uppercase
    CHECK(Tile::pointsForLetter('Q') == 10);
    CHECK(Tile::pointsForLetter('E') == 1);

    // ---- TileBag ----
    TileBag bag(42);
    CHECK(bag.remaining() == TOTAL_TILES);
    std::vector<Tile> all = bag.draw(1000);     // asking for more than exists
    CHECK(all.size() == 98);
    CHECK(bag.isEmpty());
    CHECK(bag.draw(5).empty());                 // stops when empty

    int sum = 0;
    std::map<char, int> counts;
    for (const Tile& t : all) { sum += t.getPoints(); ++counts[t.getLetter()]; }
    CHECK(sum == TOTAL_TILE_POINTS);            // 187
    CHECK(counts['E'] == 12);
    CHECK(counts['A'] == 9);
    CHECK(counts['Q'] == 1);

    bag.returnTiles(all);
    CHECK(bag.remaining() == 98);

    TileBag a(7), b(7), c(8);                   // same seed -> same order
    CHECK(a.draw(98) == b.draw(98));
    CHECK(!(TileBag(7).draw(98) == c.draw(98)));

    // ---- Player ----
    Player p("Mirudhulaa");
    CHECK(p.getName() == "Mirudhulaa");
    CHECK(p.getScore() == 0);
    CHECK(p.addTiles(makeRack("CATBAGE")));     // 7 tiles
    CHECK(p.getRack().size() == 7);
    CHECK(!p.addTiles(makeRack("Z")));          // refuses past 7
    CHECK(p.getRack().size() == 7);

    std::vector<Tile> removed;
    CHECK(!p.removeTilesAt({1, 1}, removed));   // duplicate
    CHECK(!p.removeTilesAt({0, 7}, removed));   // past the end
    CHECK(!p.removeTilesAt({-1}, removed));     // negative
    CHECK(p.getRack().size() == 7);             // nothing changed
    CHECK(p.getRack()[0].getLetter() == 'C');

    CHECK(p.removeTilesAt({0, 2, 5}, removed)); // C, T, G
    CHECK(removed.size() == 3);
    CHECK(removed[0].getLetter() == 'C');
    CHECK(removed[1].getLetter() == 'T');
    CHECK(removed[2].getLetter() == 'G');
    CHECK(p.getRack().size() == 4);
    // Remaining must be A B A E, in original order.
    CHECK(p.getRack()[0].getLetter() == 'A');
    CHECK(p.getRack()[1].getLetter() == 'B');
    CHECK(p.getRack()[2].getLetter() == 'A');
    CHECK(p.getRack()[3].getLetter() == 'E');
    CHECK(p.rackPoints() == 1 + 3 + 1 + 1);

    p.addScore(10);
    p.addScore(5);
    CHECK(p.getScore() == 15);

    if (failures == 0) std::cout << "ALL TESTS PASSED\n";
    else std::cout << failures << " TEST(S) FAILED\n";
    return failures == 0 ? 0 : 1;
}
