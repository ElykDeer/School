 /* Author: Kyle Martin
  *
  * This code was written for the class CS 2124
  *
  * This program is another version of the Protector program, but as an exercise
  *  in inheritance.
  *
  */

#ifndef WARRIORCRAFT_PROTECTOR
#define WARRIORCRAFT_PROTECTOR 1

#include <string>
#include <iostream>

namespace WarriorCraft
{
  //Neeeded Forward Dec
  class Lord;
  //The Protector Class -- based on the Protector struct from the previous class
  class Protector
  {
  public:
    //Constructor - needs name and strength
    Protector(const std::string&, const int);

    virtual ~Protector();

    //Cute little display method - nothing complicated
    virtual void display(std::ostream&) const = 0;

    //Some standard getters
    std::string getName() const;
    int getStrength() const;

    //For when they fight, they get damage distributed to them (they're told
    //how much more they have to live).
    void damage(const double);

    //Sets the master pointer, but returns false if the master pointer is full
    bool newMaster(Lord*);

    //Clears master pointer, returns false if already empty
    bool release();

    //Allows the Protector to run away from cruel masters - ret false on no master
    bool runaway();

    std::string masterName() const;

  private:
    std::string name;
    double strength;
    Lord* master;
  };
}
std::ostream& operator<<(std::ostream&, const WarriorCraft::Protector&);
#endif
