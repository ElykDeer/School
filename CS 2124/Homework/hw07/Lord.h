/* Author: Kyle Martin
 *
 * This code was written for the class CS 2124
 *
 * This program is another version of the warrior program, but as an exercise
 *  in inheritance.
 *
 */

#ifndef WARRIORCRAFT_LORD
#define WARRIORCRAFT_LORD 1

#include "NobleBase.h"
#include <string>
#include <iostream>
#include <vector>

namespace WarriorCraft
{
  class Lord : public NobleBase
  {
  public:
    using NobleBase::NobleBase;

    //Get Protectors!
    //Since this is non-user code, this one is different as to not redo work
    //(works by object, not by name) - the calle checks that both exist
    bool hires(Protector&);

    //Get rid of Protectors
    Protector* fire(const std::string&);

    //Be notified if a Protector runs away
    void noWeekNotice(const std::string&);

	//The Status command (also displays their Protectors)
    virtual void display(std::ostream&) const override;

    virtual void battle(NobleBase&) override;

  protected:
    virtual int getStrength() const override;

    //Simply multiply percentDamaged by current strength
    virtual void damage(const double) override;

  private:
    //Checks if a Noble already has hired a Protector
    Protector* owns(const std::string&) const;

	std::vector <Protector*> army;
  };
}
#endif
