// #include <grid.hxx>
#include <curses.h>
#include <main.hxx>
#include <memory>

class windowSmartPtr
{
  public:
    WINDOW* window;
    windowSmartPtr(int sizeY, int sizeX, int Y, int X)
    {
        window = newwin(sizeY, sizeX, Y, X);
    }
};

int
main()
{
    // gridSmall grdid;
    // grdid.initialize();
    // grdid.generateMines();
    // grdid.print();

    initscr();
    noecho();
    curs_set(0);

    start_color();

    init_pair(0, COLOR_WHITE, COLOR_BLACK);
    init_pair(1, COLOR_BLUE, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);

    refresh();

    printw("waiting");
    getch();

    unique_ptr<int> difficultyselector(new int());
    *difficultyselector = 0;

    windowSmartPtr difficultyOne(7, 20, (LINES / 2) - 3, (COLS / 2) - 32);
    windowSmartPtr difficultyTwo(7, 20, (LINES / 2) - 3, (COLS / 2) - 10);
    windowSmartPtr difficultyThree(7, 20, (LINES / 2) - 3, (COLS / 2) + 12);

    vector<windowSmartPtr> difficulties = { difficultyOne,
                                            difficultyTwo,
                                            difficultyThree };

    for (int i{ 0 }; i < 3; i++) {
        box(difficulties[i].window, 0, 0);
        wrefresh(difficulties[i].window);
    }

    while (true) {
        char input = getch();
        if (input == 'a' || input == 'A') {
            if (*difficultyselector > 0) {
                *difficultyselector -= 1;
            } else {
                *difficultyselector = difficulties.size() - 1;
            }
        } else if (input == 'd' || input == 'D') {
            if (*difficultyselector < (int)difficulties.size() - 1) {
                *difficultyselector += 1;
            } else {
                *difficultyselector = 0;
            }
        } else if (input == (char)KEY_ENTER) {
            break;
        }

        for (int i{ 0 }; i < (int)difficulties.size(); i++) {
            if (i == *difficultyselector) {
                wbkgd(difficulties[i].window, COLOR_PAIR(2));

            } else {
                wbkgd(difficulties[i].window, COLOR_PAIR(1));
            }
            wrefresh(difficulties[i].window);
        }
    }

    // Pick difficulty based on difficulty selector

    refresh();

    getch();

    return 0;
}