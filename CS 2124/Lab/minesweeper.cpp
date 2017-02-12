/* Author: Kyle Martin
 * 
 * This code was written for the class CS 2124
 * 
 * This is a text-based version of minesweeper!
 *  Enjoy!
 * 
 * Known errrs:
 *   Crash on board out of bounds requests
 *   Crash on letter input where there should be numbers
 *   Crash on spaces where they're shouldn't be
 *   
 * 
 * */

#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <sstream>
#include <time.h>
using namespace std;


//This character will probably display a question mark, but might display
  //a texture of dots, either way, it represents an "untouched" tile
static string QUESTION = "#";

//Let's get color's working
  //Color codes:
static int NORMAL   = -30;
static int NEGATIVE = -23;
static int RED      = 1;
static int GREEN    = 2;
static int YELLOW   = 3;
static int BLUE     = 4;
//For colors in such a way that it doesn't break compilation/print garbage (On windows, namely)
#ifdef _WIN32
void startPaint(const int color) {}
void endPaint() {}
#else
void startPaint(const int color)
{
    cout << "\033[" << color+30 << "m";
}
void endPaint()
{
    cout << "\033[0m";
}
#endif


//This will hold the boad, as a matrix of tiles
class Board
{
public:
    explicit Board() //Create the default board, 
    {
        createBoard();
    }
    
    //This is the board customization process, called by the Customize command
    void customizeBoard()
    {
        //Clear the old board
        gameBoard.clear();
        
        //ector <vector <Tile>> newGameBoard;
        //gameBoard = newGameBoard;
        
        //Inofrm the user what they're doing:
          //"Animate" screen, promt user, erro check, repeat if error
        int newRowsNum = 0;
        while (!(newRowsNum < 21) || !(newRowsNum > 0))
        {
            clearScreen();
            cout << " Baord Size Selection:\n\n  Select Number of Rows (1-20)\n";
            cout << "                        (    )\b\b\b\b";
            cin >> newRowsNum;
        }
        
        //"Animate" screen, promt user, erro check, repeat if error
        int newColsNum = 0;
        while (!(newColsNum < 41) || !(newColsNum > 0))
        {
            clearScreen();
            
            //Print Rows, give the user a visual representation of what they're getting in to
            for (int rowIndex = 0; rowIndex < newRowsNum; ++rowIndex)
            {
                startPaint(YELLOW);
                cout << " R" << rowIndex+1 << '\t';
                startPaint(BLUE);
                cout << QUESTION << endl;
                endPaint();
            }
            
            //Prompt user for number of columns
            cout << " Baord Size Selection:\n\n  Select Number of Columns (1-40)\n";
            cout << "                           (    )\b\b\b\b";
            cin >> newColsNum;
        }
        
        //"Animate" screen, promt user, erro check, repeat if error
        difficulty = -1;
        while (!(difficulty < 101) || !(difficulty > -1))
        {
            clearScreen();
            
            //Print board pretty: Yellow row/col numbers, blue tiles
            for (int rowIndex = 0; rowIndex <= newRowsNum; ++rowIndex)
            {
                startPaint(YELLOW);
                
                //This if block is because the first row is column indexes
                if (rowIndex > 0)
                    cout << " R" << rowIndex << '\t';
                else
                    cout << " C: \t";
                for (int colIndex = 0; colIndex < newColsNum; colIndex++)
                {
                    if (rowIndex < 1) //First row is column numbers
                        cout << (colIndex+1)%10;
                    else
                    {
                        startPaint(BLUE);
                        cout << QUESTION;
                        endPaint();
                    }
                 }
                 cout << endl; //End of row newline
            }
            cout << "\n  Select Difficulty (0-100) : (No Bombs - All Bombs)\n";
            cout << "                         (     )\b\b\b\b\b";
            cin >> difficulty;
        }
        
        //Create the board
        createBoard(newRowsNum, newColsNum, difficulty);
    }
    
    
    //This will count all the bombs near all tiles, and populate the appropriate feilds
    void countBombs()
    {
        //Loop through all tiles and reveal bombs
        for (size_t row = 0; row < gameBoard.size(); ++row)
            for (size_t col = 0; col < gameBoard[0].size(); ++col)
                for (int rowOffset = -1; rowOffset < 2; ++rowOffset) //Loop through my eight neighbors
                    for (int colOffset = -1; colOffset < 2; ++colOffset)
                    {
                        if ((row + rowOffset >= gameBoard.size()) ||  (row + rowOffset < 0) ||
                            (col + colOffset >= gameBoard[0].size() || (col + colOffset < 0))) //If I'm out of bounds, leave
                                continue;
                        else if (gameBoard[row + rowOffset][col + colOffset].isBomb()) //If my neighbor is a bumb, add to my count
                            gameBoard[row][col].nearBy(); //Inc my nearBy counter
                    }
    }
    
    
    //This function creates and populates the board
    void createBoard(int rows = 10, int cols = 20, int difficulty = 10)
    {
        //Create And Populate Board
        //Create rows, not populated
        vector<Tile> rowVector;
        for (int r = 0; r < rows; ++r)
            gameBoard.push_back(rowVector);
         
        //Create cols, initalize bombs states
          //Diificulty number serves as the percentage for bomb chances:
          //bool isBomb = (rand() %101 + 1 > difficulty)
        for (vector <Tile>& row : gameBoard)
            for (int c = 0; c < cols; ++c)
                row.push_back(Tile((rand() %100 + 1 <= difficulty))); //Algorithm for calculating if it's a bomb or not
        
        //Populate "near me"        
        countBombs();
    }
    
    
    //Print the board! Tile by tile, with fancy colors
    void print() const
    {
        //A lot of fancy formating... Cylces through all rows and cols, canges colors
        for (size_t row = 0; row <= gameBoard.size(); ++row)
        {
            startPaint(YELLOW);
            if (row > 0) //First row is column headers
                cout << " R" << row << '\t';
            else
                cout << " C: \t";
            for (size_t col = 0; col < gameBoard[0].size(); col++)
            {
                if (row < 1) //First row is column headers
                    cout << (col+1)%10;
                else
                {
                    gameBoard[row-1][col].print();
                }
             }
             startPaint(YELLOW); //Rihgt-side number reference
             if (row > 0) //First row is column headers
                cout << " R" << row;
             endPaint();
             cout << endl; //End of row newline
        }
        //Print second reference on bottom
        startPaint(YELLOW);
        cout << '\t';
        for (size_t col = 0; col < gameBoard[0].size(); col++)
            cout << (col+1)%10;
        endPaint();
        cout << endl << endl;
    }
    
    //"Animates" the screen by printing a bunch of newline
    void clearScreen() const
    {
        for (int i = 0; i < 100; ++i)
            cout << endl;
        return;
    }
 
    //Flag will put a flag on a bomb by caling that tile's flag function
    void flag(int row, int col)
    {
        gameBoard[row-1][col-1].flagTile();
    }
    
    //Touch will "guess" a tile, and reveal it
    void touch(int row, int col)
    {
        //Convert user coodinates to computer coodinates
        row -= 1;
        col -= 1;
        
        //Ignore stumbles.. Touching flags or already cleared tiles
        if (gameBoard[row][col].isFlagged() || gameBoard[row][col].isRevealed())
            return;
        //If you touch a bomb, you die
        else if (gameBoard[row][col].isBomb())
        {
            alive = false;
            revealAll();
        }
        else  //if it's not a bomb, show what it is
            recReveal(row, col);
    }
    
    //This recursively reveals all non-bomb tiles around a given tile - needs starting position
    void recReveal(size_t rowStart, size_t colStart)
    {
        //Reveal me
        gameBoard[rowStart][colStart].reveal();
        
        for (int rowOffset = -1; rowOffset < 2; ++rowOffset) //Loop through my nine neighbors
            for (int colOffset = -1; colOffset < 2; ++colOffset)
            {
                if ((rowStart + rowOffset >= gameBoard.size()) ||  (rowStart + rowOffset < 0) ||
                    (colStart + colOffset >= gameBoard[0].size() || (colStart + colOffset < 0))) //If I'm out of bounds, leave
                        continue;
                //Doesn't reveal revealed tiles or bombs
                if (gameBoard[rowStart + rowOffset][colStart + colOffset].isBomb() ||
                    gameBoard[rowStart + rowOffset][colStart + colOffset].isFlagged() ||
                    gameBoard[rowStart + rowOffset][colStart + colOffset].isRevealed() )
                        continue;
                else if (gameBoard[rowStart][colStart].isClose())
                        continue;
                else  //if it's not a bomb, show what it is
                    recReveal(rowStart+rowOffset, colStart+colOffset);
            }
    }
    
    //Checks if the game has been lost
    bool isAlive() const
    {
        return alive;
    }
    
    //Checks if the game has been lost
    bool hasWon() const
    {
        //If there is a tile that is not a bomb and it hasn't been revealed, no win
        for (const vector <Tile>& row : gameBoard)
            for (const Tile& tile : row)
                if (!tile.isBomb() && !tile.isRevealed())
                    return false;
        return true;
    }
private:
    //Show all Bomb locations.
    void revealAll()
    {
        //Loop through all tiles and reveal bombs
        for (vector <Tile>& row : gameBoard)
            for (Tile& tile : row)
                if (tile.isBomb())
                    tile.reveal();
        //redisplay board
        clearScreen();
        print();
    }

    class Tile
    {
        public:
            explicit Tile(bool isbomb) : bomb(isbomb) { } //Constructor where one can set if the tile is a bomb or not
            
            //Inc number of bombs
            void nearBy()
            {
                nearByBombs+=1;
            }
            
            bool isClose() const
            {
                return (nearByBombs > 0);
            }
            
            //Print an indevidual tile, colored and formated just right
            void print() const
            {
                //If it's revealed, show it's bomb, it's nearby, or a space if no neadby
                if (revealed)
                {
                    if (bomb) //If this tile is a bomb
                    {
                        startPaint(NORMAL); //Reset colors
                        startPaint(NEGATIVE);
                        cout << '@';
                        endPaint();
                    }
                    else if (nearByBombs == 0) //If this is an "open" tile - nothing near it
                        cout << ' ';
                    else  //If this tile is near a bomb! 
                    {
                        startPaint(RED);
                        cout << nearByBombs;
                        endPaint();
                    }
                }
                else if (flag) //Or Display a red exclamation if the tile is flagged
                {
                    startPaint(RED);
                    cout << '!';
                    endPaint();
                }
                else //Has to be hidden, display default character "QUESTION"
                {
                    startPaint(BLUE);
                    cout << QUESTION;
                    endPaint();
                }
            }
            
            //Called when touching, to make sure the user is not being dumb
            bool isFlagged() const
            {
                return flag;
            }
            
            //Called through the flag command, will flag a tile with a '!'
            void flagTile()
            {
                flag = !flag;
            }
            
            //Checks if this tile is a bomb, used for counting bombs and when a bomb is touched
            bool isBomb() const
            {
                return bomb;
            }
            
            //Checks if a tile is revealed, used when recursively showing all open tiles next to the one pressed
            bool isRevealed() const
            {
                return revealed;
            }
            
            //Reveals a tile, used when revealing all bombs (loss condition) and touching a tile
            void reveal()
            {
                revealed = true;
            }
            
        private:
            //The data only needs to hold how many other bombs are close to it, if it's a bomb, and if it should be displayed
            short nearByBombs = 0;
            bool bomb;
            bool revealed = false;
            bool flag = false;
    };


    //This is where our game will live
      //indexed gameBoard[row][col]
    vector <vector <Tile>> gameBoard;
    //Will affect bomb placement
    int difficulty = 10;
    bool alive = true;
};


//Only two non-class function protypes:
//This function will interpret commands and call the appropriate functions!
void interpretCommand(const string& commandString, Board& world);
//This is the help command
void help();


int main()
{
    //I want to make it so this can run forever, but not right now..
    string command;
    help();
    
    //Initialize Random bombs!
    srand(time(NULL));
    
    Board world;
    
    //Main loop
    while (command != "Quit")
    {
        while ((command != "Quit") && (command != "Help"))
        {
            interpretCommand(command, world);
            
            //Display the world
            world.clearScreen();
            world.print();
            
            if (!world.isAlive())
            {
                endPaint();
                startPaint(RED);
                cout << "\n\n Congrats! You've lost!\n\n";
                command = "Quit";
                endPaint();
                continue;
            }
            else if (world.hasWon())
            {
                endPaint();
                startPaint(GREEN);
                cout << "\n\n Congrats! You've won!\n\n";
                command = "Quit";
                endPaint();
                continue;
            }
            
            //Prompt User
            startPaint(GREEN);
            cout << "  Command : ";
            endPaint();
            getline(cin, command);
            //Option to just type in r/c and auto touch
            if (command.size() < 7 && command.size() > 3 && !(command == "Quit") && !(command == "Help"))
                command = "touch " + command;
        }
        if (command == "Help")
        {
            help();
            command = "";
        }
    }
}


//This function will interpret commands and call the appropriate functions!
void interpretCommand(const string& commandString, Board& world)
{
    //Need to break command up into parts
    istringstream commandStream(commandString);
    
    //This will be the command 'type' (touch vs flag)
    string commandName;
    commandStream >> commandName;
    
    if (commandName == "Customize")
    {
        world.customizeBoard();
        return;
    }
    
    //Used in the next few blocks
    int row, col;
    char identifier;
    
    //Loop twice and determine the row/col nums
    for (int i=0; i<2; ++i)
    {
        commandStream >> identifier;
        if (identifier == 'C' || identifier == 'c')
            commandStream >> col;
        else if (identifier == 'R' || identifier == 'r')
            commandStream >> row;
        else
            return; //Invalid input
    }
    
    //Determine which command is being invoked, and run that command
    if (commandName == "Flag" || commandName == "flag")
        world.flag(row, col);
    else if (commandName == "Touch" || commandName == "touch")
        world.touch(row, col);
    
}


//This is the help command
void help()
{
    cout << "\n This is minesweeper. You know how to play.\n\n";
    startPaint(BLUE);
    cout << " Commands:\n  Touch: ";
    endPaint();
    cout << "(ie 'Touch r2C2') will touch the Row and Col specified\n";
    startPaint(BLUE);
    cout << "  Flag:  ";
    endPaint();
    cout << "(ie 'Flag c2R2')  will toggle the flag at the Row and Col specified\n";
    startPaint(BLUE);
    cout << "  Customize: ";
    endPaint();
    cout << "Run board customization script\n";
    startPaint(BLUE);
    cout << "  Help: ";
    endPaint();
    cout << "Will display this menu\n";
    startPaint(BLUE);
    cout << "  Quit: ";
    endPaint();
    cout << "Will quit the game\n\n";
    startPaint(RED);
    cout << " Row/Col indetifiers with no command are interpreted as touch commands\n\n";
    startPaint(YELLOW);
    cout << " Press enter to continue...\n\n";
    string ignore;
    getline(cin, ignore);
}
