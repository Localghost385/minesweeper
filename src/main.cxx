#include <curses.h>
#include <grid.hxx>
#include <iterator>
#include <locale.h>
#include <main.hxx>
#include <ncurses.h>
#include <unordered_set>
#include <vector>

// Assuming x and y are the coordinates from where the recursion should start
void
uncoverAdjacentZeros(gameGrid& grid,
                     int y, // Changed parameter order
                     int x, // Changed parameter order
                     vector<vector<bool>>& visited)
{
    // Function body remains the same
    printw("(%d, %d)\n", y, x);

    // Boundary checks
    if (y < 0 || y >= static_cast<int>(grid.grids[2].gridVector.size()) ||
        x < 0 || x >= static_cast<int>(grid.grids[2].gridVector[0].size())) {
        return;
    }

    // Check if the current cell is not zero or already uncovered (set to 1)
    if (visited[y][x]) {
        return;
    }

    printw("test");
    // Set the current cell as uncovered
    grid.grids[2].gridVector[y][x] = 1;
    visited[y][x] = true;

    // Check if the corresponding cell in grid.grids[3].gridVector is also zero
    if (grid.grids[3].gridVector[y][x] != 0) {
        return;
    }

    // Recursive calls for adjacent cells
    uncoverAdjacentZeros(grid, y, x + 1, visited);     // Right
    uncoverAdjacentZeros(grid, y, x - 1, visited);     // Left
    uncoverAdjacentZeros(grid, y + 1, x, visited);     // Down
    uncoverAdjacentZeros(grid, y - 1, x, visited);     // Up
    uncoverAdjacentZeros(grid, y + 1, x + 1, visited); // Diagonal right down
    uncoverAdjacentZeros(grid, y - 1, x - 1, visited); // Diagonal left up
    uncoverAdjacentZeros(grid, y - 1, x + 1, visited); // Diagonal right up
    uncoverAdjacentZeros(grid, y + 1, x - 1, visited); // Diagonal left down
}

class windowSmartPtr
{
  public:
    WINDOW* window;
    windowSmartPtr(int sizeY, int sizeX, int Y, int X)
    {
        window = newwin(sizeY, sizeX, Y, X);
    }
    ~windowSmartPtr() { delwin(window); }
};

int
main()
{

    gameGrid grid(20, 20, 20);
    grid.generateMines();

    setlocale(LC_ALL, "");
    initscr();
    cbreak();
    noecho();
    curs_set(0);

    start_color();
    init_pair(0, COLOR_WHITE, COLOR_BLACK);
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, COLOR_RED, COLOR_BLACK);

    refresh();

    unique_ptr<int> difficulty_selector(new int());
    *difficulty_selector = 0;

    windowSmartPtr game_border(LINES, COLS - 2, 0, 1);
    box(game_border.window, 0, 0);
    wrefresh(game_border.window);

    windowSmartPtr difficulty_one(7, 20, (LINES / 2) - 3, (COLS / 2) - 32);
    windowSmartPtr difficulty_two(7, 20, (LINES / 2) - 3, (COLS / 2) - 10);
    windowSmartPtr difficulty_three(7, 20, (LINES / 2) - 3, (COLS / 2) + 12);

    vector<windowSmartPtr*> difficulties = { &difficulty_one,
                                             &difficulty_two,
                                             &difficulty_three };

    for (int i{ 0 }; i < 3; i++) {
        box(difficulties[i]->window, 0, 0);
        wrefresh(difficulties[i]->window);
    }

    mvprintw(LINES - 2, (COLS / 2) - 11, "A <- / W Select / D ->");

    char input;
    int size{ static_cast<int>(difficulties.size()) };
    while ((input = getch()) != 'w' && input != 'W') {
        if (input == 'a' || input == 'A') {
            if (*difficulty_selector > 0) {
                --(*difficulty_selector);
            } else {
                *difficulty_selector = size - 1;
            }
        } else if (input == 'd' || input == 'D') {
            if (*difficulty_selector < size - 1) {
                ++(*difficulty_selector);
            } else {
                *difficulty_selector = 0;
            }
        }

        for (int i = 0; i < size; ++i) {
            if (i == *difficulty_selector) {
                wbkgd(difficulties[i]->window, COLOR_PAIR(2));
            } else {
                wbkgd(difficulties[i]->window, COLOR_PAIR(0));
            }
            wrefresh(difficulties[i]->window);
        }
    }

    // clear();
    refresh();
    box(game_border.window, 0, 0);
    wrefresh(game_border.window);

    windowSmartPtr contents(grid.grids[0].gridVector[0].size(),
                            grid.grids[0].gridVector[0].size() * 2,
                            (LINES / 2) - 5,
                            (COLS / 2) - 10);
    wbkgd(contents.window, COLOR_PAIR(0));
    box(contents.window, 0, 0);
    wrefresh(contents.window);

    int cursorX{ 0 };
    int cursorY{ 0 };

    int gridSize = grid.grids[0].gridVector[0].size();

    bool gameOver{ false };
    while (!gameOver) {
        int input{ getch() };
        if (input == 'p' || input == 'P') {
            break;
        }

        vector<vector<int>> gridVector = grid.grids[2].gridVector;
        int gridVectorSize = gridVector.size();
        int gridVector0Size = gridVector[0].size();

        switch (input) {
            case 'w':
            case 'W':
                cursorY = (cursorY > 0) ? cursorY - 1 : gridSize - 1;
                break;

            case 's':
            case 'S':
                cursorY = (cursorY < gridSize - 1) ? cursorY + 1 : 0;
                break;

            case 'a':
            case 'A':
                cursorX = (cursorX > 0) ? cursorX - 2 : gridSize * 2 - 2;
                break;

            case 'd':
            case 'D':
                cursorX = (cursorX < gridSize * 2 - 2) ? cursorX + 2 : 0;
                break;

            case 'q':
            case 'Q':
                if ((grid.grids[1].gridVector[cursorY][cursorX / 2] == 0) &&
                    (grid.grids[2].gridVector[cursorY][cursorX / 2] == 0)) {
                    grid.grids[1].gridVector[cursorY][cursorX / 2] = 1;
                } else if (grid.grids[1].gridVector[cursorY][cursorX / 2] ==
                           1) {
                    grid.grids[1].gridVector[cursorY][cursorX / 2] = 0;
                }
                break;
            case 'e':
            case 'E':
                if (grid.grids[2].gridVector[cursorY][cursorX / 2] == 0) {
                    grid.grids[2].gridVector[cursorY][cursorX / 2] = 1;
                    vector<vector<bool>> visited(
                      gridVectorSize, vector<bool>(gridVector0Size, false));
                    uncoverAdjacentZeros(grid, cursorY, cursorX / 2, visited);
                }
                break;
        }

        for (int i = 0; i < gridVectorSize; i++) {
            for (int j = 0; j < gridVector0Size; j++) {
                // Get the current element from the grid vector
                bool currentElement = gridVector[i][j];

                // Check if the current element is 0
                if (currentElement == 0) {
                    // Get the corresponding element from the other grid
                    bool otherElement = grid.grids[1].gridVector[i][j];

                    // Check if the other element is 1
                    if (otherElement == 1) {
                        // Print a flag symbol if the other element is 1
                        mvwprintw(contents.window, i, j * 2, "⚑ ");
                        mvwchgat(contents.window,
                                 i,
                                 j * 2,
                                 2,
                                 COLOR_PAIR(0),
                                 1,
                                 nullptr);
                    } else {
                        // Print a filled block if the other element is
                        // not 1
                        mvwprintw(contents.window, i, j * 2, "██");
                    }
                } else {
                    // Print two spaces if the current element is not 0
                    if (grid.grids[3].gridVector[i][j] != 0 &&
                        grid.grids[3].gridVector[i][j] != 9) {
                        mvwprintw(contents.window,
                                  i,
                                  j * 2,
                                  " %i ",
                                  grid.grids[3].gridVector[i][j]);
                    } else if (grid.grids[3].gridVector[i][j] == 9) {
                        mvwprintw(contents.window, i, j * 2, "󰷚 ");
                        gameOver = true;
                    } else {
                        mvwprintw(contents.window, i, j * 2, "  ");
                    }
                }
            }
        }

        mvwchgat(
          contents.window, cursorY, cursorX, 2, COLOR_PAIR(0), 1, nullptr);
        wrefresh(contents.window);

        // Check for win conditions
        bool hasWon = false;
        for (size_t i = 0; i < grid.grids[0].gridVector.size(); ++i) {
            for (size_t j = 0; j < grid.grids[0].gridVector[i].size(); ++j) {
                if (grid.grids[0].gridVector[i][j] !=
                    (grid.grids[2].gridVector[i][j] == 0 ? 1 : 0)) {
                    // The values are not the inversion of each other
                    hasWon = false;
                    break;
                }
            }
            if (!hasWon) {
                break; // No need to check further if a mismatch was found
            } else {
                hasWon = true;
                break;
            }
        }

        if (hasWon) {
            wprintw(stdscr, "Congratulations! You have won the game!");
            wrefresh(stdscr);
            getch(); // Wait for user input before exiting
        }
    }

    // ██
    refresh();
    getch();
    grid.generateMines();

    return 0;
}