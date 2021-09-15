#include <iostream>
#include <cstdlib>
using namespace std;
#define N 9

bool SudokuSolver(int grid[N][N]);          //function declaration of main solver
bool findUnassignedLocation(int grid[N][N], int &row, int &column);         //function declaration to find next blank space
bool isValid(int grid[N][N], int row, int column, int num);         //function declaration to check if a number is valid
void displayGrid(int grid[N][N]);           //function declaration of outputting function

int main()
{

    /*
       Initial Grid. Other grids can be inputted into this array. 0's
       must be used to represent blank spaces.
    */

    int grid[N][N] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    cout << "Initial grid (0's are blank spaces): " << endl;            //Displaying the initial unsolved grid
    displayGrid(grid);

    if (SudokuSolver(grid) == true) {               //calls on the display grid funciton if the main solver function returns true
        cout << endl << "Solved: " << endl;
        displayGrid(grid);
    }
    else {                                      //there is no solution if it returns false.
        cout << "There is no solution." <<endl;
    }

    return 0;
}

bool SudokuSolver(int grid[N][N])
{
    int row, column;

    if (findUnassignedLocation(grid, row, column) == false) {           //if there is no more unassigned cells, then the grid should be fully solved
       return true;
    }

    for (int num = 1; num <= 9; num++) {                //loop which runs every number 1 through 9.
        if (isValid(grid, row, column, num) == true) {          //checks if the number fits within its row, column and 3x3 grid
            grid[row][column] = num;            //if it meets all the conditions, then that number can be put in to the grid

            if (SudokuSolver(grid) == true) {
                return true;            //return true if the solver function returns true
            }
            else {
                grid[row][column] = 0;          //erase the current number which is being tried and move on to the next.
            }
        }
    }

    return false;
}

bool findUnassignedLocation(int grid[N][N], int &row, int &column)          //function which looks for any 0's within the array, returns true if it finds a 0, otherwise it returns false
{
    for (row = 0; row < N; row++) {
        for (column = 0; column < N; column++) {
            if (grid[row][column] == 0) {
                return true;
            }
        }
    }

    return false;
}

bool isValid(int grid[N][N], int row, int column, int num)          //checks if the current number which is trying to be inserted into the grid meeds the restriction
{
    for (int columnCheck = 0; columnCheck < N; columnCheck++) {     //checks to see that the current number being tried isn't repeated in the row
        if (grid[row][columnCheck] == num) {
            return false;
        }
    }

    for (int rowCheck = 0; rowCheck < N; rowCheck++) {              //checks to see that the current number being tried isn't repeated in the column
        if (grid[rowCheck][column] == num) {
            return false;
        }
    }

    int boxStartRow = row - row % 3;
    int boxStartcolumn = column - column % 3;

    for (int rowBoxCheck = 0; rowBoxCheck < 3; rowBoxCheck++) {             //checks to see that the current number being tried isn't repeated in the 3by3 grid that it is in
        for (int columnBoxCheck = 0; columnBoxCheck < 3; columnBoxCheck++) {
            if (grid[rowBoxCheck + boxStartRow][columnBoxCheck + boxStartcolumn] == num) {
                return false;
            }
        }
    }

    return true;
}

void displayGrid(int grid[N][N])            //function which displays the grid
{
    for (int row = 0; row < N; row++) {
        for (int column = 0; column < N; column++) {
            cout << grid[row][column] << "  ";
        }

        cout << endl;
    }
}


