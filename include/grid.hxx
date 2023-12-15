#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <main.hxx>
#include <ratio>
#include <string>
#include <vector>

inline int
randint(int min, int max)
{
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<std::mt19937::result_type> dist6(min, max);

    return dist6(rng);
}

class grid
{
  public:
    string title;
    vector<vector<int>> gridVector;

    grid(int sizeY, int sizeX, string _title)
      : title(_title)
      , gridVector(sizeY, vector<int>(sizeX, 0))
    {
    }
};

class gameGrid
{
  public:
    vector<grid> grids;
    int mines;

    gameGrid(int sizeY, int sizeX, int numMines)
    {
        grid minesGrid(sizeY, sizeX, "Mines");
        grids.push_back(minesGrid);

        grid flagsGrid(sizeY, sizeX, "Flags");
        grids.push_back(flagsGrid);

        grid uncoveredGrid(sizeY, sizeX, "Uncovered");
        grids.push_back(uncoveredGrid);
      
        grid proximityGrid(sizeY, sizeX, "Uncovered");
        grids.push_back(proximityGrid);

        mines = numMines;
    }

void print() {
    int sizeX = grids[0].gridVector.size();
    int sizeY = grids[0].gridVector[0].size();
    for (int i = 0; i < sizeX; ++i) {
        for (int j = 0; j < sizeY; ++j) {
            cout << grids[0].gridVector[i][j] << " ";
        }
        cout << endl;
    }
}
    void generateMines()
    {
        int x, y;
        int gridSizeX = grids[0].gridVector.size();
        int gridSizeY = grids[0].gridVector[0].size();

        grids[0].gridVector.reserve(gridSizeX * gridSizeY);

        for (int i = 0; i < mines; i++) {
            do {
                y = randint(0, gridSizeY);
                x = randint(0, gridSizeX - 1);
            } while (grids[0].gridVector[x][y] != 0);

            grids[0].gridVector[x][y] = 1;
        }

        for (int y = 0; y < gridSizeY; ++y) {
            for (int x = 0; x < gridSizeX; ++x) {
                int mineCount = 0;
                // Check all surrounding cells
                for (int dy = -1; dy <= 1; ++dy) {
                    for (int dx = -1; dx <= 1; ++dx) {
                        int nx = x + dx;
                        int ny = y + dy;
                        // Skip checking the center cell
                        if (dx == 0 && dy == 0) continue;
                        // Check bounds and increment mine count if there's a mine
                        if (nx >= 0 && nx < gridSizeX && ny >= 0 && ny < gridSizeY) {
                            if (grids[0].gridVector[ny][nx] == 1) mineCount++;
                        }
                    }
                }
                grids[3].gridVector[y][x] = mineCount;
            }
        }
        for (int y = 0; y < gridSizeY; ++y) {
            for (int x = 0; x < gridSizeX; ++x) {
                if (grids[0].gridVector[y][x] == 1) {
                    grids[3].gridVector[y][x] = 9;
                }
            }
        }
    }

};
