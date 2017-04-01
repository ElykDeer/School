/* Author: Kyle Martin
 *
 * This code was written for the class CS 2124
 *
 * This program is another version of the warrior program, but as an exercise
 *  in seperate compilation.
 *
 */

#ifndef WARRIORCRAFT_NOBLE
#define WARRIORCRAFT_NOBLE 1

#include <string>
#include <iostream>
#include <vector>

namespace WarriorCraft
{
  //Necissary Forwad Dec
  class Warrior;

  //This class is our nobles - who fight and drink
  class Noble
  {
  public:
    //Nobles haave names but don't start with armies
    Noble(const std::string& name);

    //They drink
    void drink() const;

    //Get warriors!
    //Since this is non-user code, this one is different as to not redo work
    //(works by object, not by name) - the calle checks that both exist
    bool hire(Warrior& newBlood);

    //Get rid of warriors
    Warrior* fire(const std::string& firedBlood);

    //The Battle command (as a function)
    void battle(Noble& enemy);

    //The Status command (also displays their warriors)
    void display(std::ostream&) const;

    std::string getName() const;

    //Be notified if a warrior runs away
    void noWeekNotice(const std::string&);

  private:
    //Determine the army's collective strength - for battle
    int getStrength() const;

    //Distribute damage to the warriors from battle
    //Simply multiply percentDamaged by current strength
    void damage(const double);

    //Checks if a Noble already has hired a warrior
    Warrior* owns(const std::string&) const;

    std::vector <Warrior*> army;
    std::string name;
  };
}
std::ostream& operator<<(std::ostream&, const WarriorCraft::Noble&);
#endif
