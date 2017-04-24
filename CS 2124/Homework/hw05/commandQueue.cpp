/* Author: Kyle Martin
 *
 * This code was written for the class CS 2124
 *
 * This program is another version of the
 *  warrior program, but as an exercise in
 *  dynamic memory.
 *
 * */

#include "CommandQueue.h"

using namespace std;

//Constructor, sets up head sentinal
CommandQueue::CommandQueue(): CommandQueue(const string& inputFileName = "") : firstSentinal(new CommandNode("")),
                 lastCommand(nullptr), commandCount(0)
  {
      if (inputFileName != "")
          readCommandFile(inputFileName);
  }
  
CommandQueue::~CommandQueue()
{
  //Clear everything (off the heap)
  while (commandCount > 0)
    { pop(); }
  delete firstSentinal;
}

//Populate a linked list with commands
void CommandQueue::readCommandFile(string inputFileName)
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
  while (getline(commandFile, command))
  {
    if (command.size() > 1)  //If the line is not just an endline
      push(command);
  }
}

//Get the next command, update flags
string CommandQueue::pop()
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
void CommandQueue::push(const string& newCommand)
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
size_t CommandQueue::size() const
  { return commandCount; }
