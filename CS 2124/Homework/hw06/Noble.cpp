/* Author: Kyle Martin
 *
 * This code was written for the class CS 2124
 *
 * This program is another version of the warrior program, but as an exercise
 *  in seperate compilation.
 *
 */

#include "Noble.h"
#include "Warrior.h"
using namespace std;

namespace WarriorCraft
{
  //Forward Dec Of warriors
  class Warrior;

  //This class is our nobles - who fight and drink
  class Noble
  {
  public:
    //Nobles haave names but don't start with armies
    Noble(const string& name): name(name) {}

    //They drink
    void drink() const
      { cout << "Cheers!\n"; }

    //Get warriors!
    //Since this is non-user code, this one is different as to not redo work
    //(works by object, not by name) - the calle checks that both exist
    bool hire(Warrior& newBlood)
    {
      if (owns(newBlood.getName())) //Make sure not already 'owned'
        return false;
      army.push_back(&newBlood);
      return !(nullptr == owns(newBlood.getName())); //Make sure it worked, convert to bool
    }

    //Get rid of warriors
    Warrior* fire(const string& firedBlood)
    {
      //Make sure we have the warrior we're told that we're firing
      //(modified from owns)
      Warrior* firedWarrior = nullptr;
      for (Warrior*& inspect : army)
        if (inspect->getName() == firedBlood)
        {
          firedWarrior = inspect;
          inspect = army[army.size()-1]; //Overwire inspect
          army.pop_back(); //Get rid of the duplicate
        }
      if (!firedWarrior)
        return firedWarrior;

      //Announce what's happening..
      cout << firedBlood << " you are dishonerably excused from service!\n";
      return firedWarrior;
    }

    //The Battle command (as a function)
    void battle(Noble& enemy)
    {
      //Announce
      cout << name << " battles " << enemy.name << "!\n";

      //Gather collective strengths
      double myStrength = getStrength();
      double enemyStrength = enemy.getStrength();

      //check if they're already dead
      if (myStrength == 0 || enemyStrength == 0)
      {
        if (myStrength == 0 && enemyStrength == 0)
          { cout << name << " and " << enemy.name << " are both dead!!"; }
        else if (myStrength == 0)
          { cout << name << " is dead!"; }
        else if (enemyStrength == 0)
          { cout << enemy.name << " is dead!"; }
        cout << endl << endl;
        return;
      }

      //Battle it out and assign damage
      const double deathMultiplier = 0; //If someone dies, this is what their death looks like
      if (myStrength == enemyStrength)
      {
        cout << "Mutual Annihalation: " << name << " and " << enemy.name <<
        " both die at each other's hands.";
        damage(deathMultiplier);
        enemy.damage(deathMultiplier);
      }
      else if (myStrength < enemyStrength)  //They win
      {
        cout << enemy.name << " defeats " << name << "!";
        damage(deathMultiplier);
        enemy.damage(myStrength/enemyStrength);
      }
      else if (myStrength > enemyStrength) //I win!
      {
        cout << name << " defeats " << enemy.name << "!";
        enemy.damage(deathMultiplier);
        damage(enemyStrength/myStrength);
      }

      cout << endl << endl; //Seperate block of text for visuals
    }

    //The Status command (also displays their warriors)
    void display() const
    {
      //Show off the Noble
      cout << "\n" << name << " has an army of " << army.size() << "!\n";

      //Print all warriors
      for (Warrior* inspect : army)
      {
        cout << "\t"; //Indent block below the Nobel's name
        inspect->display();
      }
    }

    string getName() const
      { return name; }

  private:
    //Determine the army's collective strength - for battle
    int getStrength() const
    {
      int totalStrength = 0;
      //Add up everyones strength
      for (Warrior* inspect : army)
        { totalStrength += inspect->getStrength(); }

      return totalStrength;
    }

    //Distribute damage to the warriors from battle
    //Simply multiply percentDamaged by current strength
    void damage(const double percentLeftAlive)
    {
      //Damage all warriors
      for (Warrior* inspect : army)
        { inspect->damage(percentLeftAlive); }
    }

    //Checks if a Noble already has hired a warrior
    Warrior* owns(const string& warriorName) const
    {
      for (Warrior* const inspect : army)
        if (inspect->getName() == warriorName)
          return inspect;
      return nullptr;
    }

    vector <Warrior*> army;
    string name;
  };
}
