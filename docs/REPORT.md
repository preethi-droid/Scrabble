# Scrabble Project Report

C++ OOP course project. Team of four. Windows, SFML 3.

> Draft started by Mirudhulaa. Sections marked **[TO FILL]** need results or text from
> the whole team. Do not leave them in the final version.

## 1. Introduction

A Scrabble game for 2 to 4 players on one computer. Players drag letter tiles from
their rack onto the board and press Submit. The game checks that the placement is
legal, looks the words up in a dictionary file, adds the score with bonus squares,
refills the rack and passes the turn.

Not included: blank tiles, challenges, undo, saving a half-played game, sound,
animation, network play.

## 2. Team and work split

| Member | Name | Work |
|---|---|---|
| 1 | Mirudhulaa | Tile, TileBag, Player, BoardView, RackView |
| 2 | Chinmayi | BoardCell and its five subclasses, Board |
| 3 | Preethi | Dictionary, ScoreCalculator, HighScoreManager, Theme, SidePanel, SetupScreen, CMake build |
| 4 | Dhaniksha | Game, GameWindow, main |

## 3. Design

Three layers, where a layer only uses the layers below it:

1. Rules and data, with no SFML: Tile, TileBag, Player, BoardCell and its subclasses,
   Board, Dictionary, ScoreCalculator, HighScoreManager.
2. Referee: Game. It owns the board, bag, players and calculator and remembers the
   pending tiles. It knows nothing about windows or the mouse.
3. Window, using SFML: GameWindow, Theme, BoardView, RackView, SidePanel, SetupScreen.
   Views only draw what they are given. Only GameWindow talks to Game.

Splitting the rules from the window means the rules can be tested without opening a
window.

Details of the parts by Member 1 are in `docs/DESIGN.md`.

## 4. Object-oriented concepts used

- **Encapsulation:** `Player` keeps its rack private. Tiles can only be added or
  removed through functions that check the rules (rack limit of 7, validated removal).
- **Inheritance and polymorphism:** `BoardCell` is an abstract class with five
  subclasses (normal, double letter, triple letter, double word, triple word). Code
  asks each cell for its multipliers and never checks the cell type. **[Chinmayi to
  confirm and add detail]**
- **Abstraction:** the views take a function that describes each square instead of
  using the board class directly, so drawing does not depend on how the board stores
  its data.
- **Separation of concerns:** game rules, referee and window are three layers.
- **Error handling without exceptions:** errors are returned as values (`ActionResult`).

## 5. Implementation notes

- 98 tiles with the standard letter counts and no blanks. Points add up to 187.
- The bag is shuffled with a seed so tests are repeatable.
- Mouse-to-square maths uses `floor`, because plain integer cutting maps points just
  left of or above the board to the wrong square.
- Removing tiles from a rack checks everything first and removes from the highest
  position down, so a failed removal changes nothing.
- The geometry is header-only with no SFML, so it is tested without a window.

**[TO FILL by each member: one or two paragraphs on the hardest part of their work.]**

## 6. Testing

| Test | Covers | Result |
|---|---|---|
| `test_tiles_player` | tiles, bag, player | **[TO FILL after the CMake build]** |
| `test_views_geometry` | square and slot maths | **[TO FILL after the CMake build]** |
| `test_board` | layout counts, placement rules | **[TO FILL]** |
| `test_dict_score` | dictionary, scoring | **[TO FILL]** |
| `test_panel_geometry` | side panel buttons | **[TO FILL]** |
| `test_game` | turns, submit, pass, exchange, game over | **[TO FILL]** |
| `test_integration` | board with real game | **[TO FILL]** |

Reference scores to check by hand: CAT = 10, BAGEL = 22, A and B below the C of CAT = 8,
and +50 for a move that uses all 7 tiles.

Manual checklist and a full game played by hand: **[TO FILL]**

## 7. Problems and how we solved them

- The original long guide was not available to the team, so the shared headers
  (`Types.h`, `Tile.h` and others) were written as a draft and agreed together.
- SFML is not stored in the repository, so every member downloads the same version.
- Layout numbers were missing in `Theme.h`, so they were placed in `ViewGeometry.h`.

**[TO FILL: add problems found while integrating.]**

## 8. Limitations and possible extensions

Not implemented: blank tiles, challenges, undo, saving a game in progress, sound,
animation, network play. **[TO FILL: other limits found during testing.]**

## 9. How to build and run

See `README.md`.

## 10. References

- SFML 3 documentation: https://www.sfml-dev.org/documentation/
- Word list used for the dictionary: **[TO FILL with name and licence]**
- Font used: **[TO FILL with name and licence]**
