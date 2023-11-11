#include <main.hxx>
#include <grid.hxx>

class SmartPtr
{
    int* ptr; // Actual pointer
  public:
    // Constructor: Refer https:// www.geeksforgeeks.org/g-fact-93/
    // for use of explicit keyword
    explicit SmartPtr(int* p = NULL) { ptr = p; }

    // Destructor
    ~SmartPtr() { delete (ptr); }

    // Overloading dereferencing operator
    int& operator*() { return *ptr; }
};



int
main()
{
    gridSmall grdid;
    grdid.initialize();
    grdid.generateMines();
    grdid.print();

    return 0;

}