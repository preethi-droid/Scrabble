# Scrabble

A Scrabble game for 2 to 4 players on one computer, written in C++17 with SFML 3
for the window. Course project for C++ OOP.

You drag letter tiles from your rack onto the board and press **Submit**. The game
checks that the placement is legal, looks the words up in a dictionary file, adds the
score (with bonus squares), refills your rack and passes the turn.

Not included: blank tiles, challenges, undo, saving a half-played game, sound,
animation, network play.

## Team

| Member | Name | Main job |
|---|---|---|
| 1 | Mirudhulaa | Tiles, tile bag, players, drawing the board and rack |
| 2 | Chinmayi | Board squares and board logic |
| 3 | Preethi | Dictionary, scoring, high scores, side panel, setup screen, build |
| 4 | Dhaniksha | Game (the referee), game window with mouse handling, `main` |

## What you need (Windows)

- Visual Studio 2022 Community with the workload **Desktop development with C++**
  (all four team members must use the same version and the MSVC compiler, not MinGW)
- Git for Windows
- CMake 3.22 or newer (included with Visual Studio 2022)
- SFML 3.1.0 for **Visual C++ 17 (2022) - 64-bit**

## Get SFML (once per laptop)

SFML is not stored in Git (it is listed in `.gitignore`), so everyone downloads it:

1. Download SFML 3.1.0 for Visual C++ 17 (2022) 64-bit from https://www.sfml-dev.org/download/
2. Extract it. You get a folder named `SFML-3.1.0`.
3. Create a folder `SFML-VC` in the project root and put `SFML-3.1.0` inside it.
4. This path must exist:
   `SFML-VC/SFML-3.1.0/lib/cmake/SFML`

## Build

1. Clone the repository and open the folder in Visual Studio 2022
   (File > Open > Folder).
2. Wait for the CMake output to say `CMake generation finished`.
3. Choose Build > Build All.

`data/` and `assets/` are copied next to the executables automatically during the
build.

## Run

Run the programs from `build\Debug\` (not from the project root), because they look
for `assets/fonts/font.ttf` and `data/dictionary.txt` next to the executable.

- `scrabble.exe` - the game
- `demo_board.exe` - draws the board with fake data (move the mouse: the window title
  shows the square, for example `H8`)
- `demo_rack.exe` - draws a rack with fake data (left click selects, right click hides)

If a program says it cannot open a file, you are probably running it from the wrong
folder.

## Tests

Each module has its own test program. They need no window.

- `test_tiles_player` - tile bag (98 tiles, 187 points, letter counts), player rack rules
- `test_views_geometry` - mouse-to-square and mouse-to-slot maths
- `test_board`, `test_dict_score`, `test_panel_geometry`, `test_game`,
  `test_integration` - written by the other members

Each test prints `ALL TESTS PASSED` when it succeeds.

## Project layout

```
include/      headers (what each class can do)
src/          implementation (.cpp), plus main.cpp
demos/        small programs that show one view alone in a window
tests/        one test program per module
docs/         design notes, interface change log, report
assets/fonts/ the font file
data/         dictionary.txt (high scores and history are created while playing)
```

Game logic (tiles, board, rules) does not use SFML. Only the window parts do. This is
why the rules can be tested without opening a window.

## Rules for working in the team

- Everything lives in `namespace scrabble`.
- Rows and columns start at 0 in code (0 to 14). Only the screen shows A-O and 1-15.
- Letters are UPPERCASE inside the game.
- Errors are returned as values, not thrown between modules.
- The rack changes only after Submit succeeds.
- Each file has one owner. Only the owner edits it.
- Work on your own branch, open a pull request, one teammate reviews, then merge.
  Never commit directly to `main`, never force-push, never commit `build/`.
