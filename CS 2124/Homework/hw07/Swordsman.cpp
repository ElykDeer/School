/* Author: Kyle Martin
 *
 * This code was written for the class CS 2124
 *
 * This program is another version of the warrior program, but as an exercise
 *  in inheritance.
 *
 */

#include "Swordsman.h"
using namespace std;

namespace WarriorCraft
{
  //using Protector::Protector;
  //Cute little display method - nothing complicated
  void Swordsman::display(ostream& os=cout) const
  { os << "CLANG! " << getName() << " says: 'Take that in the name of my lord, " << masterName() << ".'"; }
}
