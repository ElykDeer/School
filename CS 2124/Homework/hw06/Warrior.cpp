/* Author: Kyle Martin
 *
 * This code was written for the class CS 2124
 *
 * This program is another version of the warrior program, but as an exercise
 *  in seperate compilation.
 *
 */

 #include "Warrior.h"
 #include "Noble.h"
 using namespace std;

namespace WarriorCraft
{
  //Neeeded Forward Dec
  class Noble;

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
}
