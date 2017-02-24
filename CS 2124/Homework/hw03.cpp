/* Author: Kyle Martin
 * 
 * This code was written for the class CS 2124
 * 
 * The purpose of this code is to read a file, 
 *  "warriors.txt", which is a set of commands,
 *  one on each line, and run a "battle
 *  simulation".  The commands supported are
 *  listed below.
 * 
 *  Warrior: Creates a Warrior, first parm
 *   is the name, followed by an int strength
 * 
 *  Status: Lists all current Warriors and 
 *   their respective Stregths
 * 
 *  Battle: Takes two parameters that must be
 *   two Warriors (if it is the same Warrior,
 *   that Warrior will kill themself), and
 *   will report the results of that Battle.
 * 
 * Please ignore anything with "__future__:"
 * 	before it, those are just comments to a
 *  future self of mine.
 * 
 * */


#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <sstream>
using namespace std;


//This class is going to hold all of the warriors for us,
  //deal with creating them, making them fight, and
  //returning status reports
    //The idea behind this is that there can be multiple
    //pools of warriors, perhaps for different leaders, 
    //and outside of this assignment I plan to extend
    //the functionality so that warriors can fight acrros
    //"rabbles"/clans/tribes whatever
class TheRabble
{
public:
	//The Warrior command (as a function)
	void add(const string& warriorName, const string& weaponName, const int weaponPower)
	{
		if (!exists(warriorName))
			rabble.emplace_back(warriorName, weaponName, weaponPower);
		else
			cerr << "The King commandeth that thall shalt not make copies of men!!\n\n";
	}
		
	//The Battle command (as a function)
	void battle(const string& nameOne, const string& nameTwo)
	{
		//Find the actual warrior objects (by index) in the vector (in this for loop, also error checks
		size_t warOneIndex = rabble.size();
		size_t warTwoIndex = rabble.size();
		//condition waits for both warriors to be found AND ensures no segfault
		for (size_t index = 0; (warOneIndex == rabble.size() || warTwoIndex == rabble.size()) && index < rabble.size(); ++index)
		{
			if (rabble[index].getName() == nameOne) //Assign First Name
				warOneIndex = index;
			if (rabble[index].getName() == nameTwo)  //Assign Second Name
				warTwoIndex = index;
			if ((warOneIndex == rabble.size() || warTwoIndex == rabble.size()) && index == rabble.size()-1) //Failsafe...At least ne of the names do not exist
			{
				cerr << "The King cries, '";
				if (warOneIndex == rabble.size())
					cerr << nameOne << " hast not shown! ";
				if (warTwoIndex == rabble.size())
					cerr << nameTwo << " has not shown! ";
				cerr << "This matcheth is cancel'd!!'\n";
				return; //Cancel the match
			}
		}
		
		//Fight the warriors!
		rabble[warOneIndex].battle(rabble[warTwoIndex]);
		
		cout << endl;
	}
	
	//The Status command (for one warrior)
	void report(const string& warName) const
	{
		//Find the warrior amongst the rabble
		for (const Warrior& inspect : rabble)
			if (inspect.getName() == warName)
				inspect.print();
	}
	
	//The Status command (for all warriors)
	void report() const
	{
		cout << endl;
		//Find out how many dead/alive warriors there are
		int aliveWarriors = 0;
		for (const Warrior& warrior : rabble)
			if (warrior.isAlive())
				aliveWarriors+=1;
		int deadWarriors = rabble.size()-aliveWarriors;
		
		if (aliveWarriors == 1) //Singular Alive Warrior Flavor Text
			cout << "Only one is truly fit to serve The King:\n";
		if (aliveWarriors > 1)  //Multiple Alive Warriors Flavor Text
			cout << "The following warriors are fit to serve their King:\n";
		
		for (const Warrior& warrior : rabble)
			if (warrior.isAlive())
				cout << " " << warrior.getPrint();
				
		if (deadWarriors > 0)//Any number of dead guys -- don't provide their full info
		{
			cout << "The following warriors are just a bit... Stale:\n";
			for (const Warrior& warrior : rabble)
				if (!warrior.isAlive())
					cout << " " << warrior.getPrintSimple();
		}
		cout << endl;
	}
	
	//This function will make sure that the name "warName" is not already in the vector.
	bool exists(const string& warName) const
	{
		for (const Warrior& inspect : rabble)
			if (inspect.getName() == warName)
				return true;
		return false;
	}
	
private:
	//The Warrior Class -- based on the warrior struct from the previous class
	class Warrior
	{
	public:
		Warrior(const string& warriorName, const string& weaponName, const int weaponPower): name(warriorName), weapon(weaponName, weaponPower) {}
		
		//This function will facilitate a fight between two warriors
		void battle(Warrior& enemy)
		{
			//Check if the warrior is killing themselves
			if  (name == enemy.name)//__future__: (this == &enemy)
			{
				weapon.dullen(weapon); //Destroy his weapon
				dead = true;
				++kills; //What? He /did/ kill another person...
				{//Flavor Text (bracketed so I can collapse the block) - if a warrior kills himself for the glory of The King
				cout << "'Silence!!', the King bellows. He stands up, extending his arm to the knight standing before him in the ring. '";
				cout << name << ", I hest thee, as thy king and holy leadeth'r, to did shed thy blood f'r the ent'rtainment of all who is't art h're tonight!'\n\n";
				cout << name << " looks down. He knows that by his honor he must obey his King, so he unsheaths his sword, holds it in both hands, ";
				cout << "and brings it down upon his flesh, spilling his insides over his shoes and onto the ground below him, which rushes up to welcome him.\n\n";
				cout << "The crowd goes wild and the King laughs, splashing some wine onto the silk of his shirt and the furs of the rug below his feet.\n\n"; }
				return;
			}
			
			//Pass enemy's weapon to this guy's weapon, and have the weapons do the talking
			//deathCondition will be (in reference to this warrior)
			int deathCondition = weapon.dullen(enemy.weapon);
			  //positive for no death,
			  //negative for absolute death
			  //zero for mutual annhilation with the other warrior
			  
			//Flavor Text
			cout << name << " 'gainst " << enemy.name << ". 'Square!', belches The King, and the fight ensues.\n";
			
			//Declare winners and update warrior stats
			if (deathCondition > 0)
			{
				cout << name << " hast defeat'd " << enemy.name << "!\n"; //Flavor Text
				//This warrior won!
				++kills;
				//Enemy warrior lost!
				enemy.dead = true;
			}
			if (deathCondition < 0)
			{
				cout << enemy.name << " has defeated " << name << "!\n"; //Flavor Text
				//Enemy warrior won!
				++enemy.kills;
				//this warrior died
				dead = true;
			}
			if (deathCondition == 0)
			{
				cout << name << " and " << enemy.name << " are equally matched, and hack each other to pieces!! The King approves!\n"; //Flavor Text
				//This warrior dies
				dead = true;
				++kills;
				//The enemy dies as well
				enemy.dead = true;
				++enemy.kills;
			}
		}
		
		//Returns a string with all of the info for the warrior...
		  //In case user wants to parse the info for some reason.
		string getPrint() const
		{
			ostringstream statusStream;
			statusStream << name << " is a ";
			if (kills > 5)
				statusStream << "truely mighty";
			else if (kills > 3)
				statusStream << "great";
			else if (kills > 1)
				statusStream << "bloodied";
			else if (kills > 0)
				statusStream << "novice";
			else
				statusStream << "pathetic";
			//Makes output easier to read __future__:
			statusStream << " warrior having killed\t" << kills << " other warriors using " << weapon.getName() << ", which has a power of\t" << weapon.getPower() << "." << endl;
			return statusStream.str();
		}
		
		void print() const
			{ cout << getPrint(); }
		
		string getPrintSimple() const
			{ return  name + " holds\t" + weapon.getName() + ".\n"; }
			
		void printSimple() const
			{ cout << getPrintSimple(); }
			
		string getName() const
			{ return name; }
			
		bool isAlive() const
			{ return !dead; }
		
		
	private:
		class Weapon
		{
		public:
			Weapon(const string& name, const int power): name(name), power(power) {}
			
			//Returns the power of this warrior's weapon so the warrior
			  //can determine if he's dead, and if so, how dead.
			int dullen(Weapon& enemyWeapon)
			{
				int difference = power - enemyWeapon.power;	
				if ((enemyWeapon.power - power) < 0)
					enemyWeapon.power = 0;
				else
					enemyWeapon.power = -difference;
				
				if (difference < 0)
					power = 0;
				else
					power = difference;
					
				return (difference);
			}
			
			string getName() const
				{ return name; } //__future__: give the blade a modifying name "The Terrifying", "The Hungry", etc..
			
			int getPower() const
				{ return power; }
				
		private:
			string name;
			int power;
		};
		

		string name;
		Weapon weapon;
		bool dead=false;
		int kills = 0;
	};
	
	//Where all warriors will be stored
	vector<Warrior> rabble;
};


//The function the reads the file and plays this game
 //Not constant because I want to prompt the user for a file if this one fails to open
void readFileAndRun(string inputFileName);


int main()
{
	//Just one call
	readFileAndRun("warriors.txt");
}


void readFileAndRun(string inputFileName)
{
	//Open and check filestream, prompt user if they want another file instead (if failed)
	ifstream commandFile(inputFileName);
	while (!commandFile)
	{
		//Prompt for another file, or not
		char tryAgain;
		cerr << inputFileName << " failed to open. Would you like to try another file? (Y/n) ";
		cin >> tryAgain;
		//If no, exit program
		if (tryAgain == 'n' || tryAgain == 'N')
		{
			cerr << "No alternate file provided. Cannot continue, closing program.\n";
			exit(1);
		}
		//Otherwise, get a new file
		cout << "Filename: ";
		cin >> inputFileName;
		commandFile.open(inputFileName);        
	}
	
	//What the commands will be running on
	TheRabble regiment;
	
	//Sort out what needs to be done
	string command;
	
	while (commandFile >> command)
	{
		if (command == "Warrior")
		{
			string warName, wepName;
			commandFile >> warName >> wepName;
			int wepPower;
			commandFile >> wepPower;
			regiment.add(warName, wepName, wepPower);
		}
		else if (command == "Battle")
		{
			string warOneName, warTwoName;
			commandFile >> warOneName >> warTwoName;
			regiment.battle(warOneName, warTwoName);
		}
		else if (command == "Status")
			regiment.report();
	}
}

