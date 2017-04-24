/* Author: Kyle Martin
 *
 * This code was written for the class CS 2124
 *
 * This program is another version of the warrior program, but as an exercise
 *  in inheritance.
 *
 */

 #include "Warrior.h"
 #include "Lord.h"
 using namespace std;

namespace WarriorCraft
{
  //Neeeded Forward Dec
  class Lord;

  //The Warrior Class -- based on the warrior struct from the previous class
  Warrior::Warrior(const string& warriorName, const int strength): name(warriorName),
  		  			strength(strength), master(nullptr) {}

  //Cute little display method - nothing complicated
  void Warrior::display(ostream& os=cout) const
    { os << name << " of power " << strength << ".\n"; }

  string Warrior::getName() const
  	{ return name; }

  int Warrior::getStrength() const
    { return strength; }

  //For when they fight, they get damage distributed to them (they're told
  //how much more they have to live).
  void Warrior::damage(const double percentLeftAlive)
    { strength *= percentLeftAlive; }

  //Sets the master pointer, but returns false if the master pointer is full
  bool Warrior::newMaster(Lord* newMaster)
  {
    if (master) //if there's a master in place
      return false;

    master = newMaster;
    return true;
  }

  //Clears master pointer, returns false if already empty
  bool Warrior::release()
  {
    if (master)
    {
      master = nullptr;
      return true;
    }
    return false;
  }

  //Allows the warrior to run away from cruel masters - ret false on no master
  bool Warrior::runaway()
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

}

ostream& operator<<(ostream& os, const WarriorCraft::Warrior& rhs)
{
  rhs.WarriorCraft::Warrior::display(os);
  return os;
}
