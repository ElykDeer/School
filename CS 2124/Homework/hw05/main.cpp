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

int main()
{
  CommandQueue test;

  test.readCommandFile("commandFile.txt");
  while (test.size() > 0)
  {
    cout << test.pop() << endl;
  }
}
