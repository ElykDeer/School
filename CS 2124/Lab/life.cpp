/* Author: Kyle Martin
 * 
 * This code was written for the class CS 2124
 * 
 * The purpose of this code is to read a file, 
 *  "life.txt", which is the initial state of 
 *  a board for Conway's Game Of Life, then
 *  the rest is the respective  simulation.
 * 
 * */


#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>
#include <stdlib.h>
using namespace std;


//This function will read the initialBoardState file into a blank 2D vector
void readInitialBoard(const string filename, vector <vector <char>>& initialBoardState);

//This function takes a string reference and turns it into a vector <char>, padded with '#'
vector<char> populateRow(const string& rowString);

//This function will run one cycle on the boardState
void stepBoard(vector <vector <char>>& boardState);

//This function will display the board, boardStaet
void displayBoard(const vector <vector <char>>& boardState);

//Just a thought.. Not working
//This function will clear the board
//void clearBoard(const vector <vector <char>>& boardState);

int main()
{
    //Open file, read file into a 2D vector
    //A 2D vector will store the initialBoardState, and impliment changes each cycle, with a padding of "#" around the boarder
    //vector indexed as boardState[y][x], or boardState[row][col]
    vector <vector <char>> boardState;
    readInitialBoard("life.txt", boardState);
    displayBoard(boardState);
    
    for (int i = 0; i < 50; ++i)
    {
        stepBoard(boardState);
        displayBoard(boardState);
    }
}


//This function will read the initialBoardState file into a blank 2d vector
void readInitialBoard(const string filename, vector <vector <char>>& boardState)
{
    //Open and check filestream
    ifstream initialBoardState(filename);
    if (!initialBoardState)
    {
        cerr<<"The file failed to open.  Closing program/n";
        exit(1);
    }
    
    //Find row length by getting first line, and making a pad of that length+2
    string rowString;
    getline(initialBoardState, rowString);
    vector <char> rowPad(rowString.size()+2, '#');          //Make Pad
    
    //Store that pad as the first row
    boardState.push_back(rowPad);
    
    //Populate first row (since it was already getline'd)
    vector<char> row = populateRow(rowString);
    boardState.push_back(row);                              //Add it to the actual board
    
    //Popluate all rows of the board
    while (getline(initialBoardState, rowString))
    {
        row = populateRow(rowString);                       //Turn each row into a vector
        boardState.push_back(row);                          //Add it to the actual board
    
    }
    boardState[boardState.size()-1] = rowPad;
}


//This function takes a string reference and turns it into a vector <char>, padded with '#'
vector<char> populateRow(const string& rowString)
{
    vector<char> row;
    row.push_back('#');             //Pad
    for (char cell : rowString)     //Populate each character into vector
    {
        row.push_back(cell);
    }
    row.push_back('#');             //Pad
    
    return row;
}


//This function will run one cycle on the boardState
void stepBoard(vector <vector <char>>& boardState)
{
    //Cycle through every element
    for (size_t row = 1; row < boardState.size()-1; ++row)
    {
        for (size_t col = 1; col < boardState[0].size()-1; ++col)
        {
            //Count The  Cells Around It
            int liveNeighborCount = 0;
            if (boardState[row-1][col-1]=='*' || boardState[row-1][col-1]=='d')
                liveNeighborCount+=1;
            if (boardState[row-1][col]=='*' || boardState[row-1][col]=='d')
                liveNeighborCount+=1;
            if (boardState[row-1][col+1]=='*' || boardState[row-1][col+1]=='d')
                liveNeighborCount+=1;
            if (boardState[row][col-1]=='*' || boardState[row][col-1]=='d')
                liveNeighborCount+=1;
            if (boardState[row][col+1]=='*' || boardState[row][col+1]=='d')
                liveNeighborCount+=1;
            if (boardState[row+1][col-1]=='*' || boardState[row+1][col-1]=='d')
                liveNeighborCount+=1;
            if (boardState[row+1][col]=='*' || boardState[row+1][col]=='d')
                liveNeighborCount+=1;
            if (boardState[row+1][col+1]=='*' || boardState[row+1][col+1]=='d')
                liveNeighborCount+=1;
            
            //Mark for birth
            if (liveNeighborCount == 3)
                boardState[row][col] = 'a';
            //Mark for death
            if (liveNeighborCount < 2 && boardState[row][col]=='*')
                boardState[row][col] = 'd';
            if (liveNeighborCount > 3 && boardState[row][col]=='*')            
                boardState[row][col] = 'd';
        }
    }
    //Cycle through every element
    for (size_t row = 1; row < boardState.size()-1; ++row)
    {
        for (size_t col = 1; col < boardState[0].size()-1; ++col)
        {
            if (boardState[row][col]=='a')      //Revive Cells
                boardState[row][col]='*';
            if (boardState[row][col]=='d')      //Kill Cells
                boardState[row][col]='-';
        }
    }
}

//This function will display the board, boardStaet
void displayBoard(const vector <vector <char>>& boardState)
{
    //Loop over rows, and print each element
    for (const vector <char>& row : boardState)
    {
        //Loop over each element
        for (char cell : row)
        {
            if (cell == '-')
                cout <<  ' ';
            else
                cout << cell;
        }
        cout << endl;
    }
}

/*
//This function will clear the board
void clearBoard(const vector <vector <char>>& boardState)
{
    int boardSize = boardState.size()*boardState[0].size();
    //Print Backspaces!!
    char backspace = 12;
    cout << backspace;
    for (int i = 0; i < boardSize; ++i)
    {
        cout << '1';
    }
}*/
