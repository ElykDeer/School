/* Author: Kyle Martin
 *
 * This code was written for the class 2134
 *
 * This code served as an exercise in linked lists.
 *   The assignment only required certian functional portions of a linked list,
 *   but to extend the exercise, I made a more functional class.
 *
 * Support for the user dealing with the nodes themselves may be added in the
 *   future to allow for significantly more efficient algorithms.  As is this
 *   serves mainly as a fair implementation for lists editable at either end
 *   (with middle support at a higher cost than neccissary for a linked list).
 *
 */

#include <iostream>
#include <vector>

template<typename type>
class LinkedList
{
    friend std::ostream& operator<<(std::ostream& os, LinkedList& toPrint)
    {
        for(std::size_t i = 0; i < toPrint.size; ++i)
            os << toPrint[i] << ' ';
        return os;
    }

public:
    //Copy Control
    LinkedList() : size(0), head(nullptr), tail(nullptr) {}

    LinkedList(const LinkedList& toCopy)
    {
        //Set up my vars
        size = toCopy.size;
        head = recvCopyHelper(toCopy.head);  //Actually copy the linkedList
        tail = &getNode(size-1);  //Only time that we need to find the tail
    }

    ~LinkedList()
    {
        clear();
    }

    LinkedList& operator=(const LinkedList& toCopy)
    {
        if(this == &toCopy)
            return *this;

        clear();

        size = toCopy.size;
        head = recvCopyHelper(toCopy.head);  //Actually copy the linkedList
        tail = &getNode(size-1);  //The only other time we need to find the tail

        return *this;
    }

    //LinkedList Builders
    void pushFront(const type& newNodeData)
    {
        head = new Node(newNodeData, head);
        if(!tail)
            tail = head;
        ++size;
    }

    void pushBack(const type& newNodeData)
    {
        if(tail)
            tail = tail->next = new Node(newNodeData);
        else
            head = tail = new Node(newNodeData);
        ++size;
    }

    void pushBefore(const std::size_t index, const type& newNodeData)
    {
        pushAfter(index-1, newNodeData);
    }

    void pushBefore(const std::size_t index, const LinkedList& sliceIn)
    {
        pushAfter(index-1, sliceIn);
    }

    void pushAfter(const std::size_t index, const type& newNodeData)
    {
        if((index < size) && (index > 0))
        {
            Node* node = &getNode(index);
            node->next = new Node(newNodeData, node->next);
            ++size;
        }
        else
            std::cerr << "Bad index\n";
    }

    void pushAfter(const std::size_t index, const LinkedList& sliceIn)
    {
        if((index < size) && (index > 0))
        {
            Node* node = &getNode(index);
            sliceIn.tail->next = node->next;
            node->next = sliceIn.head;
            size += sliceIn.size;
        }
        else
            std::cerr << "Bad index\n";
    }


    //LinkedList Teardowners
    type popFront()
    {
        if(!head)
            return type();

        //Save some stuff
        type oldFrontData = head->data;
        Node* oldHead = head;

        //Set new head
        head = head->next;

        //Remove oldHead
        delete oldHead;
        --size;

        return oldFrontData;
    }

    type popBack()
    {
        if(!tail)
            return type();

        //Save some stuff
        type oldTailData = tail->data;
        Node* oldTail = tail;

        //Set new tail
        tail = &getNode(size-2);

        //Remove oldHead
        delete oldTail;
        --size;

        tail->next=nullptr; //No dangles!!

        return oldTailData;
    }

    type popAfter(const std::size_t index)
    {
        if((index < size) && (index > 0))
        {
            Node* node = &getNode(index);

            //Save some stuff
            type nodeAfterData = node->next->data;
            Node* oldAfterNode = node->next;

            //Set new after node
            node->next = node->next->next;

            //Remove oldAfterNode
            delete oldAfterNode;
            --size;

            return nodeAfterData;
        }
        std::cerr << "Bad index\n";
        return type();
    }

    type popBefore(const std::size_t index)
    {
        return popAfter(index-1);
    }

    void clear()
    {
        std::size_t oldSize = size; //Other wise this just wouldn't work
        for(std::size_t i = 0; i < oldSize; ++i)
            popFront();  //Just use a function we already have
    }

    //Non-Destructive Accessors/Node Changer
    type operator[](const std::size_t index) const
    {
        Node* node = &getNode(index); //Reuse functions
        return node->data;
    }

    type& operator[](const std::size_t index)
    {
        Node* node = &getNode(index);
        return node->data;
    }

    std::size_t getSize() const  //Simple Size getter
    {
        return size;
    }

    //will return the index the marks the beginning of the match, Size on error
    std::size_t match(const LinkedList& subSet) const
    {
        for(std::size_t mainIndex = 0; mainIndex < size; ++mainIndex) //Parse whole LL
            if(subSet[0] == operator[](mainIndex)) //Not efficient (first match?)
                for(std::size_t subIndex = 1; subIndex < subSet.size; ++subIndex)
                {
                    if(subSet[subIndex] != operator[](mainIndex+subIndex)) //Still bad
                        break;
                    if(subIndex == subSet.size-1) //If it got to the end
                        return mainIndex;
                }
        return size; //Otherwise, return the index
    }


private:
    struct Node { //From given code, only changed the type
    	Node(type data, Node* link = NULL) : data(data), next(link) {}
    	type data;
    	Node* next;
    };

    //Recursive copy-helper function - WARNING, possibly dangerous (but pffft)
    Node* recvCopyHelper(const Node* node)
    {
        if(node) { return (new Node(node->data, recvCopyHelper(node->next))); }
        return nullptr;
    }

    Node& getNode(const std::size_t index) const
    {
        Node* currentNode = head;
        for(std::size_t i = 0; i < index; ++i)
            currentNode = currentNode->next;
        return *currentNode;
    }

    std::size_t size;
    Node* head;
    Node* tail;
};
