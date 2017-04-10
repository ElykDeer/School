/* Author: Kyle Martin
 *
 * This code was written for the class CS 2124
 *
 * This program is another version of the warrior program, but as an exercise
 *  in inheritance.
 *
 */

#ifndef WARRIORCRAFT_PERSONWITHSTRENGTHTOFIGHT
#define WARRIORCRAFT_PERSONWITHSTRENGTHTOFIGHT 1

#include "NobleBase.h"
#include <string>
#include <iostream>

namespace WarriorCraft
{
  class PersonWithStrengthToFight : public NobleBase
  {
  public:
    //Constructor
    PersonWithStrengthToFight(const std::string&, const int);

    //The Status command
    virtual void display(std::ostream&) const override;

  protected:
    virtual int getStrength() const override;

    //Simply multiply percentDamaged by current strength
    virtual void damage(const double) override;

  private:
    int strength;
  };
}
#endif
