#ifndef PREVIOUS_H
#define PREVIOUS_H

#include "globals.h"

class Previous
{
    public:
        Previous(int nRows, int nCols);
        bool dropACrumb(int r, int c);
        void showPreviousMoves() const;

    private:
        int m_grid[MAXROWS][MAXCOLS];
        int m_rows; 
        int m_cols; 
};

#endif // PREVIOUS_H