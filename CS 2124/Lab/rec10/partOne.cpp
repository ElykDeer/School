// Author: Kyle Martin
// This code was writen for the class CS 2124
// This recitation serves as a exercise in inheritance and polymophism

#include <iostream>
#include <vector>
using namespace std;

//Base class for all intruments.  All instruments make sounds
class Instrument
{
public:
    //To make this class more flexible
    virtual ~Instrument() {}

    //Public display
    virtual void makeSound(ostream&) const = 0;
};
//Default makeSound function
void Instrument::makeSound(ostream& os=cout) const
    { os << "To make a sound ... "; }


//We have three families of instruments: Wind, String, Percussion
class Wind : public Instrument
{
public:
    //Wind instruments come with a sized mouthpiece - no gaurds on the size yet
    Wind(const unsigned int mouthPieceSize) : mouthPieceSize(mouthPieceSize) {}
    virtual ~Wind() {}

    //Public display
    virtual void makeSound(ostream& os=cout) const override
    {
        Instrument::makeSound();
        os << "blow on my mouthpiece of size " << mouthPieceSize;
    }
private:
    unsigned int mouthPieceSize;
};
//All the instruments!
#include "windFamily.cpp"


class String : public Instrument
{
public:
    //String Instruments are created with one, pitched string
    String(unsigned int stringPitch) : stringPitch(stringPitch) {}
    virtual ~String() {}

    //Public display
    virtual void makeSound(ostream& os=cout) const override
    {
        Instrument::makeSound();
        os << "bow my string of pitch " << stringPitch;
    }
private:
    unsigned int stringPitch;
};
//All the instruments!
#include "stringFamily.cpp"


class Percussion : public Instrument
{
public:
    virtual ~Percussion() {}

    //Public display
    virtual void makeSound(ostream& os=cout) const override
    {
        Instrument::makeSound();
        os << "hit me!";
    }
};
//All the instruments!
#include "percussionFamily.cpp"

class Musician {
public:
	Musician() : instr( NULL ) {}
	void acceptInstr( Instrument & i ) { instr = &i; }
	Instrument* giveBackInstr( ) {
		Instrument* tmp(instr);
		instr = NULL;
		return tmp;
	}
	void testPlay() const {
		if( instr )
			instr->makeSound();
		else
			cerr << "have no instr\n";
	}
private:
	Instrument* instr;
};


//The renting industry for instruments
  //The instrument mill?
class MILL
{
public:
    void receiveInstr(Instrument& newInstra)
    {
        //Test the instrument!
        newInstra.makeSound();
        cout << endl;

        //Find a null slot to fill, or append to the end
        for (Instrument*& instra : inventory)
            if (instra == nullptr)
            {
                instra = &newInstra;
                return;
            }
        //No additional room, put it at the back
        inventory.push_back(&newInstra);
    }

    Instrument* loanOut()
    {
        //Check if we have anything to loan our
        for (Instrument*& instra : inventory)
            if (instra != nullptr)
            {
                Instrument* loaner = instra;
                instra = nullptr;
                return loaner;
            }

        //No instruments at this time
        return nullptr;
    }

    void dailyTestPlay() const
    {
        for (Instrument* test : inventory)
        {
            if (test != nullptr)
            {
                test->makeSound();
                cout << endl;
            }
        }
    }
private:
    vector <Instrument*> inventory;
};


// PART ONE
int main()
{

  cout << "Define some instruments ----------------------------------------\n";
  Drum drum;
  Cello cello(673);
  Cymbal cymbal;
  Trombone tbone( 4 );
  Trumpet trpt( 12 ) ;
  Violin violin( 567 ) ;

  // use the debugger to look at the mill
  cout << "Define the MILL ------------------------------------------------\n";
  MILL mill;

  cout << "Put the instruments into the MILL ------------------------------\n";
  mill.receiveInstr( trpt );
  mill.receiveInstr( violin );
  mill.receiveInstr( tbone );
  mill.receiveInstr( drum );
  mill.receiveInstr( cello );
  mill.receiveInstr( cymbal );

  cout << "Daily test -----------------------------------------------------\n";
  cout << endl;
  cout << "dailyTestPlay()" << endl;
  mill.dailyTestPlay();
  cout << endl;

  cout << "Define some Musicians-------------------------------------------\n";
  Musician j;
  Musician jj;
  Musician q;

  cout << "TESTING: q.acceptInstr( *mill.loanOut() );-----------------------\n";
  q.testPlay();
  cout << endl;
  q.acceptInstr( *mill.loanOut() );
  cout << endl;
  q.testPlay();
  cout << endl;
  cout << "dailyTestPlay()" << endl;
  mill.dailyTestPlay();

  cout << endl << endl;

  q.testPlay();
  cout << endl;
  mill.receiveInstr( *q.giveBackInstr() );
  j.acceptInstr( *mill.loanOut() );
  q.acceptInstr( *mill.loanOut() );
  cout << endl;
  q.testPlay();
  cout << endl;
  j.testPlay();
  cout << endl;
  cout << "dailyTestPlay()" << endl;
  mill.dailyTestPlay();

  cout << "TESTING: mill.receiveInstr( *q.giveBackInstr() ); -------------\n";

  // fifth
  mill.receiveInstr( *q.giveBackInstr() );
  cout << "TESTING: mill.receiveInstr( *j.giveBackInstr() ); -------------\n";
  mill.receiveInstr( *j.giveBackInstr() );


  cout << endl;
  cout << "dailyTestPlay()" << endl;
  mill.dailyTestPlay();
  cout << endl;

  cout << endl;

}
