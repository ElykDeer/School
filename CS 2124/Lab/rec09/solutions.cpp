/* Author: Kyle Martin
 *
 * This code was written for the class CS 2124
 *
 * This code serves as an exercise in inheritance
 *
 * */

////////////////////////////////////////////////////////////////////////////////

//Task One
/*
          Printed Material
        Book            Magazine
    Novel  TextBook
*/

////////////////////////////////////////////////////////////////////////////////
/*
//Task Two And Three:
#include <iostream>
using namespace std;

class PrintedMaterial {
public:
protected:
private:
    unsigned numberOfPages;
};

class Magazine : public PrintedMaterial {
public:
protected:
private:
};

class Book : public PrintedMaterial {
public:
protected:
private:
};

class TextBook : public Book {
public:
protected:
private:
};

class Novel : public Book {
public:
protected:
private:
};

// tester/modeler code
int main()
{
	TextBook t;
	Novel n;
	Magazine m;
}

////////////////////////////////////////////////////////////////////////////////

//Task Four:  Should Not Compile!
#include <iostream>
using namespace std;

class PrintedMaterial {
public:
    PrintedMaterial(unsigned numberOfPages) : numberOfPages(numberOfPages) {}
protected:
private:
    unsigned numberOfPages;
};

class Magazine : public PrintedMaterial {
public:
protected:
private:
};

class Book : public PrintedMaterial {
public:
protected:
private:
};

class TextBook : public Book {
public:
protected:
private:
};

class Novel : public Book {
public:
protected:
private:
};

////////////////////////////////////////////////////////////////////////////////

//Task Five: Should Not Compile!
#include <iostream>
using namespace std;

class PrintedMaterial {
public:
    PrintedMaterial(unsigned numberOfPages = 0) : numberOfPages(numberOfPages) {}
protected:
private:
    unsigned numberOfPages;
};

class Magazine : public PrintedMaterial {
public:
    Magazine(unsigned numberOfPages = 0) : PrintedMaterial(numberOfPages) {}
protected:
private:
};

class Book : public PrintedMaterial {
public:
    Book(unsigned numberOfPages = 0) : PrintedMaterial(numberOfPages) {}
protected:
private:
};

class TextBook : public Book {
public:
    TextBook(unsigned numberOfPages = 0) : Book(numberOfPages), PrintedMaterial(numberOfPages) {}
protected:
private:
};

class Novel : public Book {
public:
    Novel(unsigned numberOfPages = 0) : Book(numberOfPages), PrintedMaterial(numberOfPages) {}
protected:
private:
};

// tester/modeler code
int main()
{
	TextBook t;
	Novel n;
	Magazine m;
}

////////////////////////////////////////////////////////////////////////////////

//Task Six:
#include <iostream>
using namespace std;

class PrintedMaterial {
public:
    PrintedMaterial(unsigned numberOfPages = 0) : numberOfPages(numberOfPages) {}

    void displayNumPages() const { cout << numberOfPages; }
protected:
private:
    unsigned numberOfPages;
};

class Magazine : public PrintedMaterial {
public:
    Magazine(unsigned numberOfPages = 0) : PrintedMaterial(numberOfPages) {}
protected:
private:
};

class Book : public PrintedMaterial {
public:
    Book(unsigned numberOfPages = 0) : PrintedMaterial(numberOfPages) {}
protected:
private:
};

class TextBook : public Book {
public:
    TextBook(unsigned numberOfPages = 0) : Book(numberOfPages) {}
protected:
private:
};

class Novel : public Book {
public:
    Novel(unsigned numberOfPages = 0) : Book(numberOfPages) {}
protected:
private:
};

// tester/modeler code
int main()
{
	TextBook t;
	Novel n;
	Magazine m;

    //Task 6
    t.displayNumPages();
    n.displayNumPages();
}

////////////////////////////////////////////////////////////////////////////////

//Task Seven: Should not compile, textbook is accessing private members
#include <iostream>
using namespace std;

class PrintedMaterial {
public:
	PrintedMaterial( unsigned numPages )
		: numOfPages(numPages)
	{}
	void displayNumPages() const
	{ cout << numOfPages; }
protected:
private:
	unsigned numOfPages;
};

class Magazine : public PrintedMaterial {
public:
	Magazine( unsigned numPages )
		: PrintedMaterial(numPages)
	{}
protected:
private:
};

class Book : public PrintedMaterial {
public:
	Book( unsigned numPages )
		: PrintedMaterial(numPages)
	{}
protected:
private:
};

class TextBook : public Book {
public:
	TextBook( unsigned numPages, unsigned numIndxPgs  )
		: Book(numPages),
		  numOfIndexPages(numIndxPgs)
	{}
	void displayNumPages() const
	{
		cout << numOfIndexPages << endl;
		cout << numOfPages;
	}
protected:
private:
	unsigned numOfIndexPages;
};

class Novel : public Book {
public:
	Novel( unsigned numPages )
		: Book(numPages)
	{}
protected:
private:
};

////////////////////////////////////////////////////////////////////////////////

//Task Eight:
#include <iostream>
using namespace std;

class PrintedMaterial {
public:
    PrintedMaterial(unsigned numberOfPages = 0) : numberOfPages(numberOfPages) {}

    virtual void displayNumPages() const { cout << numberOfPages; }
protected:
private:
    unsigned numberOfPages;
};

class Magazine : public PrintedMaterial {
public:
    Magazine(unsigned numberOfPages = 0) : PrintedMaterial(numberOfPages) {}
protected:
private:
};

class Book : public PrintedMaterial {
public:
    Book(unsigned numberOfPages = 0) : PrintedMaterial(numberOfPages) {}
protected:
private:
};

class TextBook : public Book {
public:
    TextBook(unsigned numberOfPages = 0, unsigned numOfIndexPages = 0) : Book(numberOfPages), numOfIndexPages(numOfIndexPages) {}

    void displayNumPages() const override
    {
        cout << "Pages: \n ";
        PrintedMaterial::displayNumPages();
        cout << "\nIndex Pages: \n ";
        cout << numOfIndexPages << endl;
    }
protected:
private:
    unsigned numOfIndexPages;
};

class Novel : public Book {
public:
    Novel(unsigned numberOfPages = 0) : Book(numberOfPages) {}
protected:
private:
};

////////////////////////////////////////////////////////////////////////////////

//Task Nine And Ten And Eleven:
#include <iostream>
using namespace std;

class PrintedMaterial {
public:
    PrintedMaterial(unsigned numberOfPages = 0) : numberOfPages(numberOfPages) {}

    virtual void displayNumPages() const { cout << numberOfPages << endl; }
protected:
private:
    unsigned numberOfPages;
};

class Magazine : public PrintedMaterial {
public:
    Magazine(unsigned numberOfPages = 0) : PrintedMaterial(numberOfPages) {}
protected:
private:
};

class Book : public PrintedMaterial {
public:
    Book(unsigned numberOfPages = 0) : PrintedMaterial(numberOfPages) {}
protected:
private:
};

class TextBook : public Book {
public:
    TextBook(unsigned numberOfPages = 0, unsigned numOfIndexPages = 0) : Book(numberOfPages), numOfIndexPages(numOfIndexPages) {}

    void displayNumPages() const override
    {
        cout << "Pages: \n ";
        PrintedMaterial::displayNumPages();
        cout << "Index Pages: \n ";
        cout << numOfIndexPages << endl;
    }
protected:
private:
    unsigned numOfIndexPages;
};

class Novel : public Book {
public:
    Novel(unsigned numberOfPages = 0) : Book(numberOfPages) {}
protected:
private:
};

////////////////////////////////////////////////////////////////////////////////

//Task Twelve:
#include <iostream>
using namespace std;

class PrintedMaterial {
public:
    PrintedMaterial(unsigned numberOfPages = 0) : numberOfPages(numberOfPages) {}

    virtual void displayNumPages() const { cout << numberOfPages << endl; }
protected:
private:
    unsigned numberOfPages;
};

class Magazine : public PrintedMaterial {
public:
    Magazine(unsigned numberOfPages = 0) : PrintedMaterial(numberOfPages) {}
protected:
private:
};

class Book : public PrintedMaterial {
public:
    Book(unsigned numberOfPages = 0) : PrintedMaterial(numberOfPages) {}
protected:
private:
};

class TextBook : public Book {
public:
    TextBook(unsigned numberOfPages = 0, unsigned numOfIndexPages = 0) : Book(numberOfPages), numOfIndexPages(numOfIndexPages) {}

    void displayNumPages() const override
    {
        cout << "Pages: \n ";
        PrintedMaterial::displayNumPages();
        cout << "Index Pages: \n ";
        cout << numOfIndexPages << endl;
    }
protected:
private:
    unsigned numOfIndexPages;
};

class Novel : public Book {
public:
    Novel(unsigned numberOfPages = 0) : Book(numberOfPages) {}
protected:
private:
};

void displayNumberOfPages(const PrintedMaterial& printMe)
{
    printMe.displayNumPages();
}

*/
////////////////////////////////////////////////////////////////////////////////

//Task Thirteen, Fourteen, And Fifteen
#include <iostream>
#include <vector>
using namespace std;

class PrintedMaterial {
public:
    PrintedMaterial(unsigned numberOfPages = 0) : numberOfPages(numberOfPages) {}

    virtual void displayNumPages(ostream& os=cout) const = 0;

    unsigned getPages() const
        { return numberOfPages; }
protected:
private:
    unsigned numberOfPages;
};



class Magazine : public PrintedMaterial {
public:
    Magazine(unsigned numberOfPages = 0) : PrintedMaterial(numberOfPages) {}

    virtual void displayNumPages(ostream& os=cout) const override
        { os << PrintedMaterial::getPages() << endl; }
protected:
private:
};

class Book : public PrintedMaterial {
public:
    Book(unsigned numberOfPages = 0) : PrintedMaterial(numberOfPages) {}

    virtual void displayNumPages(ostream& os=cout) const override
        { os << PrintedMaterial::getPages() << endl; }
protected:
private:
};

class TextBook : public Book {
public:
    TextBook(unsigned numberOfPages = 0, unsigned numOfIndexPages = 0):
            Book(numberOfPages), numOfIndexPages(numOfIndexPages) {}

    void displayNumPages(ostream& os=cout) const override
    {
        os << "Pages: \n " << PrintedMaterial::getPages() <<
                "\nIndex Pages: \n " << numOfIndexPages << endl;
    }
protected:
private:
    unsigned numOfIndexPages;
};

class Novel : public Book {
public:
    Novel(unsigned numberOfPages = 0) : Book(numberOfPages) {}

    virtual void displayNumPages(ostream& os=cout) const override
        { os << PrintedMaterial::getPages() << endl; }
protected:
private:
};

void displayNumberOfPages(const PrintedMaterial& printMe)
{
    printMe.displayNumPages();
}

ostream& operator<<(ostream& os, const PrintedMaterial& printMe)
{
    printMe.displayNumPages(os);
    return os;
}

// tester/modeler code
int main()
{
	TextBook t(12, 11);
	Novel n(39);
	Magazine m(4);

    //Task 6
    cout << "Displaying a TextBook then a Novel:\n";
    t.displayNumPages();
    n.displayNumPages();

    //Task 9 - No longer works as of Task 14
    //cout << "Displaying a TextBook sliced in to a PrintedMaterial:\n";
    //PrintedMaterial pm = t; // like putting a t into a vector of PrintedMaterials
    //pm.displayNumPages();

    //Task 10
    cout << "Displaying a TextBook through a PrintedMaterial pointer:\n";
    PrintedMaterial* pmPtr;
    pmPtr = &t;
    pmPtr->displayNumPages();

    //Task 12
    cout << "Calling universal print method on a TextBook then a Novel:\n";
    displayNumberOfPages(t);
    displayNumberOfPages(n);
    cout << "Using << operator to print a TextBook then a Novel:\n";
    cout << t << n;


    //Task 15
    cout <<"\nPrint Collection:\n";
	vector <PrintedMaterial*> printableObjects;
	printableObjects.push_back(&t);
	printableObjects.push_back(&n);
	printableObjects.push_back(&m);
    for( size_t i=0; i < printableObjects.size(); ++i )
	{
		printableObjects[i]->displayNumPages();
	}
    cout << "\nUsing << operator:\n";
    for( size_t i=0; i < printableObjects.size(); ++i )
	{
		cout << *printableObjects[i];
	}
}
