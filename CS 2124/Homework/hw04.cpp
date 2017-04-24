/* Author: Kyle Martin
 *
 * This code was written for the class CS 2124
 *
 * The purpose of this code is to simulate a
 *  game of "Nobles And Their Men".  One can
 *  create some Nobles, create some Warriors,
 *  assign Warriors to Nobles, and bash heads
 *  together.  Be warned: there's no error
 *  checking on whether warriors are assigned
 *  to multiple Nobles, so it's the user's job
 *  to be careful.
 *
 * */


#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <sstream>

using namespace std;

//The Warrior Class -- based on the warrior struct from the previous class
class Warrior
{
public:
	Warrior(const string& warriorName, const int strength): name(warriorName), strength(strength) {}

	void display() const
		{ cout << name << " of power " << strength << ".\n"; }

	string getName() const
		{ return name; }

	int getStrength() const
		{ return strength; }

	void damage(const double percentLeftAlive)
		{ strength *= percentLeftAlive; }

private:
	string name;
	double strength;
};


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
	void hire(Warrior& newBlood)
		{ army.push_back(&newBlood); }

	//Get rid of warriors
	void fire(const Warrior& firedBlood)
	{
		//Announce what's happening..
		cout << "\n" << firedBlood.getName() << " you are dishonerably excused from service!\n\n";

		//Sort the odd guy out
		for (size_t i = 0; i < army.size(); ++i)
			if (army[i] == &firedBlood)
			{
				army[i] = army[army.size()-1];
				army.pop_back();
				break;
			}
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
				{ cout << name << " and " << enemy.name << " are both already dead!!\n"; }
			else if (myStrength == 0)
					{ cout << name << " is already dead!\n"; }
			else if (enemyStrength == 0)
				{ cout << enemy.name << " is already dead!\n"; } //Bug in original version - printed wrong name
			return;
		}

		//Battle it out and assign damage
		const double deathMultiplier = 0; //If someone dies, this is what their death looks like
		if (myStrength == enemyStrength)
		{
			cout << "Mutual Annihalation: " << name << " and " << enemy.name << " both die at each other's hands.\n";
			damage(deathMultiplier);
			enemy.damage(deathMultiplier);
		}
		else if (myStrength < enemyStrength)
		{
			cout << enemy.name << " defeats " << name << "!\n";
			damage(deathMultiplier);
			enemy.damage(myStrength/enemyStrength);
		}
		else if (myStrength > enemyStrength)
		{
			cout << name << " defeats " << enemy.name << "!\n";
			enemy.damage(deathMultiplier);
			damage(enemyStrength/myStrength);
		}

	}

	//The Status command (for all warriors)
	void display() const
	{
		//Show off the Noble
		cout << "\n" << name << " has an army of " << army.size() << "!\n";

		//Print all warriors
		for (Warrior* inspect : army)
		{
			cout << "\t";
			inspect->display();
		}
	}

private:
	//Determine the army's collective strength
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

	vector <Warrior*> army;
	string name;
};


int main()
{
	Noble art("King Arthur");
	Noble lance("Lancelot du Lac");
	Noble jim("Jim");
	Noble linus("Linus Torvalds");
	Noble billie("Bill Gates");

	Warrior cheetah("Tarzan", 10);
	Warrior wizard("Merlin", 15);
	Warrior theGovernator("Conan", 12);
	Warrior nimoy("Spock", 15);
	Warrior lawless("Xena", 20);
	Warrior mrGreen("Hulk", 8);
	Warrior dylan("Hercules", 3);

	jim.hire(nimoy);
	lance.hire(theGovernator);
	art.hire(wizard);
	lance.hire(dylan);
	linus.hire(lawless);
	billie.hire(mrGreen);
	art.hire(cheetah);

	jim.display();
	lance.display();
	art.display();
	linus.display();
	billie.display();

	art.fire(cheetah);
	art.display();

	art.battle(lance);
	jim.battle(lance);
	linus.battle(billie);
	billie.battle(lance);
}
