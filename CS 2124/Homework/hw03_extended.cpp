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
 * Note: This program utilizes a CommandQueue,
 *  which may seem obsesive for this program,
 *  and it is.  This program was expanded out
 *  of class in a way that needed the command
 *  Queue to be what it is here, with more 
 *  additions. 
 * 
 * */


#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <sstream>
using namespace std;


//The command queue handles all "command stuff"
  //that is, it will read a command file to process
  //those raw commands and turn them into command 
  //struct which it will store, and run as the user
  //of this class specifices, or as the commands ask
//The techincal: stored as nodes in a vector
  //commands is the vector that holds the commands
  //nextCommandIndex - index of the next command to exec
  //lastCommandIndex - index of the last command in queue
  //insertCommandIndex - where to insert the next command
class CommandQueue
{
public:
/* Everything to be implimented in this class for compatibility of last program:
//Insert a commandNode into the commandQueue, and update commandQueue's flags
void insertCommand(CommandQueue& addingCommandQ, const CommandNode& commandToInsert);

//This function will read a file (default =
  //"warriors.txt", but if that fails, the 
  //program will prompt the user for another
  //file).  This function will return a
  //command queue to be proccessed by
  //another function (commands = strings).
  //The string is passed by value because I
  //desired to pass litteral filenames to
  //this function, and then use the variable,
  //inputFileName to accept a new file if the
  //given file fails to open.
CommandQueue readCommandFile(string inputFileName);

//Remove the next command from the command queue
  //and return that command
CommandNode front_pop(CommandQueue& commandSet);

//Interpret the next Command in the Command 
  //Queue (FIFO, First In First Out), and
  //execute that command.  Needs the active
  //commandQueue and active Warriors
void processCommand(CommandNode& command, vector <Warrior>& warriorSet); //Alternatively, could return a "commandType"

//Will process and run numberOfCommands number of commands. If numberOfCommands==0, run all commands (default)
void runCommands(CommandQueue& commandSet, vector <Warrior>& warriorSet, size_t numberOfCommands=0);

//This function will make sure that the name "warName" is not already in the vector.
bool isDouble(const vector <Warrior>& warriors, string warName);
*/
private:
	//A command node, holds the command string, the
	  //index of the next command to be executed in
	  //the commandQueue commands vector, and
	  //whether or not this command has been executed
	//Optinmally this would be implimented in a linked,
	  //but I don't believe that we are yet allowed to
	  //impliment those for this class
	struct CommandNode{
		string command;
		size_t nextCommand=0;
		bool hasBeenExecuted=false;
		
		CommandNode(string commandInit):command(commandInit){}
	};
	
	vector <CommandNode> commands;
	size_t nextCommandIndex = 0;
	size_t lastCommandIndex = 0;
	size_t insertCommandIndex = 0;
};


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
		{ rabble.emplace_back(warriorName, weaponName, weaponPower); }
		
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
	}
	
/* Everything to be implimented in this class for compatibility of last program:



//The Status command (as a function)
void statusCommand(const vector <Warrior>& warriors);\
*/
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
			statusStream << " warrior haviing killed " << kills << " other warriors using " << weapon.getName() << " which has a power of " << weapon.getPower() << "." << endl;
			return statusStream.str();
		}
		
		void print() const
			{ cout << getPrint(); }
		
		string getPrintSimple() const
			{ return  name + " holds " + weapon.getName() + ".\n"; }
			
		void printSimple() const
			{ cout << name << " holds " << weapon.getName() << ".\n"; }
			
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


int main()
{
	TheRabble regiment;
	
	string warOne = "tim";
	string wepName = "Weapon";
	regiment.add(warOne, wepName, 20);
	string warTwo = "jon";
	regiment.add(warTwo, wepName, 1);
	
	regiment.battle(warOne, warTwo);
	
	regiment.report();
	
	//Create and populate the command queue
	//CommandQueue commandSet = readCommandFile("warriors.txt");
	
	//Run all commands
	//runCommands(commandSet, regiment);
}


/*
//Insert a commandNode into the commandQueue, and update commandQueue's flags
void insertCommand(CommandQueue& addingCommandQ, const CommandNode& commandToInsert)
{
	//if there are no availible spots, tack it on to the end
	if (addingCommandQ.insertCommandIndex == addingCommandQ.commands.size())
	{
		addingCommandQ.commands.push_back(commandToInsert);
		if (addingCommandQ.lastCommandIndex != addingCommandQ.commands.size())
			addingCommandQ.commands[addingCommandQ.lastCommandIndex].nextCommand=addingCommandQ.commands.size(); //Link the previous "last command" to this command, if it exists"
		addingCommandQ.lastCommandIndex=addingCommandQ.commands.size(); //Set this as the last command
		++addingCommandQ.insertCommandIndex; //increment the index.  Since it was already at the end, it's safe to assume that the queue is full before this point
	} else //Assumed: at least one other node exists
	{
		addingCommandQ.commands[addingCommandQ.insertCommandIndex]=commandToInsert;
		addingCommandQ.commands[addingCommandQ.lastCommandIndex].nextCommand=addingCommandQ.insertCommandIndex; //Link the previous "last command" to this command
		addingCommandQ.lastCommandIndex=addingCommandQ.commands.size(); //Set this as the last command
		
		//Update the insertCommandIndex
		size_t index = addingCommandQ.insertCommandIndex;
		while (!addingCommandQ.commands[index].hasBeenExecuted && index < addingCommandQ.commands.size())
			++index;
		addingCommandQ.insertCommandIndex=index;
	}
}


CommandQueue readCommandFile(string inputFileName)
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
	
	//Input each line (each command) into a node, then add them each to the commandQueue
	string command;
	CommandQueue commandSet;
	while (getline(commandFile, command))
	{
		if (command.size() > 1)  //If the line is not just an endline
			insertCommand(commandSet, CommandNode(command));
	}
	return commandSet;
}


//Remove the next command from the command queue
  //and return that command
CommandNode front_pop(CommandQueue& commandSet)
{
	//If there's no next command, return a "already executed" "status" command
	if (commandSet.nextCommandIndex == commandSet.commands.size())
	{
		cerr << "There are no commands to execute!\n";
		CommandNode falseEntry("Status");
		falseEntry.hasBeenExecuted = true;
		return falseEntry;
	}
	
	//Clone the command
	CommandNode nextCommand = commandSet.commands[commandSet.nextCommandIndex];
	//Will mark as executed, though it is entirely possible that is has not been
	commandSet.commands[commandSet.nextCommandIndex].hasBeenExecuted = true;
	//Check if there is a next command chained after this
	if (commandSet.commands[commandSet.nextCommandIndex].nextCommand == commandSet.commands.size()) // No, there isn't
	{
		CommandQueue newQueue;
		commandSet = newQueue; //Reset all flags. empty command queue
	} else //Yes, there is
		commandSet.nextCommandIndex = commandSet.commands[commandSet.nextCommandIndex].nextCommand; //Set new values for commandQueue
	return nextCommand;
}

//Interpret the next Command in the Command 
  //Queue (FIFO, First In First Out), and
  //execute that command.  Needs the active
  //commandQueue and active Warriors
void processCommand(CommandNode& command, vector <Warrior>& warriorSet)
{
	//Create a stream as to process the command (a whole line) word by word.
	istringstream commandString(command.command);
	
	string commandName;
	commandString >> commandName; //get command
	
	//Determine which command is being invoked, and run that command
	if (commandName == "Status")
		statusCommand(warriorSet);
	else if (commandName == "Warrior")
	{
		string warOne;
		int strength;
		commandString >> warOne; //get warrior name
		commandString >> strength; //get warrior strength
		if (!isDouble(warriorSet, warOne))
			warriorSet.push_back(warriorCommand(warOne, strength));
	}
	else if (commandName == "Battle")
	{
		string warOne;
		string warTwo;
		commandString >> warOne; //get warrior name
		commandString >> warTwo; //get warrior name
		battleCommand(warOne, warTwo, warriorSet);
	}
	else
		cerr << "Command not found\n";
}


//Will process and run numberOfCommands number of commands. If numberOfCommands==0, run all commands (default)
void runCommands(CommandQueue& commandSet, vector <Warrior>& warriorSet, size_t numberOfCommands)
{
	if (numberOfCommands==0)
		numberOfCommands=commandSet.commands.size();
	
	//run the commands
	for (size_t index= 0; index < numberOfCommands; ++index)
	{
		CommandNode workingCommand = front_pop(commandSet);
		processCommand(workingCommand, warriorSet);
	}
}


//This function will make sure that the name "warName" is not already in the vector.
bool isDouble(const vector <Warrior>& warriors, string warName)
{
	for (const Warrior& inspect : warriors)
		if (inspect.name == warName)
			return true;
	return false;
}*/
