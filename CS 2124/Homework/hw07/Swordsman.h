/* Author: Kyle Martin
 *
 * This code was written for the class CS 2124
 *
 * This program is another version of the warrior program, but as an exercise
 *  in inheritance.
 *
 */

#ifndef WARRIORCRAFT_SWORDSMAN
#define WARRIORCRAFT_SWORDSMAN 1

#include "Protector.h"
#include <iostream>

namespace WarriorCraft
{
  class Swordsman : public Protector
  {
  public:
    using Protector::Protector;

    //Cute little display method - nothing complicated
    virtual void display(std::ostream&) const override;
  };
}
#endif
