/* Author: Kyle Martin
*
* This code was written for the class CS 2124
*
* This code builds off the three previos
*  assignments, hw2-4.s
*
* The purpose of this code is to read a file,
*  "commandFile.txt", which is a set of
*  commands, one on each line, and run a
*  "battle simulation".  The commands
*  supported are listed below.
*
* Quoted from the spec:
*
* """
* Noble. Create a Noble on the heap.
*
* Warrior. Create a Warrior on the heap.
*
* Hire. Call the Noble's hire method.
*
* Fire. Call the Noble's fire method.
*
* Battle. Call the Noble's battle method.
*
* Status. The status command shows the nobles,
*  together with their armies, in a similar
*  way that the Noble display method did in
*  hw03. In addition, it will show the warriors
*  who do not have an employer, either because
*  they were fired or never hired.
*
* Clear. Clear out all the nobles and warriors
*  that were created
* """
*
* Everything is contained within the Gamestate
*  class, allowing for minimal work for the user,
*  but also hiding the majority of the internals
*  from them as well
*
* */

#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

//THis class is how to interface with the world/game
class GameState
{
public:
    ~GameState()
    { clear(); /* clear the heap */ }

    //The Seven specified commands:
    bool addNoble(const string& newNobleName)
    {
        if (nobleExists(newNobleName))
            return false;

        theNobles.push_back(new Noble(newNobleName));
        return true;
    }

    bool addWarrior(const string& newWarriorName, const int strength)
    {
        if (warriorExists(newWarriorName))
            return false;

        theRabble.push_back(new Warrior(newWarriorName, strength));
        return true;
    }

    bool nobleHireWarrior(const string& nobleName, const string& warriorName)
    {
        //Ensure that both parties already exist
        Noble* employer;
        Warrior* employee;
        if (!(employer = nobleExists(nobleName)) || !(employee = warriorPick(warriorName)))
            return false;

        //Run command, return command's state
        //Since this is non-user code, this one is different as to not redo work
        //(works by object, not by name)
        return employer->hire(*employee);
    }

    bool nobleFireWarrior(const string& nobleName, const string& warriorName)
    {
        //Ensure that the warrior exists
        Noble* employer;
        if (!(employer = nobleExists(nobleName)))
            return false;

        //Fire the guy, if the warrior owns him (internally checked)
        Warrior* employee;
        if (!(employee = employer->fire(warriorName)))
            return false;

        //Add the warrior back to be hired
        theRabble.push_back(employee);
        return true;
    }

    bool battle(const string& nobleOneName, const string& nobleTwoName)
    {
        //Ensure that both parties already exist
        Noble *nobleOne, *nobleTwo; //Tow Noble pointers
        if (!(nobleOne = nobleExists(nobleOneName)) || !(nobleTwo = nobleExists(nobleTwoName)))
            return false;

        //Call the battle command
        nobleOne->battle(*nobleTwo);
        return true;
    }

    void status() const
    {
        //Check if anyone exists
        if ((theNobles.size() == 0) && (theRabble.size() == 0))
            cout << "No Nobles or Warriors yet exist.";
        else if (theNobles.size() == 0)
            cout << "No Nobles yet exist.";
        else
        {
            //If they exist, display The Nobles (which will list their men)
            for (const Noble* noble : theNobles)
                noble->display();

            //List those who are unemployed, if any.
            if (theRabble.size() != 0)
            {
                cout << "\nUnempolyed:";
                for (const Warrior* warrior : theRabble)
                    cout << " " << warrior->getName();
            }
        }
        cout << endl << endl; //Seperate this block of text
    }

    void clear()
    {
        //Clear the heap
        for (Warrior* inspect : theRabble)
            delete inspect;
        for (Noble* inspect : theNobles)
            delete inspect;

        //Clear the vectors now containing hanging pointers
        theRabble.clear();
        theNobles.clear();
    }

private:
    //The Warrior Class -- based on the warrior struct from the previous class
    class Warrior
    {
    public:
        Warrior(const string& warriorName, const int strength): name(warriorName),
        strength(strength) {}

        //Cute little display method - nothing complicated
        void display() const
            { cout << name << " of power " << strength << ".\n"; }

        string getName() const
            { return name; }

        int getStrength() const
            { return strength; }

        //For when they fight, they get damage distributed to them (they're told
        //how much more they have to live).
        void damage(const double percentLeftAlive)
            { strength *= percentLeftAlive; }

    private:
        string name;
        double strength;
    };

    //This class is our nobles - who fight and drink
    class Noble
    {
    public:
        //Nobles haave names but don't start with armies
        Noble(const string& name): name(name) {}

        //They drink
        void drink() const
            { cout << "Cheers!\n"; }

        //Get warriors!
        //Since this is non-user code, this one is different as to not redo work
        //(works by object, not by name) - the calle checks that both exist
        bool hire(Warrior& newBlood)
        {
            if (owns(newBlood.getName())) //Make sure not already 'owned'
                return false;
            army.push_back(&newBlood);
            return !(nullptr == owns(newBlood.getName())); //Make sure it worked, convert to bool
        }

        //Get rid of warriors
        Warrior* fire(const string& firedBlood)
        {
            //Make sure we have the warrior we're told that we're firing
            //(modified from owns)
            Warrior* firedWarrior = nullptr;
            for (Warrior*& inspect : army)
                if (inspect->getName() == firedBlood)
                {
                    firedWarrior = inspect;
                    inspect = army[army.size()-1]; //Overwire inspect
                    army.pop_back(); //Get rid of the duplicate
                }
            if (!firedWarrior)
                return firedWarrior;

            //Announce what's happening..
            cout << firedBlood << " you are dishonerably excused from service!\n";
            return firedWarrior;
        }

        //The Battle command (as a function)
        void battle(Noble& enemy)
        {
            //Announce
            cout << name << " battles " << enemy.name << "!\n";

            //Gather collective strengths
            double myStrength = getStrength();
            double enemyStrength = enemy.getStrength();

            //check if they're already dead
            if (myStrength == 0 || enemyStrength == 0)
            {
                if (myStrength == 0 && enemyStrength == 0)
                    { cout << name << " and " << enemy.name << " are both dead!!"; }
                else if (myStrength == 0)
                    { cout << name << " is dead!"; }
                else if (enemyStrength == 0)
                    { cout << enemy.name << " is dead!"; }
                cout << endl << endl;
                return;
            }

            //Battle it out and assign damage
            const double deathMultiplier = 0; //If someone dies, this is what their death looks like
            if (myStrength == enemyStrength)
            {
                cout << "Mutual Annihalation: " << name << " and " << enemy.name <<
                        " both die at each other's hands.";
                damage(deathMultiplier);
                enemy.damage(deathMultiplier);
            }
            else if (myStrength < enemyStrength)  //They win
            {
                cout << enemy.name << " defeats " << name << "!";
                damage(deathMultiplier);
                enemy.damage(myStrength/enemyStrength);
            }
            else if (myStrength > enemyStrength) //I win!
            {
                cout << name << " defeats " << enemy.name << "!";
                enemy.damage(deathMultiplier);
                damage(enemyStrength/myStrength);
            }

            cout << endl << endl; //Seperate block of text for visuals
        }

        //The Status command (also displays their warriors)
        void display() const
        {
            //Show off the Noble
            cout << "\n" << name << " has an army of " << army.size() << "!\n";

            //Print all warriors
            for (Warrior* inspect : army)
            {
                cout << "\t"; //Indent block below the Nobel's name
                inspect->display();
            }
        }

        string getName() const
            { return name; }

    private:
        //Determine the army's collective strength - for battle
        int getStrength() const
        {
            int totalStrength = 0;
            //Add up everyones strength
            for (Warrior* inspect : army)
                { totalStrength += inspect->getStrength(); }

            return totalStrength;
        }

        //Distribute damage to the warriors from battle
        //Simply multiply percentDamaged by current strength
        void damage(const double percentLeftAlive)
        {
            //Damage all warriors
            for (Warrior* inspect : army)
                { inspect->damage(percentLeftAlive); }
        }

        //Checks if a Noble already has hired a warrior
        Warrior* owns(const string& warriorName) const
        {
            for (Warrior* const inspect : army)
                if (inspect->getName() == warriorName)
                    return inspect;
            return nullptr;
        }

        vector <Warrior*> army;
        string name;
    };

    //If they exist, this returns their pointer
    Noble* nobleExists(const string& nobleName) const
    {
        //Find the noble
        for (Noble* const inspect : theNobles)
            if (inspect->getName() == nobleName)
                return inspect;

        return nullptr; //Error
    }

    //If they exist, this returns their pointer
    Warrior* warriorExists(const string& warriorName) const
    {
        //Find the warrior
        for (Warrior* const inspect : theRabble)
            if (inspect->getName() == warriorName)
                return inspect;

        return nullptr; //Error
    }

    //If they exist, this returns their pointer and removes them from the rabble
    Warrior* warriorPick(const string& warriorName)
    {
        //Find the warrior
        for (Warrior*& inspect : theRabble) //A reference to each pointer
            if (inspect->getName() == warriorName)
            {
                //Save the heap location of the warrior
                Warrior* theOne = inspect;

                //Remove from the rabble
                inspect = theRabble[theRabble.size()-1];
                theRabble.pop_back();

                return theOne;
            }
        return nullptr;
    }

    vector <Noble*> theNobles;
    vector <Warrior*> theRabble; //Out of work warriors
};

//Not necessary for this assignment, but I made it and I want to use it
//Holds commands as a linked list, where you can pop off the strings
//or the "digest" of a command (the vector of space-seperated words)
class CommandQueue
{
public:
    //Constructor, sets up head sentinal, and accepts a command file
    CommandQueue(const string& inputFileName = "") : firstSentinal(new CommandNode("")),
    lastCommand(nullptr), commandCount(0)
    {
        if (inputFileName != "")
            readCommandFile(inputFileName);
    }

    ~CommandQueue()
    {
        //Clear everything (off the heap)
        while (commandCount > 0)
            pop();
        delete firstSentinal;
    }

    //Populate a linked list with commands
    void readCommandFile(string inputFileName)
    {
        //Open and check filestream, prompt user if they want another file instead (if failed)
        ifstream commandFile(inputFileName);
        while (!commandFile)
        {
            //Prompt for another file, or not
            char tryAgain;
            cerr << inputFileName << " failed to open. Would you like to try another file? (y/n) ";
            cin >> tryAgain;
            //If no, exit program
            if (tryAgain == 'n' || tryAgain == 'N')
            {
                cerr << "No alternate file provided. Cannot continue, closing program.\n";
                exit(1);
            }
            //Otherwise, get a new file
            cout << "Filename: ";
            cin >> inputFileName;
            commandFile.open(inputFileName);
        }

        //Input each line (each command) into a node, then add them each to the commandQueue
        string command;
        while (getline(commandFile, command))
        {
            if (command.size() > 1)  //If the line is not just an endline
                push(command);
        }
    }

    //Get the next command, update flags
    string pop() //A front pop
    {
        if (commandCount)
        {
            //Save a copy of the first real CommandNode, which is about to go away
            CommandNode oldFirstCommand = *firstSentinal->nextCommand;

            //Clean up the heap
            delete firstSentinal->nextCommand;

            //Re-link to the new first command
            firstSentinal->nextCommand = oldFirstCommand.nextCommand;

            //Readjust size of linked list
            --commandCount;

            if (!commandCount) //If there's nothing left, reset to init value
                lastCommand = nullptr;

            return oldFirstCommand.command;
        }
        else
        {
            cerr << "Nothing to pop.\n";
            return "";
        }
    }

    //Put a new command on the back, update flags
    void push(const string& newCommand)
    {
        if (lastCommand) //Tack on next command
        {
            lastCommand->nextCommand = new CommandNode(newCommand);
            //Re-adjust last command pointer
            lastCommand = lastCommand->nextCommand;
        }
        else //Add first and last command
        {
            lastCommand = new CommandNode(newCommand);
            firstSentinal->nextCommand = lastCommand;
        }

        //Re-adjust size
        ++commandCount;
    }

    //Return the size of the linked list
    size_t size() const
        { return commandCount; }

    //Returns a vector of the seperate words in the first command, and pops
    vector <string> popDigest()
    {
        //Pop and get the commands, Convert string to a stream
        istringstream commandStream(pop());

        //Convert stream into a vector
        vector <string> commandVector;
        string word = "";
        while (commandStream >> word)
            commandVector.push_back(word); //Build vector

        return commandVector;
    }

    //Checks the length of a command vecotr, and prints appropriate messages
    bool checkCommandCount(const vector <string>& command, size_t expectedCommandCount) const
    {
        if (command.size() != expectedCommandCount)
        {
            cerr << "Error: Expected Number Of Arguments: " << expectedCommandCount-1 //Exclude Commandname
                 << ". Recieved Number Of Arguments: " << command.size()-1 << ".\n";
            return false; //failed
        }
        return true;
    }

private:
    //Simple Struct, holds a string and a pointer - it's a linked list
    //Allows for FIFO structure easily with what knowledge we're allowed to use
    struct CommandNode
    {
        std::string command;
        CommandNode* nextCommand=nullptr;
        CommandNode(const std::string& command):command(command) {}
    };

    //pointers to the head sentinal and last node of the linked list
    CommandNode* firstSentinal;
    CommandNode* lastCommand;
    size_t commandCount;
};


int main()
{
    //Get the commands
    CommandQueue commands("commandFile.txt");
    //Create gamestate
    GameState myGame;

    //Loop through all commands
    while (commands.size() > 0)
    {
        //Get each command as a vector - easy to process
        vector <string> command = commands.popDigest();

        if (command[0] == "Noble")
        {
            //Check correct amount of arguments, and run command
            if (!commands.checkCommandCount(command, 2) || !myGame.addNoble(command[1]))
                cerr << "Error: Command 'Noble' failed. Does that Noble already exist?\n";
        }
        else if (command[0] == "Warrior")
        {
            //convert strength to a int
            istringstream strenghtStream(command[2]);
            int strength;
            strenghtStream >> strength;

            if (strength < 0)
                { cerr << "Warriors Cannot have negative power\n"; continue; }

            //Check correct amount of arguments and run command
            if (!commands.checkCommandCount(command, 3) || !myGame.addWarrior(command[1], strength))
                cerr << "Error: Command 'Warrior' failed. Does that Warrior already exist?\n";
        }
        else if (command[0] == "Hire")
        {
            //Check correct amount of arguments, and run command
            if (!commands.checkCommandCount(command, 3) || !myGame.nobleHireWarrior(command[1], command[2]))
                cerr << "Error: Command 'Hire' failed. Does that Warrior and Noble "
                        "exist? Has that Noble already hired that Warrior? Is that "
                        "Warrior hired by someone else?\n";
        }
        else if (command[0] == "Fire")
        {
            //Check correct amount of arguments
            if (!commands.checkCommandCount(command, 3) || !myGame.nobleFireWarrior(command[1], command[2]))
                cerr << "Error: Command 'Fire' failed. Does that Warrior and Noble "
                        "exist? Has that Noble hired that Warrior?\n";
        }
        else if (command[0] == "Battle")
        {
            //Check correct amount of arguments
            if (!commands.checkCommandCount(command, 3) || !myGame.battle(command[1], command[2]))
                cerr << "Error: Command 'Battle' failed. Do the Nobles exist?\n";
        }
        else if (command[0] == "Status")
        {
            //Check correct amount of arguments
            if (!commands.checkCommandCount(command, 1))
                {cerr << "In Command 'Status'"; continue; }

            //Run command
            myGame.status();
        }
        else if (command[0] == "Clear")
        {
            //Check correct amount of arguments
            if (!commands.checkCommandCount(command, 1))
                {cerr << "In Command 'Clear'"; continue; };

            //Run command
            myGame.clear();
        }
        else
            cerr << "Error: Unknown Command '" << command[0] << "'.\n";
    }
}
