#include <cstdlib>
#include <iostream>
#include <main.hxx>

inline int
randint(int min, int max)
{
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<std::mt19937::result_type> dist6(min, max);

    return dist6(rng);
}

class gridSmall
{
  private:
    int gridMines[9][9];

    int gridFlags[9][9];
    int gridUncovered[9][9];
    int mines{ 10 };

  public:
    void initialize()
    {
        for (int i{ 0 }; i < 9; i++) {
            for (int j{ 0 }; j < 9; j++) {
                gridMines[i][j] = 0;
            }
            cout << endl;
        }
        for (int i{ 0 }; i < 9; i++) {
            for (int j{ 0 }; j < 9; j++) {
                gridFlags[i][j] = 0;
            }
            cout << endl;
        }
        for (int i{ 0 }; i < 9; i++) {
            for (int j{ 0 }; j < 9; j++) {
                gridUncovered[i][j] = 0;
            }
            cout << endl;
        }
    }

    void print()
    {
        cout << "Mines" << endl;
        for (int i{ 0 }; i < 9; i++) {
            for (int j{ 0 }; j < 9; j++) {
                cout << gridMines[i][j] << " ";
            }
            cout << endl;
        }
        cout << "Flags" << endl;
        for (int i{ 0 }; i < 9; i++) {
            for (int j{ 0 }; j < 9; j++) {
                cout << gridFlags[i][j] << " ";
            }
            cout << endl;
        }
        cout << "Uncovered" << endl;
        for (int i{ 0 }; i < 9; i++) {
            for (int j{ 0 }; j < 9; j++) {
                cout << gridUncovered[i][j] << " ";
            }
            cout << endl;
        }
    }
    void generateMines()
    {
        int a, b;
        for (int i{ 0 }, j{ 0 }; i < mines; i++) {
            while (i == j) {
                a = randint(0, 8);
                b = randint(0, 8);
                if (gridMines[a][b] == 0) {
                    gridMines[a][b] = 1;
                    j++;
                }
            }
        }
    }
};
