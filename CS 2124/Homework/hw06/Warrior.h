/* Author: Kyle Martin
 *
 * This code was written for the class CS 2124
 *
 * This program is another version of the warrior program, but as an exercise
 *  in seperate compilation.
 *
 */

 #ifndef WARRIORCRAFT_WARRIORS
 #define WARRIORCRAFT_WARRIORS 1

 #include <string>
 #include <iostream>
 #include <vector>

namespace WarriorCraft
{
  //The Warrior Class -- based on the warrior struct from the previous class
  class Warrior
  {
  public:
    //Constructor - needs name and strength
    Warrior(const std::string&, const int);

    //Cute little display method - nothing complicated
    void display() const;

    //Some standard getters
    std::string getName() const;
    int getStrength() const;

    //For when they fight, they get damage distributed to them (they're told
    //how much more they have to live).
    void damage(const double);

  private:
    std::string name;
    double strength;
  };
}
#endif
