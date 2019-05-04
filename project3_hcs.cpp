#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void HCS(int[]);
void generateChild(int[],int);
int numOfAttacks(int[]);
void generateRandom(int[]);
int findIndex(int,int);
void arrCopy(int[],int[]);
void swap(int[],int,int);
void displayBoard(int[]);

int main()
{
    // empty board
    int board[64];
    for (int i = 0; i < 64; i++)
    {
        board[i] = 0;
    }
    
    // generate random board with all 8 queens
    generateRandom(board);
    cout << "Board generated:";
    displayBoard(board);
    
    HCS(board);
    
    if (numOfAttacks(board) > 0)
    {
        cout << "\n\nUnsolved. Peak:";
        displayBoard(board);
        cout << endl << endl;
    }
    
    else
    {
        cout << "\n\nSolved.";
        displayBoard(board);
        cout << endl << endl;
    }
    
    return 0;
}

void HCS(int initialState[])
{
    int current[64]; // initial state at first run
    arrCopy(current, initialState);
    const int MAX = 28;
    int next[64]; // next best state
    int child[64]; // child of current
    
    while (true)
    {
        int min = MAX;
        
        arrCopy(child,current);
        
        int currentQueen = 0;
        
        for (int i = 0; i < 56; i++) // for each child
        {
            generateChild(child, currentQueen);
            
            int attacks = numOfAttacks(child);
            
            if (attacks < min)
            {
                min = attacks;
                arrCopy(next,child);
            }
            
            // update current queen
            if (i % 7 == 6) // after 7 runs
            {
                // move queen back to original place
                generateChild(child, currentQueen);
                
                // change queen
                currentQueen++;
            }
        }
        
        if (min >= numOfAttacks(current))
        {
            arrCopy(initialState,current); // copied to IS to be accessed in main
            break; // exit while loop
        }
        
        arrCopy(current,next);
    }
}

void generateChild(int board[], int currentQueen) // currentQuenn = column number of queen
{
    int currentRow;
    
    for (int i = 0; i < 8; i++) // check rows for queen
    {
        if (board[findIndex(i,currentQueen)] == 1)
        {
            currentRow = i;
            break;
        }
    }
    
    if (currentRow < 7)
    {
        // move queen
        swap(board, findIndex(currentRow,currentQueen), findIndex(currentRow + 1,currentQueen));
    }
    
    else if (currentRow == 7) // last row
    {
        // move queen to top row
        swap(board, findIndex(currentRow,currentQueen), findIndex(0,currentQueen));
    }
}

int numOfAttacks(int board[])
{
    // get indexes of queens
    int index[8];
    int indexPos = 0;
    
    for (int i = 0; i < 64; i++)
    {
        if (board[i] == 1)
        {
            index[indexPos] = i;
            indexPos++;
        }
    }
    
    // check row attacks
    int rowAttacks = 0;
    
    for (int i = 0; i < 7; i++) // choose queen
    {
        for (int j = i + 1; j < 8; j++) // check occurances
        {
            if ((index[i] / 8) == (index[j] / 8)) // if rows are equal
                rowAttacks++;
        }
    }
    
    // check all diagonal attacks (major + minor)
    int row1, row2, col1, col2, diagAttacks = 0;
    
    for (int i = 0; i < 7; i++) // choose queen
    {
        row1 = index[i] / 8;
        col1 = index[i] % 8;
        
        for (int j = i + 1; j < 8; j++) // compare to rest
        {
            row2 = index[j] / 8;
            col2 = index[j] % 8;
            
            if (abs(row1 - row2) == abs(col1 - col2))
                diagAttacks++;
        }
    }
    
    return rowAttacks + diagAttacks;
}

void generateRandom(int board[])
{
    int t = (unsigned int)time(0);
    srand(t);
    int r;
    
    for (int i = 0; i < 8; i++)
    {
        r = rand() % 8; // choose random row for each column
        
        for (int j = 0; j < 8; j++)
        {
            if (j == r)
                board[findIndex(j, i)] = 1;
        }
    }
}

int findIndex(int row, int col)
{
    int index = 0;
    index += (row * 8);
    index += col;
    
    return index;
}

void arrCopy(int arr1[], int arr2[])
{
    for (int i = 0; i < 64; i++)
    {
        arr1[i] = arr2[i];
    }
}

void swap(int board[], int index1, int index2)
{
    if (board[index1] == 0)
    {
        board[index1] = 1;
        board[index2] = 0;
    }
    else if (board[index1] == 1)
    {
        board[index1] = 0;
        board[index2] = 1;
    }
}

void displayBoard(int board[])
{
    for (int i = 0; i < 64; i++)
    {
        if (i % 8 == 0)
            cout << endl;
        
        if (board[i] == 0)
            cout << "- ";
        
        else if (board[i] == 1)
            cout << "Q ";
    }
}
