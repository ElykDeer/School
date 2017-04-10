/* Author: Kyle Martin
 *
 * This code was written for the class CS 2124
 *
 * This program is another version of the warrior program, but as an exercise
 *  in inheritance.
 *
 */

#include "Archer.h"
using namespace std;

namespace WarriorCraft
{
  //Cute little display method - nothing complicated
  void Archer::display(ostream& os=cout) const
  { os << "TWANG! " << getName() << " says: 'Take that in the name of my lord, " << masterName() << ".'"; }
}
