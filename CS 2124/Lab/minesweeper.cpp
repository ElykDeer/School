/* Author: Kyle Martin
 * 
 * This code was written for the class CS 2124
 * 
 * This is a text-based version of minesweeper!
 *  Enjoy!
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


//Let's get color's working
//For colors in such a way that it doesn't break compilation/print garbage
/* Short Color Reference:
 * -30 - Normal
 * -25 - Blink
 * 1 - Red
 * 2 - Green
 * 3 - Yellow
 * 4 - Blue
 */
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
    explicit Board()
    {
        createBoard();
    }
    
    void custom()
    {
        vector <vector <Tile>> newGameBoard;
        gameBoard = newGameBoard;
        
        //Inofrm the user what they're doing:
        //Clear the screen for uniform input, and keep doing it until they answer right
        int rows;
        while (!(rows < 21) || !(rows > 0))
        {
            clear();
            cout << " Baord Size Selection:\n\n  Select Number of Rows (1-20)\n";
            cout << "                        (    )\b\b\b\b";
            cin >> rows;
        }
        
        //Clear the screen for uniform input, and keep doing it until they answer right
        int cols;
        while (!(cols < 21) || !(cols > 0))
        {
            clear();
            //Print Rows
            for (int r = 0; r < rows; ++r)
            {
                startPaint(3);
                cout << " R" << r+1 << '\t';
                startPaint(4);
                cout << unknownTile << endl;
                endPaint();
            }
            cout << " Baord Size Selection:\n\n  Select Number of Columns (1-20)\n";
            cout << "                           (    )\b\b\b\b";
            cin >> cols;
        }
        
        //Clear the screen for uniform input, and keep doing it until they answer right
        while (!(difficulty < 101) || !(difficulty > -1))
        {
            clear();
            //Print board pretty
            for (int r = 0; r <= rows; ++r)
            {
                startPaint(3);
                if (r > 0)
                    cout << " R" << r << '\t';
                else
                    cout << " C: \t";
                for (int c = 0; c < cols; c++)
                {
                    if (r < 1)
                        cout << (c+1)%10;
                    else
                    {
                        startPaint(4);
                        cout << unknownTile;
                        endPaint();
                    }
                 }
                 cout << endl;
            }
            cout << "\n  Select Difficulty (0-100) : (No Bombs - All Bombs)\n";
            cout << "                         (     )\b\b\b\b\b";
            cin >> difficulty;
        }
        
        //Create the board
        createBoard(rows, cols, difficulty);
    }
    
    
    //This will count all the bombs near all tiles, and populate the appropriate feilds
    void countBombs()
    {
        //Loop through all tiles and reveal bombs
        for (size_t row = 0; row < gameBoard.size(); ++row)
            for (size_t col = 0; col < gameBoard[0].size(); ++col)
                for (int rowOffset = -1; rowOffset < 2; ++rowOffset) //Loop through my nine neighbors
                    for (int colOffset = -1; colOffset < 2; ++colOffset)
                        if (rowOffset != 0 || colOffset != 0)
                        {
                            if ((row + rowOffset >= gameBoard.size()) ||  (row + rowOffset <= 0) ||
                                (col + colOffset >= gameBoard[0].size() || (col + colOffset <= 0)))
                                {
                                                            cout << "row " << row << " col " << col << " rowOffset " << rowOffset << " colOffset " << colOffset << endl;
                                                            continue;

                                }
                            else if (gameBoard[row + rowOffset][col + colOffset].isBomb())
                                gameBoard[row][col].nearBy();
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
                row.push_back(Tile((rand() %101 + 1 < difficulty)));
        
        //Populate "near me"        
        countBombs();
    }
    
    
    void print() const
    {
        //A lot of fancy formating... Cylces through all rows and cols
        for (size_t row = 0; row <= gameBoard.size(); ++row)
        {
            startPaint(3);
            if (row > 0)
                cout << " R" << row << '\t';
            else
                cout << " C: \t";
            for (size_t col = 0; col < gameBoard[0].size(); col++)
            {
                if (row < 1)
                    cout << (col+1)%10;
                else
                {
                    gameBoard[row-1][col].print();
                }
             }
             cout << endl;
        }
        cout << endl;
    }
    
    void clear() const
    {
        for (int i = 0; i < 30; ++i)
            cout << endl;
        return;
    }
 
    //Flag will put a flag on a bomb
    void flag(int row, int col)
    {
        cout << "R" << row << "C" << col << endl;
        gameBoard[row-1][col-1].flag();
    }
    
    //Touch will "guess" a tile, and reveal it
    void touch(int row, int col)
    {
        //If you touch a bomb, you die
        if (gameBoard[row-1][col-1].isBomb())
        {
            alive = false;
            revealAll();
        }
        else  //if it's not a bomb, show what it is
            gameBoard[row-1][col-1].reveal();
    }
    
    bool isAlive()
    {
        return alive;
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
        clear();
        print();
    }

    class Tile
    {
    public:
        explicit Tile(bool isbomb) : bomb(isbomb) { }
        
        //Inc number of bombs
        void nearBy()
        {
            nearByBombs+=1;
        }
        
        void print() const
        {
            //If it's revealed, show it's bomb, it's nearby, or a space if no neadby
            if (revealed)
            {
                if (bomb)
                {
                    endPaint();
                    startPaint(-23);
                    cout << '@';
                    endPaint();
                }
                else if (nearByBombs == 0)
                    cout << ' ';
                else
                {
                    startPaint(1);
                    cout << nearByBombs;
                    endPaint();
                }
            }
            else //Or display that it's hidden
            {
                startPaint(4);
                cout << display;
                endPaint();
            }
        }
        
        void flag()
        {
            display = '!';
        }
        
        bool isBomb()
        {
            return bomb;
        }
        
        bool isRevealed()
        {
            return revealed;
        }
        
        void reveal()
        {
            revealed = true;
        }
        
    private:
        //The data only needs to hold how many other bombs are close to it, if it's a bomb, and if it should be displayed
        short nearByBombs = 0;
        bool bomb;
        bool revealed = false;
        //This prints a default questionmark on my screen, but might print a dotty pattern on others, either way, I like it
        //I will change this to a space ' ' after the character reveals it, if not a bomb number or a bomb
        char display = 178;
    };

    //This is where our game will live
      //indexed gameBoard[row][col]
    vector <vector <Tile>> gameBoard;
    //Will affect bomb placement
    int difficulty = -100;
    
    //This prints a questionmark on my screen, but might print a dotty pattern on others, either way, I like it
    char unknownTile = 178;
    
    bool alive = true;
};


//This function will interpret commands and call the appropriate functions!
void interpretCommand(const string& commandString, Board& world);

//This is the help command
void help();


int main()
{
    //Initialize Random bombs!
    srand(time(NULL));
    
    Board world;

    string command;
    
    //Main loop
    while (command != "Quit")
    {
        while ((command != "Quit") && (command != "Help"))
        {
            interpretCommand(command, world);
            
            //Display the world
            world.clear();
            world.print();
            
            if (!world.isAlive())
            {
                cout << "\n\n Congrats! You've lost!";
                command = "Quit";
                continue;
            }
            
            //Prompt User
            startPaint(2);
            cout << "  Command : ";
            endPaint();
            getline(cin, command);
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
        world.custom();
        return;
    }
    
    //Loop twice and determine the row/col nums
    int row, col;
    char identifier;
    for (int i=0; i<2; ++i)
    {
        commandStream >> identifier;
        if (identifier == 'C' || identifier == 'c')
            commandStream >> col;
        if (identifier == 'R' || identifier == 'r')
            commandStream >> row;
    }
    
    //Determine which command is being invoked, and run that command
    if (commandName == "Flag")
        world.flag(row, col);
    else if (commandName == "Touch")
        world.touch(row, col);
    
}


//This is the help command
void help()
{
    cout << "\n This is minesweeper. It's not rocket science. You know how to play.\n\n Commands:\n";
    cout << " Touch: (ie 'Touch R2C2') will touch the Row and Col specified (in either order)\n";
    cout << " Flag:  (ie 'Flag R2C2')  will flag  the Row and Col specified (in either order)\n";
    cout << " Customize: Run board customization script\n\n";
    cout << " Press enter to continue...\n\n";
    string ignore;
    getline(cin, ignore);
}
