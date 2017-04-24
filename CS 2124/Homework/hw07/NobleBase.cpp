/* Author: Kyle Martin
 *
 * This code was written for the class CS 2124
 *
 * This program is another version of the Protector program, but as an exercise
 *  in inheritance.
 *
 */

#include "NobleBase.h"
using namespace std;

namespace WarriorCraft
{
  //Nobles haave names but don't start with armies
  NobleBase::NobleBase(const string& name): name(name), alive(true) {}

  NobleBase::~NobleBase() {}

  //They drink
  void NobleBase::drink() const
  	{
      if (!alive)
      {
        cout << name << " can't drink, they're already dead!\n";
        return;
      }
      cout << "Cheers!\n";
    }

  bool NobleBase::continueToBattle(NobleBase& enemy)
  {
      //Announce
      cout << name << " battles " << enemy.name << "!\n";
      
      //check if they're already dead
      if (!alive || !enemy.alive)
      {
        if (!alive && !enemy.alive)
          { cout << name << " and " << enemy.name << " are both already dead!!"; }
        else if (!alive)
          { cout << name << " is already dead!"; }
        else if (!enemy.alive)
          { cout << enemy.name << " is already dead!"; }
        cout << endl;
        return false;
      }
      return true;
  }

  void NobleBase::theRestOfTheBattle(NobleBase& enemy)
  {
      //Gather collective strengths
      int enemyStrength = enemy.getStrength();
      int myStrength = getStrength();

      //Battle it out and assign damage
      const double deathMultiplier = 0; //If someone dies, this is what their death looks like
      if (myStrength == enemyStrength)
      {
        cout << "Mutual Annihalation: " << name << " and " << enemy.name <<
                " both die at each other's hands.";
        damage(deathMultiplier);
        enemy.damage(deathMultiplier);
        enemy.alive = false;
        alive = false;
      }
      else if (myStrength < enemyStrength)  //They win
      {
        cout << enemy.name << " defeats " << name << "!";
        damage(deathMultiplier);
        enemy.damage(myStrength/enemyStrength);
        alive = false;
      }
      else if (myStrength > enemyStrength) //I win!
      {
        cout << name << " defeats " << enemy.name << "!";
        enemy.damage(deathMultiplier);
        damage(enemyStrength/myStrength);
        enemy.alive = false;
      }
      cout << endl; //Seperate block of text for visuals
  }

  //The Battle command (as a function)
  void NobleBase::battle(NobleBase& enemy)
  {
    //Check for a pulse
    if (!continueToBattle(enemy))
    { theRestOfTheBattle(enemy); /* Actually battle! */}
  }

  string NobleBase::getName() const
    { return name; }

  void NobleBase::display(ostream&) const {} //Dummy Declaration for << operator

  bool NobleBase::isAlive() const
    { return alive; }
}

ostream& operator<<(ostream& os, const WarriorCraft::NobleBase& rhs)
{
  rhs.display(os);
  return os;
}
