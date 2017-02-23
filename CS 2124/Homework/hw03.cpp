/* Author: Kyle Martin
 * 
 * This code was written for the class CS 2124
 * 
 * The purpose of this code is to read a file, 
 *  "warriors.txt", which is a set of commands,
 *  one on each line, and run a "battle
 *  simulation".  The commands supported are
 *  listed below.
 * 
 *  Warrior: Creates a Warrior, first parm
 *   is the name, followed by an int strength
 * 
 *  Status: Lists all current Warriors and 
 *   their respective Stregths
 * 
 *  Battle: Takes two parameters that must be
 *   two Warriors (if it is the same Warrior,
 *   that Warrior will kill themself), and
 *   will report the results of that Battle.
 * 
 * Note: This program utilizes a CommandQueue,
 *  which may seem obsesive for this program,
 *  and it is.  This program was expanded out
 *  of class in a way that needed the command
 *  Queue to be what it is here, with more 
 *  additions. 
 * 
 * */


#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <sstream>
using namespace std;


//A command node, holds the command string, the
  //index of the next command to be executed in
  //the commandQueue commands vector, and
  //whether or not this command has been executed
struct CommandNode{
    string command;
    size_t nextCommand=0;
    bool hasBeenExecuted=false;
    
    CommandNode(string commandInit):command(commandInit){}
};
//The Command Queue, stored as nodes in a vector
  //commands is the vector that holds the commands
  //nextCommandIndex - index of the next command to exec
  //lastCommandIndex - index of the last command in queue
  //insertCommandIndex - where to insert the next command
struct CommandQueue{
    vector <CommandNode> commands;
    size_t nextCommandIndex = 0;
    size_t lastCommandIndex = 0;
    size_t insertCommandIndex = 0;
};


//The Warrior Class -- based on the warrior struct from the previous class
class Warrior
{
public:
    Warrior(string n, int s):name(n), strength(s), maxStrength(s) {}

//private:
    string name;
    int strength;
    int maxStrength;
    bool dead=false;
    int kills = 0;
};


//Insert a commandNode into the commandQueue, and update commandQueue's flags
void insertCommand(CommandQueue& addingCommandQ, const CommandNode& commandToInsert);


//This function will read a file (default =
  //"warriors.txt", but if that fails, the 
  //program will prompt the user for another
  //file).  This function will return a
  //command queue to be proccessed by
  //another function (commands = strings).
  //The string is passed by value because I
  //desired to pass litteral filenames to
  //this function, and then use the variable,
  //inputFileName to accept a new file if the
  //given file fails to open.
CommandQueue readCommandFile(string inputFileName);

//Remove the next command from the command queue
  //and return that command
CommandNode front_pop(CommandQueue& commandSet);

//Interpret the next Command in the Command 
  //Queue (FIFO, First In First Out), and
  //execute that command.  Needs the active
  //commandQueue and active Warriors
void processCommand(CommandNode& command, vector <Warrior>& warriorSet); //Alternatively, could return a "commandType"

//Will process and run numberOfCommands number of commands. If numberOfCommands==0, run all commands (default)
void runCommands(CommandQueue& commandSet, vector <Warrior>& warriorSet, size_t numberOfCommands=0);

//The Warrior command (as a function)
Warrior warriorCommand(const string name, const int strength);

//The Battle command (as a function)
void battleCommand(const string nameOne, const string nameTwo, vector <Warrior>& warriors);

//The Status command (for one warrior)
void statusCommand(string warName);

//The Status command (as a function)
void statusCommand(const vector <Warrior>& warriors);

//This function will make sure that the name "warName" is not already in the vector.
bool isDouble(const vector <Warrior>& warriors, string warName);


int main()
{
    //Create and populate the command queue
    CommandQueue commandSet = readCommandFile("warriors.txt");
    
    //Where all warriors will be stored
    vector<Warrior> regiment;
    
    //Run all commands
    runCommands(commandSet, regiment);
}


//Insert a commandNode into the commandQueue, and update commandQueue's flags
void insertCommand(CommandQueue& addingCommandQ, const CommandNode& commandToInsert)
{
    //if there are no availible spots, tack it on to the end
    if (addingCommandQ.insertCommandIndex == addingCommandQ.commands.size())
    {
        addingCommandQ.commands.push_back(commandToInsert);
        if (addingCommandQ.lastCommandIndex != addingCommandQ.commands.size())
            addingCommandQ.commands[addingCommandQ.lastCommandIndex].nextCommand=addingCommandQ.commands.size(); //Link the previous "last command" to this command, if it exists"
        addingCommandQ.lastCommandIndex=addingCommandQ.commands.size(); //Set this as the last command
        ++addingCommandQ.insertCommandIndex; //increment the index.  Since it was already at the end, it's safe to assume that the queue is full before this point
    } else //Assumed: at least one other node exists
    {
        addingCommandQ.commands[addingCommandQ.insertCommandIndex]=commandToInsert;
        addingCommandQ.commands[addingCommandQ.lastCommandIndex].nextCommand=addingCommandQ.insertCommandIndex; //Link the previous "last command" to this command
        addingCommandQ.lastCommandIndex=addingCommandQ.commands.size(); //Set this as the last command
        
        //Update the insertCommandIndex
        size_t index = addingCommandQ.insertCommandIndex;
        while (!addingCommandQ.commands[index].hasBeenExecuted && index < addingCommandQ.commands.size())
            ++index;
        addingCommandQ.insertCommandIndex=index;
    }
}


CommandQueue readCommandFile(string inputFileName)
{
    //Open and check filestream, prompt user if they want another file instead (if failed)
    ifstream commandFile(inputFileName);
    while (!commandFile)
    {
        //Prompt for another file, or not
        char tryAgain;
        cerr << inputFileName << " failed to open. Would you like to try another file? (Y/n) ";
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
    CommandQueue commandSet;
    while (getline(commandFile, command))
    {
        if (command.size() > 1)  //If the line is not just an endline
            insertCommand(commandSet, CommandNode(command));
    }
    return commandSet;
}


//Remove the next command from the command queue
  //and return that command
CommandNode front_pop(CommandQueue& commandSet)
{
    //If there's no next command, return a "already executed" "status" command
    if (commandSet.nextCommandIndex == commandSet.commands.size())
    {
        cerr << "There are no commands to execute!\n";
        CommandNode falseEntry("Status");
        falseEntry.hasBeenExecuted = true;
        return falseEntry;
    }
    
    //Clone the command
    CommandNode nextCommand = commandSet.commands[commandSet.nextCommandIndex];
    //Will mark as executed, though it is entirely possible that is has not been
    commandSet.commands[commandSet.nextCommandIndex].hasBeenExecuted = true;
    //Check if there is a next command chained after this
    if (commandSet.commands[commandSet.nextCommandIndex].nextCommand == commandSet.commands.size()) // No, there isn't
    {
        CommandQueue newQueue;
        commandSet = newQueue; //Reset all flags. empty command queue
    } else //Yes, there is
        commandSet.nextCommandIndex = commandSet.commands[commandSet.nextCommandIndex].nextCommand; //Set new values for commandQueue
    return nextCommand;
}


//Physic note:
//(1+-sqrt(1+2gh)/v^2)/g


//Interpret the next Command in the Command 
  //Queue (FIFO, First In First Out), and
  //execute that command.  Needs the active
  //commandQueue and active Warriors
void processCommand(CommandNode& command, vector <Warrior>& warriorSet)
{
    //Create a stream as to process the command (a whole line) word by word.
    istringstream commandString(command.command);
    
    string commandName;
    commandString >> commandName; //get command
    
    //Determine which command is being invoked, and run that command
    if (commandName == "Status")
        statusCommand(warriorSet);
    else if (commandName == "Warrior")
    {
        string warOne;
        int strength;
        commandString >> warOne; //get warrior name
        commandString >> strength; //get warrior strength
        if (!isDouble(warriorSet, warOne))
            warriorSet.push_back(warriorCommand(warOne, strength));
    }
    else if (commandName == "Battle")
    {
        string warOne;
        string warTwo;
        commandString >> warOne; //get warrior name
        commandString >> warTwo; //get warrior name
        battleCommand(warOne, warTwo, warriorSet);
    }
    else
        cerr << "Command not found\n";
}


//Will process and run numberOfCommands number of commands. If numberOfCommands==0, run all commands (default)
void runCommands(CommandQueue& commandSet, vector <Warrior>& warriorSet, size_t numberOfCommands)
{
    if (numberOfCommands==0)
        numberOfCommands=commandSet.commands.size();
    
    //run the commands
    for (size_t index= 0; index < numberOfCommands; ++index)
    {
        CommandNode workingCommand = front_pop(commandSet);
        processCommand(workingCommand, warriorSet);
    }
}


//The Warrior command (as a function)
Warrior warriorCommand(const string name, const int strength)
{
    Warrior w(name, strength);
    return w;
}


//The Battle command (as a function)
void battleCommand(const string nameOne, const string nameTwo, vector <Warrior>& warriorSet)
{
    cout << endl;
    //Find the actual warrior objects (by index) in the vector
    size_t warOneIndex = warriorSet.size();
    size_t warTwoIndex = warriorSet.size();
    //condition waits for both warriors to be found AND ensures no segfault
    for (size_t index = 0; (warOneIndex == warriorSet.size() || warTwoIndex == warriorSet.size()) && index < warriorSet.size(); ++index)
    {
        if (warriorSet[index].name == nameOne) //Assign First Name
            warOneIndex = index;
        if (warriorSet[index].name == nameTwo)  //Assign Second Name
            warTwoIndex = index;
        if ((warOneIndex == warriorSet.size() || warTwoIndex == warriorSet.size()) && index == warriorSet.size()-1) //Failsafe...At least ne of the names do not exist
        {
            cerr << "The King cries, '";
            if (warOneIndex == warriorSet.size())
                cerr << nameOne << " hast not shown! ";
            if (warTwoIndex == warriorSet.size())
                cerr << nameTwo << " has not shown! ";
            cerr << "This matcheth is cancel'd!!'\n";
            return; //Cancel the match
        }
    }
    //Block if a warrior kills himself for the glory of The King
    if (nameOne==nameTwo)
    {
        cout << "'Silence!!', the King bellows. He stands up, extending his arm to the knight standing before him in the ring. '";
        cout << nameOne << ", I hest thee, as thy king and holy leadeth'r, to did shed thy blood f'r the ent'rtainment of all who is't art h're tonight!'\n";
        cout << nameOne << " looks down. He knows that by his honor he must obey his King, so he unsheaths his sword, holds it in both hands, ";
        cout << "and brings it down upon his flesh, spilling his insides over his shoes and onto the ground below him, which rushes up to welcome him.\n";
        cout << "The crowd goes wild and the King laughs, splashing some wine onto the silk of his shirt and the furs of the rug below his feet.\n";
        warriorSet[warOneIndex].strength = 0;
        warriorSet[warOneIndex].dead = true;
        warriorSet[warOneIndex].kills++; //What? He /did/ kill another person...
        return;
    }
    
    cout << nameOne << " 'gainst " << nameTwo << ". 'Square!', belches The King, and the fight ensues.\n";
    //Declare winners and update warrior stats
    if (warriorSet[warOneIndex].strength > warriorSet[warTwoIndex].strength)
    {
        cout << nameOne << " hast defeat'd " << nameTwo << "!\n";
        warriorSet[warOneIndex].strength -= warriorSet[warTwoIndex].strength;
        warriorSet[warOneIndex].kills++;
        warriorSet[warTwoIndex].strength = 0;
        warriorSet[warTwoIndex].dead = true;
    }
    if (warriorSet[warOneIndex].strength < warriorSet[warTwoIndex].strength)
    {
        cout << nameTwo << " has defeated " << nameOne << "!\n";
        warriorSet[warTwoIndex].strength -= warriorSet[warOneIndex].strength;
        warriorSet[warTwoIndex].kills++;
        warriorSet[warOneIndex].strength = 0;
        warriorSet[warOneIndex].dead = true;
    }
    if (warriorSet[warOneIndex].strength == warriorSet[warTwoIndex].strength)
    {
        cout << nameTwo << " and " << nameOne << " are equally matched, and hack each other to pieces!! The King approves!\n";
        warriorSet[warOneIndex].strength = 0;
        warriorSet[warOneIndex].dead = true;
        warriorSet[warOneIndex].kills++;
        warriorSet[warTwoIndex].strength = 0;
        warriorSet[warTwoIndex].dead = true;
        warriorSet[warTwoIndex].kills++;
    }
}


//The Status command (for one warrior)
void statusCommand(const vector <Warrior>& warriors, string warName)
{
    for (const Warrior& inspect : warriors)
        if (inspect.name == warName)
        {
            cout << warName << " is a great warrior, with a strength of " << inspect.strength << " and " << inspect.kills << " kill";
            if (inspect.kills > 3)
                cout << "s! A truely mighty warrior!\n";
            else if (inspect.kills > 1)
                cout << "s!\n";
            else if (inspect.kills > 0)
                cout << "!\n";
            else
                cout << "s... Pathetic.\n";
            return;
        }
    cerr << warName << " does not exist.\n";
    return;
}

//The Status command (as a function)
void statusCommand(const vector <Warrior>& warriors)
{
    cout << endl;
    //Find out how many dead/alive warriors there are
    int aliveWarriors = 0;
    for (const Warrior& warrior : warriors)
        if (!warrior.dead)
            aliveWarriors+=1;
    int deadWarriors = warriors.size()-aliveWarriors;
        
    //cout << aliveWarriors << endl;
    
    if (aliveWarriors == 1) //Singular Alive Warrior
        for (const Warrior& warrior : warriors)
            if (!warrior.dead)
            {
                statusCommand(warriors, warrior.name);
                //return;
            }
    if (aliveWarriors > 1)  //Multiple alive warriors
    {
        cout << "The following warriors are fit to serve their King:\n";
        for (const Warrior& warrior : warriors)
            if (!warrior.dead)
                cout << " " << warrior.name << ", at " << warrior.strength << " strength." << endl;
    }
    if (deadWarriors > 0)//Any number of dead guys
    {
        cout << "The following warriors are just a bit... Stale:\n";
        for (const Warrior& warrior : warriors)
            if (warrior.dead)
                cout << " " << warrior.name << endl;
    }
}


//This function will make sure that the name "warName" is not already in the vector.
bool isDouble(const vector <Warrior>& warriors, string warName)
{
    for (const Warrior& inspect : warriors)
        if (inspect.name == warName)
            return true;
    return false;
}
