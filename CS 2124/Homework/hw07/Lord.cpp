/* Author: Kyle Martin
 *
 * This code was written for the class CS 2124
 *
 * This program is another version of the Protector program, but as an exercise
 *  in inheritance.
 *
 */

#include "Lord.h"
#include "Protector.h"
using namespace std;

namespace WarriorCraft
{
  //Forward Dec Of Protectors
  class Protector;

  //Get Protectors!
  //Since this is non-user code, this one is different as to not redo work
  //(works by object, not by name) - the calle checks that both exist
  bool Lord::hires(Protector& newBlood)
  {
    //Check for a pulse
    if (!NobleBase::isAlive())
    { return false; }

    if (owns(newBlood.getName()) || !newBlood.newMaster(this)) //Make sure not already 'owned'
      return false;
    army.push_back(&newBlood);
    return !(nullptr == owns(newBlood.getName())); //Make sure it worked, convert to bool
  }

  //Get rid of Protectors
  Protector* Lord::fire(const string& firedBlood)
  {
    //Make sure we have the Protector we're told that we're firing
    //(modified from owns)
    Protector* firedProtector = nullptr;
    for (Protector*& inspect : army)
      if (inspect->getName() == firedBlood)
      {
        firedProtector = inspect;
        inspect = army[army.size()-1]; //Overwire inspect
        army.pop_back(); //Get rid of the duplicate
      }
    if (!firedProtector)
      return firedProtector;

    //Announce what's happening..
    cout << firedBlood << " you are dishonerably excused from service!\n";
    firedProtector->release();
    return firedProtector;
  }

  //Be notified if a Protector runs away
  void Lord::noWeekNotice(const string& firedBlood)
  {
    //Make sure we have the Protector we're told that we're firing
    //(modified from owns)
    Protector* firedProtector = nullptr;
    for (Protector*& inspect : army)
      if (inspect->getName() == firedBlood)
      {
        firedProtector = inspect;
        inspect = army[army.size()-1]; //Overwire inspect
        army.pop_back(); //Get rid of the duplicate
      }
    if (!firedProtector)
      return;

    //Announce what's happening..
    cout << firedBlood << " runs away from his master in terror\n";
    firedProtector->release();
  }

  //The Status command (also displays their Protectors)
  void Lord::display(ostream& os=cout) const
  {
    //Show off the Noble
    os << "\n" << getName() << " has an army of " << army.size() << "!\n";

    //Print all Protectors
    for (Protector* inspect : army)
      { os << "\t" << *inspect; }//Indent block below the Nobel's name
  }

  //Determine the army's collective strength - for battle
  int Lord::getStrength() const
  {
      int totalStrength = 0;
      //Add up everyones strength
      for (Protector* inspect : army)
        { totalStrength += inspect->getStrength(); }

      return totalStrength;
  }

  //Distribute damage to the Protectors from battle
  //Simply multiply percentDamaged by current strength
  void Lord::damage(const double percentLeftAlive)
  {
    //Damage all Protectors
    for (Protector* inspect : army)
      { inspect->damage(percentLeftAlive); }
  }

  //Checks if a Noble already has hired a Protector
  Protector* Lord::owns(const string& ProtectorName) const
  {
    for (Protector* const inspect : army)
      if (inspect->getName() == ProtectorName)
      return inspect;
    return nullptr;
  }

  void Lord::battle(NobleBase& noble)
  {
    if (continueToBattle(noble))
    {
      for (Protector* protector : army)
        { cout << *protector << "\n"; }
      theRestOfTheBattle(noble);
    }
  }
}
