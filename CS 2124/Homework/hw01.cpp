/* Author: Kyle Martin
 * 
 * This code was written for the class CS 2124
 * 
 * The purpose of this code is to read a file, 
 *  "encrypted.txt", which is a text encrypted 
 *  using a basic Ceasar cypher with the rotation
 *  count at the beginning of the file, and 
 *  output the decrypted text to the standard 
 *  output stream, cout.
 * 
 * */


#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>
#include <stdlib.h>
using namespace std;


//This function will accept a encrypted character (which is any lowercase character), crptChar, decrypt it by rotating it "rotate" steps backwards, and return it.
char decryptChar(char crptChar, int rotate);

//This function will accept a encrypted string, crptString, decrypt it by rotating each acceptable char "rotate" steps backwards.  This function will change the inputed string.
void decryptString(string& crptString, int rotate);


int main()
{
    //Read file, make sure everything is okay
    ifstream encryptedFile("encrypted.txt");
    if (!encryptedFile)
    {
        cerr<<"The file failed to open.  Closing program.\n";
        exit(1);
    }
    
    //Get the rotate amount from the file
    int rotate;
    encryptedFile >> rotate;
    
    //Get each line from the file, decrypt them, store them
    string lineString;
    //Clear EOF, get to text
    getline(encryptedFile, lineString);
    
    //Parse entire file, sotre in vector
    vector<string> decryptedText;
    while (getline(encryptedFile, lineString))
    {
        decryptString(lineString, rotate);      //Fetch line
        decryptedText.push_back(lineString);    //Decrypt line
    }
    
    //Print text in proper order (backwards)
    for (int lineNumber = decryptedText.size()-1; lineNumber >= 0; --lineNumber)
    {
        cout << decryptedText[lineNumber] << endl;
    }    
}


//This function will accept a encrypted character (which is any lowercase character), crptChar, decrypt it by rotating it "rotate" steps backwards, and return it.
char decryptChar(char crptChar, int rotate)
{
    //If the character is lowercase, rotate it
    if (crptChar<='z' && crptChar>='a')
    {
        crptChar -= rotate;
        //Wrap-around
        if (crptChar < 'a')
        {
            crptChar += 26;
        }
    }
    return crptChar;
}


//This function will accept a encrypted string, crptString, decrypt it by rotating each acceptable char "rotate" steps backwards.  This function will change the inputed string.
void decryptString(string& crptString, int rotate)
{
    for (char& crptChar : crptString)
    {
        crptChar=decryptChar(crptChar, rotate);
    }
}
