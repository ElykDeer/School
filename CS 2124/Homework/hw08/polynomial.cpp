#include "polynomial.h"
using namespace std;

ostream& operator<<(ostream& os, const Polynomial& toPrint)
{
  toPrint.recvPrintHelper(toPrint.head, os);
  return os;
}

bool operator==(const Polynomial& lhs, const Polynomial& rhs)
{
  if(lhs.degreeOfPoly != rhs.degreeOfPoly)
    return false;

  Polynomial::Node* rhsNode = rhs.head;
  Polynomial::Node* lhsNode = lhs.head;

  for(size_t i = 0; i < rhs.degreeOfPoly; ++i)
  {
    if(rhsNode->data != lhsNode->data)
      return false;
    rhsNode = rhsNode->next;
    lhsNode = lhsNode->next;
  }
  return true;
}

bool operator!=(const Polynomial& rhs, const Polynomial& lhs)
{
  return !(rhs==lhs);
}

Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs)
{
  size_t maxDegree = 0;
  size_t minDegree = 0;
  if(lhs.degreeOfPoly > rhs.degreeOfPoly)
  {
    maxDegree = lhs.degreeOfPoly;
    minDegree = rhs.degreeOfPoly;
  }
  else
  {
    maxDegree = rhs.degreeOfPoly;
    minDegree = lhs.degreeOfPoly;
  }

  //For coefficients
  Polynomial::Node* rhsNode = rhs.head;
  Polynomial::Node* lhsNode = lhs.head;
  Polynomial sum;
  for(size_t degree = 0; degree < minDegree; ++degree)
  {
    sum.pushBack(rhsNode->data + lhsNode->data);

    rhsNode = rhsNode->next;
    lhsNode = lhsNode->next;
  }
  if(minDegree == maxDegree)
  {
    //Clear zeros at the front
    while(sum.tail->data==0)
        sum.popBack();
    return sum;
  }

  if(minDegree == lhs.degreeOfPoly) //rhs is bigger
  {
    for(size_t i  = (maxDegree-minDegree); i <= maxDegree; ++i)
    {
      sum.pushBack(rhsNode->data);
      rhsNode = rhsNode->next;
    }
  }
  else //lhs is bigger
  {
    for(size_t i  = (maxDegree-minDegree); i <= maxDegree; ++i)
    {
      sum.pushBack(lhsNode->data);
      lhsNode = lhsNode->next;
    }
  }
  //Clear zeros at the front
  while(sum.tail->data==0)
      sum.popBack();
  return sum;
}

Polynomial& Polynomial::operator+=(const Polynomial& rhs)
{
  size_t maxDegree = 0;
  size_t minDegree = 0;
  if(degreeOfPoly > rhs.degreeOfPoly)
  {
    maxDegree = degreeOfPoly;
    minDegree = rhs.degreeOfPoly;
  }
  else
  {
    maxDegree = rhs.degreeOfPoly;
    minDegree = degreeOfPoly;
  }

  //For coefficients
  Polynomial::Node* rhsNode = rhs.head;
  Polynomial::Node* myNode = head;
  for(size_t degree = 0; degree < minDegree; ++degree)
  {
    myNode->data += rhsNode->data;

    rhsNode = rhsNode->next;
    myNode = myNode->next;
  }
  if(minDegree == maxDegree)
  {
    //Clear zeros at the front
    while(tail->data==0)
      popBack();
    return *this;
  }

  if(minDegree == degreeOfPoly) //rhs is bigger
  {
    for(size_t i  = (maxDegree-minDegree); i <= maxDegree; ++i)
    {
      pushBack(rhsNode->data);
      rhsNode = rhsNode->next;
    }
  }
  //Clear zeros at the front
  while(tail->data==0)
      popBack();
  return *this;
}


//Copy Control
Polynomial::Polynomial() : degreeOfPoly(0), head(nullptr), tail(nullptr) {}

Polynomial::Polynomial(const vector<int>& coefficients)
  : degreeOfPoly(0), head(nullptr), tail(nullptr)
{
  for(const int co : coefficients)
    pushFront(co);
}

Polynomial::Polynomial(const Polynomial& toCopy)
: degreeOfPoly(toCopy.degreeOfPoly),  head(recvCopyHelper(toCopy.head)), tail(&getNode(degreeOfPoly-1))
{
  /*degreeOfPoly = toCopy.; //Set up my vars
  head = recvCopyHelper(toCopy.head); //Actually copy the linkedList
  tail = &getNode(degreeOfPoly); //Only time that we need to find the tail*/
}

Polynomial::~Polynomial()
{
  clear();
}

Polynomial& Polynomial::operator=(const Polynomial& toCopy)
{
  if(this == &toCopy)
    return *this;

  clear();

  degreeOfPoly = toCopy.degreeOfPoly;
  head = recvCopyHelper(toCopy.head);  //Actually copy the linkedList
  tail = &getNode(degreeOfPoly-1);  //The only other time we need to find the tail

  return *this;
}


//Polynomial Builders
void Polynomial::pushFront(const int newNodeData)
{
  head = new  Polynomial::Node(newNodeData, head);
  if(!tail)
    tail = head;
  ++degreeOfPoly;
}

void Polynomial::pushBack(const int newNodeData)
{
  if(tail)
    tail = tail->next = new Polynomial::Node(newNodeData, nullptr);
  else
    head = tail = new Polynomial::Node(newNodeData, nullptr);
  ++degreeOfPoly;
}

//Polynomial Teardowners
int Polynomial::popFront()
{
  if(!head)
  {
    cerr << "No head\n";
    return 0;
  }

  //Save some stuff
  int oldFrontData = head->data;
   Polynomial::Node* oldHead = head;

  //Set new head
  head = head->next;

  //Remove oldHead
  delete oldHead;
  --degreeOfPoly;

  return oldFrontData;
}

int Polynomial::popBack()
{
  if(!tail)
  {
    cerr << "No head\n";
    return 0;
  }

  //Save some stuff
  int oldTailData = tail->data;
  Polynomial::Node* oldTail = tail;

  //Set new tail
  tail = &getNode(degreeOfPoly-2);

  //Remove oldHead
  delete oldTail;
  --degreeOfPoly;

  if(tail) //If it's a no list.. Well, it's a no list
    tail->next=nullptr; //No dangles!!

  return oldTailData;
}

void Polynomial::clear()
{
  while(degreeOfPoly)
    popFront();  //Just use a function we already have
  //Just double checking
  head = nullptr;
  tail = nullptr;
  degreeOfPoly = 0;
}

//Non-Destructive Accessors/Node Changer
int Polynomial::operator[](const size_t index) const
{
  return getNode(index).data;
}

int& Polynomial::operator[](const size_t index)
{
  return getNode(index).data;
}

size_t Polynomial::degree() const //getsize
{
  return degreeOfPoly;
}

//Evaluate polynomial at X
int Polynomial::evaluate(const int x) const
{
  Polynomial::Node* index = head; //For coefficients
  int total = 0;
  for(size_t degree = 0; degree < degreeOfPoly; ++degree)
  {
    int partial = 1;
    for(size_t multiplier = 0; multiplier < degree; ++multiplier)
    {
      partial *= x;
    }
    total += (partial*index->data);
    index = index->next;
  }
  return total;
}

Polynomial::Node::Node(const int data, Node* link)
  : data(data), next(link) {}

//Recursive copy-helper function - WARNING, possibly dangerous (but pffft)
 Polynomial::Node* Polynomial::recvCopyHelper(const Polynomial::Node* node) const
{
  if(node) { return (new  Polynomial::Node(node->data, recvCopyHelper(node->next))); }
  return nullptr;
}

void Polynomial::recvPrintHelper(const Polynomial::Node* node, ostream& os, size_t degree) const
{
  if(node)
  {
    recvPrintHelper(node->next, os, ++degree);

    //Mainly Just nice formating stuff
    if(degree<(degreeOfPoly))
    {
      if(node->data > 0)
      {
          //os << "Deg{" << degree << '}' << "Deg-O-P{" << degreeOfPoly << '}';
          os << " + " << node->data;
      }
      else if(node->data < 0)
      {
          os << " - " << (node->data*-1);
      }
      else
          return;
    }
    else
      os << node->data;

    if(degree>2)
        os << "x^" << degree-1;
    else if(degree>1)
        os << "x";
  }
}

 Polynomial::Node& Polynomial::getNode(const size_t index) const
{
  Polynomial::Node* currentNode = head;
  for(size_t i = 0; i < index; ++i)
      currentNode = currentNode->next;
  return *currentNode;
}
