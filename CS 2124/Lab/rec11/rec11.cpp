/* Author: Kyle Martin
 *
 * This code was written for the class CS 2124
 *
 * This code serves as an exercise in linked lists
 *
 */

#include "ll.h"
#include <iostream>
#include <vector>
using namespace std;

void foo(LinkedList<int> list)
{
    cout << list << endl;
    return;
}

int main()
{
    LinkedList<int> myList;

    cout << "Testing pushBack() and output: \n";
    for(int i = 0; i < 20; ++i)
        myList.pushBack(i);

    cout << myList.getSize() << endl << myList << endl;

    cout << "Testing copy constructor: \n";
    foo(myList);
    LinkedList<int> otherList = myList;

    cout << otherList << endl;

    cout << "Testing popFront: \n";
    cout << otherList.popFront() << endl << otherList << endl;
    cout << "Testing popBack: \n";
    cout << otherList.popBack() << endl << otherList << endl;

    cout << "Testing clear: \n";
    otherList.clear(); //Only rids half of list?
    cout << "List: " << otherList << endl;

    cout << "Testing assignment operator: \n";
    otherList = myList;
    otherList[3] = 14;
    cout << otherList[3] << endl << otherList << endl;

    cout << "Testing pushAfter: \n";
    otherList.pushAfter(3, 15);
    cout << otherList << endl;
    cout << "Testing pushBefore: \n";
    otherList.pushBefore(3, 13);
    cout << otherList << endl;

    cout << "Testing popAfter: \n";
    cout << otherList.popAfter(4) << endl << otherList << endl;
    cout << "Testing popBefore: \n";
    cout << otherList.popBefore(3) << endl << otherList << endl;

    cout << "Testing list pushAfter: \n";
    otherList.pushAfter(3, myList);
    cout << "myList: " << myList << endl;
    cout << "otherList: " << otherList << endl;
    cout << "Testing list pushBefore: \n";
    otherList.pushBefore(3, myList);
    cout << "myList: " << myList << endl;
    cout << "otherList: " << otherList << endl;

    cout << "Testing subset search: \n";
    cout << otherList.match(myList) << endl;
    //Tested: Copy Control, PushFront/back, clear, popFront/Back, operator[],
    //          getSize, pushAfter/before, match

    cout << "Testing subset search: \n";
    LinkedList<int> mainList;
    mainList.pushBack(1);
    mainList.pushBack(2);
    mainList.pushBack(2);
    mainList.pushBack(2);
    mainList.pushBack(4);
    mainList.pushBack(4);
    LinkedList<int> subList;
    subList.pushBack(2);
    subList.pushBack(2);
    subList.pushBack(4);

    cout << "mainList: " << mainList << "\nsubList: " << subList << endl;
    cout << "Found match starting at index: " << mainList.match(subList) <<endl;

    cout << "Testing the this class works with other things!" << endl;
    LinkedList<string> stringll;
    stringll.pushBack("a");
    stringll.pushBack("b");
    stringll.pushBack("c");
    stringll.pushBack("d");
    stringll.pushBack("e");
    stringll.pushBack("f");
    stringll.pushBack("g");
    cout << stringll << endl;

    cout << "Testing if deliberately bad cases break the code: " << endl;
    stringll.pushAfter(22, "q");
    cout << stringll << endl;

    LinkedList<bool> bools;
    bools.clear(); //Clear empty list
    cout << bools << endl;
    cout << bools.popBack() << endl;
    cout << bools.popFront() << endl;
    cout << bools.popAfter(0) << endl;

    return 0;
}
