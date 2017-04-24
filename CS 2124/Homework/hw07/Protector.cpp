/* Author: Kyle Martin
 *
 * This code was written for the class CS 2124
 *
 * This program is another version of the Protector program, but as an exercise
 *  in inheritance.
 *
 */

#include "Protector.h"
#include "Lord.h"
using namespace std;

namespace WarriorCraft
{
  //The Protector Class -- based on the Protector struct from the previous class
  Protector::Protector(const string& ProtectorName, const int strength): name(ProtectorName),
                  strength(strength), master(nullptr) {}

  Protector::~Protector() {}

  //Do nothing, get compilation to work
  void Protector::display(std::ostream&) const {}

  string Protector::getName() const
    { return name; }

  int Protector::getStrength() const
    { return strength; }

  //For when they fight, they get damage distributed to them (they're told
  //how much more they have to live).
  void Protector::damage(const double percentLeftAlive)
    { strength *= percentLeftAlive; }

  //Sets the master pointer, but returns false if the master pointer is full
  bool Protector::newMaster(Lord* newMaster)
  {
    if (master) //if there's a master in place
      return false;

    master = newMaster;
    return true;
  }

  //Clears master pointer, returns false if already empty
  bool Protector::release()
  {
    if (master)
    {
      master = nullptr;
      return true;
    }
    return false;
  }

  //Allows the Protector to run away from cruel masters - ret false on no master
  bool Protector::runaway()
  {
    //If we have a master, let them know that we are leaving (to sort their
      // internals out, and then let the world know we're free)
    if (master)
    {
      master->noWeekNotice(name);
      return true;
    }
    return false;  //We don't have anyone to run away from
  }

  string Protector::masterName() const
    {return master->getName(); }

}

ostream& operator<<(ostream& os, const WarriorCraft::Protector& rhs)
{
  rhs.display(os);
  return os;
}
