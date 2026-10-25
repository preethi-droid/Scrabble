# Design notes: tiles, players, board and rack drawing

Owner: Mirudhulaa (Member 1). This file covers the parts built by Member 1. Other
members add their own sections.

## 1. Where these classes sit

The project has three layers. A layer may only use the layers below it.

| Layer | Contents | SFML allowed? |
|---|---|---|
| Rules and data | `Tile`, `TileBag`, `Player`, Board, Dictionary, ScoreCalculator, HighScoreManager | No |
| Referee | `Game` | No |
| Window | `GameWindow`, `Theme`, `BoardView`, `RackView`, `SidePanel`, `SetupScreen` | Yes |

My classes are in both the bottom and the top layer:

- `Tile`, `TileBag`, `Player` are pure game data (no SFML).
- `BoardView` and `RackView` only draw what they are given.

## 2. Shared constants and error type (`Types.h`)

Draft v0.1, to be agreed by the whole team.

- `BOARD_SIZE = 15`, `RACK_SIZE = 7`, `TOTAL_TILES = 98`, `TOTAL_TILE_POINTS = 187`.
- `ActionResult { bool ok; std::string message; }` with `success()` and
  `failure(text)`. This is how errors are returned as values.

## 3. Tile

A letter and its point value. The letter is stored UPPERCASE.

- `getLetter()`, `getPoints()`, `operator==`.
- `Tile::pointsForLetter(letter)` returns the standard point value of A-Z.
  Keeping the table in one place means TileBag and the tests agree.

## 4. TileBag

98 tiles (no blanks) with the standard letter counts, shuffled with a seed.

- `TileBag(seed)`: the same seed always gives the same order, so tests are repeatable.
- `draw(count)`: takes tiles from the back of the list; returns fewer if the bag runs
  out, and an empty list if the bag is empty.
- `returnTiles(tiles)`: adds them back and reshuffles.
- `remaining()`, `isEmpty()`.

Check used in the tests: the points of all 98 tiles add up to 187.

## 5. Player

Name, score and rack (at most 7 tiles).

- `addTiles(tiles)` refuses (returns false, changes nothing) if the rack would go past 7.
- `removeTilesAt(positions, removed)` validates everything first (no duplicate
  positions, no negative position, no position past the end). If anything is wrong it
  returns false and changes nothing. Only then does it remove, starting from the
  highest position so the other positions do not shift. The removed tiles are returned
  in the order the caller asked for them.
- `addScore(points)`, `rackPoints()` (used for the end-of-game adjustment).

Why validate first: Game's Submit removes the used tiles from the rack before it
commits to the board. A half-finished removal would lose a player's tiles, so this
function must be all-or-nothing.

## 6. BoardView and RackView

The views draw only what they are handed. They never talk to `Game`; only
`GameWindow` does.

### Geometry in one place (`ViewGeometry.h`)

All positions and the "which square is under the mouse" maths are in one header-only
file with no SFML. This is why they can be tested without a window
(`test_views_geometry`).

- Board: top-left of square (0,0) at (34, 40), squares are 40 x 40 pixels.
- Rack: 7 slots of 50 x 50 pixels with 8 pixel gaps, below the board.
- `boardCellAt(x, y, row, col)` and `rackSlotAt(x, y, slot)` use `std::floor`, not
  integer cutting. Integer cutting rounds towards zero, so a point just left of or
  above the board would wrongly map to square 0.
- The gaps between rack slots count as "no slot".

### BoardView

- `draw(window, provider)`. The provider is a function `(row, col) -> SquareView`.
  `SquareView` holds the letter multiplier, word multiplier, and, if a tile is there,
  its letter, points, and whether it is still pending (dropped this turn, not
  submitted).
- BoardView does not include `Board.h`. `GameWindow` converts the real board into
  `SquareView` values. This keeps the views independent of the board's internals and
  lets `demo_board` run with fake data before the board exists.
- Draws A-O above and 1-15 on the left (code uses 0 to 14).
- Pending tiles get a red border.

### RackView

- `draw(window, rack, hidden, selected)`. `hidden[i]` skips a tile that is placed on
  the board or being dragged. `selected[i]` highlights a tile in exchange mode.

### Shared helper

`drawLetterTile(window, theme, area, letter, points, highlighted)` draws one tile and
is used by both views.

## 7. Decisions and open points

- Layout numbers are in `ViewGeometry.h` because `Theme.h` has none yet. They can move
  into `Theme` if Preethi prefers.
- The names in `Types.h`, `Tile.h`, `TileBag.h` and `Player.h` are a draft and become
  frozen when the team agrees.
- The triple-letter colour in `Theme.h` has an alpha of 100, so it blends with the
  board colour and looks purple. Suggested to Preethi.

## 8. Testing

- `test_tiles_player`: tile uppercase, point values, 98 tiles, 187 points, letter
  counts, drawing past empty, same seed gives same order, rack limit of 7, bad
  removals change nothing, removal order, rack points, score.
- `test_views_geometry`: every board square and rack slot maps back to itself,
  corners and edges, points just outside the board, rack gaps, rack below the board.
- `demo_board`, `demo_rack`: drawing is checked by eye with fake data.
