#include "Previous.h"
#include <iostream>

using namespace std;

Previous::Previous(int nRows, int nCols)
    : m_rows(nRows), m_cols(nCols) //Initialize m_rows and m_cols as nRows and nCols respectively with initializer list
{
    for (int row = 0; row < m_rows; row++) {    //Initialize every element in the board to 0
        for (int col = 0; col < m_cols; col++) {
            m_grid[row][col] = 0;
        }
    }
}

bool Previous::dropACrumb(int r, int c)
{
    if (r < 1 || c < 1 || r > m_rows || c > m_cols) //Check if the coordinates are valid
        return false;
    else
    {
        m_grid[r - 1][c - 1]++; //Since coordinate when dropping a crumb is valid increment the element at that coordinate by 1
        return true;
    }

}

void Previous::showPreviousMoves() const 
{
    clearScreen(); //Clears the screen

    for (int row = 0; row < m_rows; row++) {
        for (int col = 0; col < m_cols; col++) { //Loops through all elements/coordinates on the board
            if (m_grid[row][col] == 0) { //If the element/coordinate is 0 print out a period (.)
                cout << '.';
            }
            else {
                if (m_grid[row][col] >= 26) { //If the element/coordinate is greater than or equal to 26 print out Z
                    cout << 'Z';
                }
                else {
                    char out = m_grid[row][col] + 'A' - 1; //Since element/coordinate is less than 26 print out the correct corresponding alphabet
                    cout << out;
                }
            } 
        }
        cout << endl; //To the next row
    }
    cout << endl; //Prints out an empty line after the arena is printed out

}