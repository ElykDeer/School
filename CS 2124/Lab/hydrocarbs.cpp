/* Author: Kyle Martin
 * 
 * This code was written for the class CS 2124
 * 
 * The purpose of this code is to read a file, 
 *  "hydrocards.txt", which is a list of
 *  hydrocarbons and their chemical formule,
 *  one on each line, and output them in the
 *  order of their ascending rank of thier
 *  carbon atoms.
 * 
 * */


#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>
using namespace std;


//For colors in such a way that it doesn't break compilation/print garbage
/* Short Color Reference:
 * -30 - Normal
 * -25 - Blink
 * 1 - Red
 * 2 - Green
 * 3 - Yellow
 * 4 - Blue
 */
#ifdef _WIN32
void startPaint(const int color) {}
void endPaint() {}
#else
void startPaint(const int color)
{
    /*istringstream colorOut; //Build a color sequence and output it
    colorOut << "\033[";
    colorOut << color + 30;
    colorOut << "m";
    string out;
    colorOut >> out;
    cout << out;
    */
    cout << "\033[" << color+30 << "m";
}
void endPaint()
{
    cout << "\033[0m";
}
#endif


//This will hold all the data for each hydrocarbon, being:
  //Number of each atom, all known names
struct Hydrocarbon
{
    vector <string> names;
    short hydrogens;
    short carbons;
    //Hydrocarbon(string n, short h, short c):names({n}), hydrogens(h), carbons(c){}
};


//This function reads the chemical file formula (promts if it couldn't open), and
  //puts constructed hydrocarbon structs into the given vector
void readChemicalFile(string inputFileName, vector <Hydrocarbon>& hydrocarbonCollection);

//This function searchs for a hydrocarbon chem form and returns its index, or the size of the vector if not found.
size_t hydrocarbinExists(const short carbonCount, const short hydrogenCount, 
                         const vector <Hydrocarbon>& hydrocarbonCollection);

//This function will list all chemical formulae and known names, in accending rank of carbon atoms
void listFormulae(const vector <Hydrocarbon>& hydrocarbonCollection);

//Main function
int main()
{
    //Create main hydrocarbon collection
    vector <Hydrocarbon> hydrocarbonCollection;
    
    //Read in the data from a given file
    readChemicalFile("hydrocarbs.txt", hydrocarbonCollection);
    
    //List the input, in the desired (min to max carbons) order
    listFormulae(hydrocarbonCollection);
}


//This function reads the chemical file formula (promts if it couldn't open), and
  //puts constructed hydrocarbon structs into the given vector
void readChemicalFile(string inputFileName, vector <Hydrocarbon>& hydrocarbonCollection)
{
    //Open and check filestream, prompt user if they want another file instead (if failed)
    ifstream hydrocarbonFile(inputFileName);
    while (!hydrocarbonFile)
    {
        //Prompt for another file, or not
        char tryAgain;
        startPaint(1);
        cerr << inputFileName << " failed to open. Would you like to try another file? (Y/n) ";
        endPaint();
        cin >> tryAgain;
        //If no, exit program
        if (tryAgain == 'n' || tryAgain == 'N')
        {
            startPaint(1);
            cerr << "No alternate file provided. Cannot continue, closing program.\n";
            endPaint();
            exit(1);
        }
        //Otherwise, get a new file
        cout << "Filename: ";
        cin >> inputFileName;
        hydrocarbonFile.open(inputFileName);        
    }

    //Input each line, token by tokern:
      // string, char, int, char, int
    string molName;
    char atomName;
    short carbonCount;
    short hydrogenCount;
    while (hydrocarbonFile >> molName)
    {
        carbonCount = hydrogenCount = 0;  //Reset atom count, for no confusion
        for (int i=0; i<2; ++i)
        {
            hydrocarbonFile >> atomName;
            if (atomName == 'C')
                hydrocarbonFile >> carbonCount;
            if (atomName == 'H')
                hydrocarbonFile >> hydrogenCount;
        }
        if (carbonCount == 0 || hydrogenCount == 0) //If the chemical is missing an atom, it's an invalid hydrocarbon, move to next loop
            continue;
        //If the hydrocarbon already exists, append this name to that name vector
        size_t hydrocarbonIndex = hydrocarbinExists(carbonCount, hydrogenCount, hydrocarbonCollection);
        if (hydrocarbonIndex != hydrocarbonCollection.size())
            hydrocarbonCollection[hydrocarbonIndex].names.push_back(molName);
        else //If hydrocarbon doesn't exist, make a new hydrocarbon
        {
            Hydrocarbon newHydrocarbon{{molName}, hydrogenCount, carbonCount};
            hydrocarbonCollection.push_back(newHydrocarbon);
        }
    }
}


//This function searchs for a hydrocarbon chem form and returns its index, or the size of the vector if not found.
size_t hydrocarbinExists(const short carbonCount, const short hydrogenCount, const vector <Hydrocarbon>& hydrocarbonCollection)
{
    //Loop through all hydrocarbons, by index, return index of matching chemical formula
    for (size_t index = 0; index < hydrocarbonCollection.size(); ++index)
        if (hydrocarbonCollection[index].carbons == carbonCount && hydrocarbonCollection[index].hydrogens == hydrogenCount)
            return index;
    return hydrocarbonCollection.size(); //return size if hydrocarbon was not found
}

//This function will list all chemical formulae and known names, in accending rank of carbon atoms
void listFormulae(const vector <Hydrocarbon>& hydrocarbonCollection)
{
    //Make sure that there are some hydrocarbons, exit if there aren't.
    if (hydrocarbonCollection.size() == 0)
    {
        startPaint(1);
        cerr << "No hydrocarbons have been loaded./n";
        endPaint();
        return;
    }
    
    //Find fewest and most count of carbons
    int minCarbons = hydrocarbonCollection[0].carbons;
    int maxCarbons = hydrocarbonCollection[0].carbons;
    for (const Hydrocarbon& inspectingHydroCarbon : hydrocarbonCollection)
    {
        if (inspectingHydroCarbon.carbons < minCarbons)
            minCarbons = inspectingHydroCarbon.carbons;
        if (inspectingHydroCarbon.carbons > maxCarbons)
            maxCarbons = inspectingHydroCarbon.carbons;
    }
    
    //print hydrocarbons, rank by rank, from minCarbons to maxCarbons
    for (; minCarbons <= maxCarbons; ++minCarbons)
        for (const Hydrocarbon& inspectingHydroCarbon : hydrocarbonCollection)
            if (inspectingHydroCarbon.carbons == minCarbons)
            {
                startPaint(2); //Print in green
                cout << "C" << inspectingHydroCarbon.carbons << "H" << inspectingHydroCarbon.hydrogens << " ";
                endPaint();
                for (const string& name : inspectingHydroCarbon.names)
                    cout << name << " ";
                cout << endl;
            }
}
