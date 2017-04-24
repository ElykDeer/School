#include <iostream>
#include <vector>

class Polynomial
{
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& toPrint);

    friend bool operator==(const Polynomial& lhs, const Polynomial& rhs);
    friend Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs);

public:
    //Copy Control
    Polynomial();
    Polynomial(const std::vector<int>& coefficients);
    Polynomial(const Polynomial& toCopy);
    ~Polynomial();
    Polynomial& operator=(const Polynomial& toCopy);

    //Polynomial Builders
    void pushFront(const int newNodeData);
    void pushBack(const int newNodeData);

    //Polynomial Teardowners
    int popFront();
    int popBack();
    void clear();

    //Non-Destructive Accessors/Node Changer
    int operator[](const std::size_t index) const;
    int& operator[](const std::size_t index);
    std::size_t degree() const;
    int evaluate(int x) const;
    Polynomial& operator+=(const Polynomial& rhs);

private:
    struct Node {
    	Node(const int data, Node* link=nullptr);
    	int data;
    	Node* next;
    };

    //Recursive copy-helper function - WARNING, possibly dangerous (but pffft)
    Node* recvCopyHelper(const Node* node) const; //Doesn't mod any class vars
    void recvPrintHelper(const Node* node, std::ostream& os, size_t degree=0) const;
    Node& getNode(const std::size_t index) const;

    std::size_t degreeOfPoly;
    Node* head;
    Node* tail;
};

bool operator!=(const Polynomial& rhs, const Polynomial& lhs);
