/* Author: Kyle Martin
 *
 * This code was written for the class CS 2124
 *
 * This program is another version of the warrior program, but as an exercise
 *  in inheritance.
 *
 */

 #ifndef WARRIORCRAFT_WARRIORS
 #define WARRIORCRAFT_WARRIORS 1

 #include <string>
 #include <iostream>
 #include <vector>

namespace WarriorCraft
{
  //Necissary Forwad Dec
  class Lord;

  //The Warrior Class -- based on the warrior struct from the previous class
  class Warrior
  {
  public:
    //Constructor - needs name and strength
    Warrior(const std::string&, const int);

    //Cute little display method - nothing complicated
    void display(std::ostream&) const;

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

    //Allows the warrior to run away from cruel masters - ret false on no master
    bool runaway();

  private:
    std::string name;
    double strength;
    Lord* master;
  };
}
std::ostream& operator<<(std::ostream&, const WarriorCraft::Warrior&);
#endif
