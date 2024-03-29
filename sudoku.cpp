// Practice.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// CURRENTLY NOT WORKING

//#include "pch.h"

#include <iostream>
#include <vector>
#include <bitset>


using namespace std;



// Rules:
// Board is 9x9
// Each row has #1-9, each digit once
// Each column has #1-9, each digit once
// Each 3x3 square contains #1-9, each digit once
// ==> Each 3x3 square also has unique digits in each row/column



bool my_isdigit(char ch)
{
    return (isdigit(static_cast<unsigned char>(ch)) && (ch != '0'));
}


bool isValid(const vector<string> &A, int x, int y, bitset<9> &rowmask)
{
    // A is the 9x9 board
    // x,y the top left corner of a 3x3 square
    // rowmask used to track unique digits across 3x3 rows
    // rowmask also tracks unique digits across full rows between calls

    //cout << " x=" << x << "; y=" << y;

    for (int i = 0; i < 3; ++i)
    {
        //cout << " i=" << i; 

        for (int j = 0; j < 3; ++j)
        {
            //cout << "; j=" << j; 

            char ch = A[x + j][y + i];

            // OK to have empty cells
            if (ch == '.')
            {
                continue;
            }
            else if (!my_isdigit(ch))
            {
                //cout << "; ch=" << ch << "; my_isdigit=FALSE\n" << endl;
                return false;
            }

            // verify same digit not already set in same row
            int digit = (ch - '0');
            if (rowmask.test(digit - 1))
            {
                // dupe
                //cout << " i=" << i; 
                //cout << "; j=" << j; 
                //cout << "\nDUPE: digit=" << digit << "; rowmask=" << rowmask;
                return false;
            }
            // set this cell's value in rowmask
            rowmask.set(digit - 1);
        }
    }
}

int isValidSudoku(const vector<string> &A)
{
    if (A.size() < 9 || A[0].size() < 9)
    {
        return 0;
    }

    // evaluate each 3x3 square
    // i,j represents the top left cell (feffective 0,0)
    for (int i = 0; i < 9; i += 3)
    {
        // rowmask: validates unique digits in each row, and across 3x3's
        bitset<9> rowmask;
        rowmask.reset();

        for (int j = 0; j < 9; j += 3)
        {
            if (!isValid(A, j, i, rowmask))
            {
                return 0;
            }
        }
    }

    // validate columns

    return 1;
}

int main()
{
    vector<string> v = { 
        "..5.....6", 
        "....14...", 
        ".........", 
        ".....92..", 
        "5....2...", 
        ".......3.", 
        "...54....", 
        "3.....42.", 
        "...27.6.." };
    
    cout << "isValid = " << isValidSudoku(v);
    return 0;
}
