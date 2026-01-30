# Noughts and Crosses

A console-based Noughts and Crosses (Tic-Tac-Toe) game written in C++.  
The game supports variable board sizes, multiple game modes, and AI opponents with different difficulty levels.  
This project was developed as part of a college coursework and includes full documentation generated using Doxygen.

---

## Features

- Two-player local mode
- Single-player mode against a bot
- Bot difficulty levels:
  - Easy (random moves)
  - Medium (basic win/block strategy)
  - Hard (center-priority + medium strategy)
- Configurable board size (3×3 up to 19×19)
- Dynamic win condition based on board size
- Colored console output (Windows)
- Doxygen-generated documentation included
- Detailed project report included as PDF

---

## Game Rules

- Players take turns placing `X` and `O` on the board
- The number of consecutive symbols required to win depends on board size:
  - Board size ≤ 6 → 3 in a row
  - Board size 7–9 → 4 in a row
  - Board size ≥ 10 → 5 in a row
- The game ends when a player wins or the board is full (draw)

---

## Controls

- Enter the cell number shown on the board to make a move
- `0` → Restart current game
- `404` → Exit the program

---

## Project Structure

```
Noughts-and-Crosses/
├─ src/
│  └─ main.cpp
├─ docs/
│  ├─ Doxygen.pdf
│  └─ Noughts and Crosses.pdf
├─ CMakeLists.txt
├─ README.md
└─ LICENSE
```

---

## Build Instructions (Windows)

### Using MinGW (g++)

```bash
g++ -std=c++20 src/main.cpp -o noughts.exe
```

> Note: This project uses `windows.h` for console colors, so it is Windows-specific.

### Using CLion (Recommended)

1. Open the project folder in CLion  
2. CLion will detect the `CMakeLists.txt` file automatically  
3. Build and run the project from the IDE

---

## Documentation

- `docs/Doxygen.pdf` — Auto-generated source code documentation  
- `docs/Noughts and Crosses.pdf` — Project report (design, logic, testing and explanation)

---

## Future Improvements

- Cross-platform console support (remove Windows dependency)
- Stronger AI using Minimax algorithm
- Object-oriented refactoring using classes
- Unit testing for win-condition logic
- Graphical user interface (GUI)

---

## Author

**Karthik Raman Keerangudi Kalyanaraman**

---

## License

This project is licensed under the MIT License.
