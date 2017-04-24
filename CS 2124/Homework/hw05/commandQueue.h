/* Author: Kyle Martin
 *
 * This code was written for the class CS 2124
 *
 * This program is another version of the
 *  warrior program, but as an exercise in
 *  dynamic memory.
 *
 * */

#include <iostream>
#include <string.h>
#include <fstream>

class CommandQueue
{
public:
  //Constructor, sets up head sentinal
  CommandQueue();
  ~CommandQueue();

  //Populate a linked list with commands
  void readCommandFile(std::string);
  //Get the next command, update flags
  std::string pop(); //A front pop
  //Put a new command on the back, update flags
  void push(const std::string&);
  //Return the size of the linked list
  size_t size() const;

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
