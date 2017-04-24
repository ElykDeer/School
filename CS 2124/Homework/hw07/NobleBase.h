/* Author: Kyle Martin
 *
 * This code was written for the class CS 2124
 *
 * This program is another version of the Protector program, but as an exercise
 *  in inheritance.
 *
 */

#ifndef WARRIORCRAFT_NOBLEBASE
#define WARRIORCRAFT_NOBLEBASE 1

#include <string>
#include <iostream>

namespace WarriorCraft
{
  //Necissary Forwad Dec
  class Protector;

  //This class is our nobles - who fight and drink
  class NobleBase
  {
  public:
    //Nobles have names but don't start with armies
    NobleBase(const std::string&);

    virtual ~NobleBase();

    //They drink
    void drink() const;

    //The Battle command (as a function)
    virtual void battle(NobleBase&);

    //The Status command (also displays their Protectors)
    virtual void display(std::ostream&) const = 0;

    std::string getName() const;

    bool isAlive() const;

  protected:
    //Determine the army's collective strength - for battle
    virtual int getStrength() const = 0;

    //Distribute damage to the Protectors from battle
    //Simply multiply percentDamaged by current strength
    virtual void damage(const double) = 0;

    bool continueToBattle(NobleBase&);
    void theRestOfTheBattle(NobleBase&);

  private:
    std::string name;
    bool alive;
  };
}
std::ostream& operator<<(std::ostream&, const WarriorCraft::NobleBase&);
#endif
