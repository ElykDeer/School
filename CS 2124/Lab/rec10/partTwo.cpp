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
    //"Normal" playing
    virtual void makeSound(ostream&, int) const = 0;
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

    //Everyone plays "normally" in a different way
    //virtual void makeSound(ostream&, int) const = 0;
private:
    unsigned int mouthPieceSize;
};
//All the instruments! ( we need for now)
class Trumpet : public Wind
{
public:
    using Wind::Wind;
    virtual void makeSound(ostream& os, int) const override
        { os << "Toot"; }
};
class Trombone : public Wind
{
public:
    using Wind::Wind;
    virtual void makeSound(ostream& os, int) const override
        { os << "Blat"; }
};


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

    //Everyone plays "normally" in a different way
    //virtual void makeSound(ostream&, int) const = 0;
private:
    unsigned int stringPitch;
};
//All the instruments!
class Cello : public String
{
public:
    using String::String;
    virtual void makeSound(ostream& os, int) const override
        { os << "Squawk"; }
};
class Violin : public String
{
public:
    using String::String;
    virtual void makeSound(ostream& os, int) const override
        { os << "Screech"; }
};


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
    //Everyone plays "normally" in a different way
    //virtual void makeSound(ostream&, int) const = 0;
};
//All the instruments!
class Cymbal : public Percussion
{
public:
    using Percussion::Percussion;
    virtual void makeSound(ostream& os, int) const override
        { os << "Chrash"; }
};
class Drum : public Percussion
{
public:
    using Percussion::Percussion;
    virtual void makeSound(ostream& os, int) const override
        { os << "Boom"; }
};


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
    void play(ostream& os=cout) const {
		if( instr )
			{ instr->makeSound(os, 1); }
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
        //Check for duplicates
        for (Instrument* inspect : inventory)
            if (inspect == &newInstra)
            {
                cerr << "We already own this instrument!\n";
                return;
            }

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

class Orch
{
public:
    void addPlayer(Musician& newMusician)
    {
        //Make sure there is room in the orchestra
        if (players.size() > 24)
        {
            cerr << "The orchestra is full!";
            return;
        }

        //Make sure this person is not already in the orchestra
        for (Musician*& inspect : players)
            if (inspect == &newMusician)
            {
                cerr << "This person is already in the orchestra!\n";
                return;
            }

        players.push_back(&newMusician);
    }

    void play(ostream& os=cout) const
    {
        for (Musician* player : players)
                { player->play(os); }

        os << endl;

    }
private:
    vector <Musician*> players;
};

// PART TWO
int main()
{
	// The initialization phase
    cout << endl << "----------------Part One----------------\n";

	Drum drum;
	Cello cello(673);
	Cymbal cymbal;
	Trombone tbone( 4 );
	Trumpet trpt( 12 ) ;
	Violin violin( 567 ) ;

    // use the debugger to look at the mill
    cout << "Define the MILL ------------------------------------------------\n";
    MILL millo;

    cout << "Put the instruments into the MILL ------------------------------\n";
    millo.receiveInstr( trpt );
    millo.receiveInstr( violin );
    millo.receiveInstr( tbone );
    millo.receiveInstr( drum );
    millo.receiveInstr( cello );
    millo.receiveInstr( cymbal );

    cout << "Daily test -----------------------------------------------------\n";
    cout << endl;
    cout << "dailyTestPlay()" << endl;
    millo.dailyTestPlay();
    cout << endl;

    cout << "Define some Musicians-------------------------------------------\n";
    Musician j;
    Musician jj;
    Musician q;

    cout << "TESTING: q.acceptInstr( *mill.loanOut() );-----------------------\n";
    q.testPlay();
    cout << endl;
    q.acceptInstr( *millo.loanOut() );
    cout << endl;
    q.testPlay();
    cout << endl;
    cout << "dailyTestPlay()" << endl;
    millo.dailyTestPlay();

    cout << endl << endl;

    q.testPlay();
    cout << endl;
    millo.receiveInstr( *q.giveBackInstr() );
    j.acceptInstr( *millo.loanOut() );
    q.acceptInstr( *millo.loanOut() );
    cout << endl;
    q.testPlay();
    cout << endl;
    j.testPlay();
    cout << endl;
    cout << "dailyTestPlay()" << endl;
    millo.dailyTestPlay();

    cout << "TESTING: mill.receiveInstr( *q.giveBackInstr() ); -------------\n";

    // fifth
    millo.receiveInstr( *q.giveBackInstr() );
    cout << "TESTING: mill.receiveInstr( *j.giveBackInstr() ); -------------\n";
    millo.receiveInstr( *j.giveBackInstr() );


    cout << endl;
    cout << "dailyTestPlay()" << endl;
    millo.dailyTestPlay();
    cout << endl;


    cout << endl << "----------------Part Two----------------\n";

	MILL mill;
	mill.receiveInstr( trpt );
	mill.receiveInstr( violin );
	mill.receiveInstr( tbone );
	mill.receiveInstr( drum );
	mill.receiveInstr( cello );
	mill.receiveInstr( cymbal );

	Musician bob;
	Musician sue;
	Musician mary;
	Musician ralph;
	Musician jody;
	Musician morgan;

	Orch orch;

	// THE SCENARIO

	//Bob joins the orchestra without an instrument.
	orch.addPlayer(bob);

	//The orchestra performs
	cout << "orch performs\n";
	orch.play();

	//Sue gets an instrument from the MIL2 and joins the orchestra.
	sue.acceptInstr( *mill.loanOut() );
	orch.addPlayer(sue);

	//Ralph gets an instrument from the MIL2.
	ralph.acceptInstr( *mill.loanOut() );

	//Mary gets an instrument from the MIL2 and joins the orchestra.
	mary.acceptInstr( *mill.loanOut() );
	orch.addPlayer(mary);

	//Ralph returns his instrument to the MIL2.
	mill.receiveInstr( *ralph.giveBackInstr() );

	//Jody gets an instrument from the MIL2 and joins the orchestra.
	jody.acceptInstr( *mill.loanOut() );
	orch.addPlayer(jody);

	// morgan gets an instrument from the MIL2
	morgan.acceptInstr( *mill.loanOut() );

	//The orchestra performs.
	cout << "orch performs\n";
	orch.play();

	//Ralph joins the orchestra.
	orch.addPlayer(ralph);

	//The orchestra performs.
	cout << "orch performs\n";
	orch.play();

	// bob gets an instrument from the MIL2
	bob.acceptInstr( *mill.loanOut() );

	// ralph gets an instrument from the MIL2
	ralph.acceptInstr( *mill.loanOut() );

	//The orchestra performs.
	cout << "orch performs\n";
	orch.play();

	//Morgan joins the orchestra.
	orch.addPlayer(morgan);

	//The orchestra performs.
	cout << "orch performs\n";
	orch.play();

    orch.addPlayer(jody);

} // main
