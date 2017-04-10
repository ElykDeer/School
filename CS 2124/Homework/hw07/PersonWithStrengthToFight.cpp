/* Author: Kyle Martin
 *
 * This code was written for the class CS 2124
 *
 * This program is another version of the warrior program, but as an exercise
 *  in inheritance.
 *
 */

#include "PersonWithStrengthToFight.h"
using namespace std;

namespace WarriorCraft
{
  PersonWithStrengthToFight::PersonWithStrengthToFight(
    const string& name, const int strength)
    : NobleBase(name), strength(strength) {}

  void PersonWithStrengthToFight::display(ostream& os=cout) const
    { os << getName() << " has a strength of " << strength << endl; }

  int PersonWithStrengthToFight::getStrength() const
    { return strength; }

  void PersonWithStrengthToFight::damage(const double percentLeftAlive)
    { strength *= percentLeftAlive; }
}
