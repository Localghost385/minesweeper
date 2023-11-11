#include <grid.hxx>
#include <main.hxx>
#include <vector>

int
rant(int min, int max)
{
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<std::mt19937::result_type> dist6(min, max);

    return dist6(rng);
}

void
grid(int y, int x)
{
    vector<vector<WINDOW*>> Grid;

    // WINDOW* Template{ newwin(, Width, Rows, Cols) }
}
