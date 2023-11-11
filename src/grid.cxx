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

    for (int i{0}; i<y; i++) {
        Grid.push_back(vector<WINDOW*> x)
    }


    //WINDOW* Template{ newwin(, Width, Rows, Cols) }
}
