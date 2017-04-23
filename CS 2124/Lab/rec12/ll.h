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
class List
{
    friend std::ostream& operator<<(std::ostream& os, List& toPrint)
    {
        for(std::size_t i = 0; i < toPrint.sizeOfList; ++i)
            os << toPrint[i] << ' ';
        return os;
    }

public:
    //Copy Control
    List() : sizeOfList(0), head(nullptr), tail(nullptr) {}

    List(const List& toCopy)
    {
        //Set up my vars
        sizeOfList = toCopy.sizeOfList;
        head = recvCopyHelper(toCopy.head);  //Actually copy the List
        tail = &getNode(sizeOfList-1, true);  //Only time that we need to find the tail
    }

    ~List()
    {
        clear();
    }

    List& operator=(const List& toCopy)
    {
        if(this == &toCopy)
            return *this;

        clear();

        sizeOfList = toCopy.sizeOfList;
        head = recvCopyHelper(toCopy.head);  //Actually copy the List
        tail = &getNode(sizeOfList-1, true);

        return *this;
    }

    //List Builders
    void push_front(const type& newNodeData)
    {
        if(head)
            head = head->last = new Node(newNodeData, head, nullptr);
        else
            head = new Node(newNodeData, head, nullptr);
        if(!tail)
            tail = head;
        ++sizeOfList;
    }

    void push_back(const type& newNodeData)
    {
        if(tail)
            tail = tail->next = new Node(newNodeData, nullptr, tail);
        else
            head = tail = new Node(newNodeData);
        ++sizeOfList;
    }

    void push_before(const std::size_t index, const type& newNodeData)
    {
        push_after(index-1, newNodeData);
    }

    void push_before(const std::size_t index, const List& sliceIn)
    {
        push_after(index-1, sliceIn);
    }

    void push_after(const std::size_t index, const type& newNodeData)
    {
        if((index < sizeOfList) && (index > 0))
        {
            Node* node = &getNode(index);
            node->next = node->next->last = new Node(newNodeData, node->next, node);
            ++sizeOfList;
        }
        else
            std::cerr << "Bad index\n";
    }

    void push_after(const std::size_t index, const List& sliceIn)
    {
        if((index < sizeOfList) && (index > 0))
        {
            Node* node = &getNode(index);
            sliceIn.tail->next = node->next;
            node->next = sliceIn.head;
            sizeOfList += sliceIn.sizeOfList;
        }
        else
            std::cerr << "Bad index\n";
    }


    //List Teardowners
    type pop_front()
    {
        if(!head)
        {
            std::cerr << "No head\n";
            return type();
        }

        //Save some stuff
        type oldFrontData = head->data;
        Node* oldHead = head;

        //Set new head
        head = head->next;
        if(head) //If it's a no list.. Well, it's a no list
            head->last=nullptr;

        //Remove oldHead
        delete oldHead;
        --sizeOfList;

        return oldFrontData;
    }

    type pop_back()
    {
        if(!tail)
        {
            std::cerr << "No tail\n";
            return type();
        }

        //Save some stuff
        type oldTailData = tail->data;
        Node* oldTail = tail;

        //Set new tail
        tail = tail->last;

        //Remove oldHead
        delete oldTail;
        --sizeOfList;

        if(tail) //If it's a no list.. Well, it's a no list
            tail->next=nullptr; //No dangles!!

        return oldTailData;
    }

    type pop_after(const std::size_t index)
    {
        if((index < sizeOfList) && (index > 0))
        {
            Node* node = &getNode(index);

            //Save some stuff
            type nodeAfterData = node->next->data;
            Node* oldAfterNode = node->next;

            //Set new after node
            node->next = node->next->next;
            node->next->last = node;

            //Remove oldAfterNode
            delete oldAfterNode;
            --sizeOfList;
            return nodeAfterData;
        }
        std::cerr << "Bad index\n";
        return type();
    }

    type pop_before(const std::size_t index)
    {
        return pop_after(index-1);
    }

    void clear()
    {
        while(sizeOfList)
            pop_front();  //Just use a function we already have
        //Just double checking
        head = nullptr;
        tail = nullptr;
        sizeOfList = 0;
    }

    //Non-Destructive Accessors/Node Changer
    type operator[](const std::size_t index) const
    {
        return getNode(index).data;
    }

    type& operator[](const std::size_t index)
    {
        return getNode(index).data;
    }

    std::size_t size() const  //Simple Size getter
    {
        return sizeOfList;
    }

    //will return the index the marks the beginning of the match, Size on error
    std::size_t match(const List& subSet) const
    {
        for(std::size_t mainIndex = 0; mainIndex < sizeOfList; ++mainIndex) //Parse whole LL
            if(subSet[0] == operator[](mainIndex)) //Not efficient (first match?)
                for(std::size_t subIndex = 1; subIndex < subSet.sizeOfList; ++subIndex)
                {
                    if(subSet[subIndex] != operator[](mainIndex+subIndex)) //Still bad
                        break;
                    if(subIndex == subSet.sizeOfList-1) //If it got to the end
                        return mainIndex;
                }
        return sizeOfList; //Otherwise, return the index
    }

    type& front() //no promise the user won't edit
    {
        return head->data;
    }

    type& back() //no promise the user won't edit
    {
        return tail->data;
    }

private:
    struct Node { //From given code, only changed the type
    	Node(type data, Node* linkForward = nullptr, Node* linkBack = nullptr) : data(data), next(linkForward), last(linkBack) {}
    	type data;
    	Node* next;
    	Node* last;
    };

    //Recursive copy-helper function - WARNING, possibly dangerous (but pffft)
    Node* recvCopyHelper(const Node* node)
    {
        if(node) { return (new Node(node->data, recvCopyHelper(node->next), node->last)); }
        return nullptr;
    }

    Node& getNode(const std::size_t index, bool frontOnlyLoop = false) const
    {
        if(index <= sizeOfList/2 || frontOnlyLoop) //If it's in the first half of the list
        {
            Node* currentNode = head;
            for(std::size_t i = 0; i < index; ++i)
                currentNode = currentNode->next;
            return *currentNode;
        }
        else if(index > sizeOfList/2) //second half
        {
            Node* currentNode = tail;
            for(std::size_t i = sizeOfList-1; i > index; --i)
                currentNode = currentNode->last;
            return *currentNode;
        }
        else
        {
            std::cerr << "Bad index\n";
            return *head; //Return /something/
        }
    }

    std::size_t sizeOfList;
    Node* head;
    Node* tail;

public:
    //Ranged For support
    class iterator
    {
        friend class List<type>;
        friend bool operator==(const iterator& lhs, const iterator& rhs)
        {
            return(lhs.pointingAt == rhs.pointingAt);
        }

        friend bool operator!=(const iterator& lhs, const iterator& rhs)
        {
            return !(lhs == rhs);
        }
    public:
        iterator() : pointingAt(nullptr) {}
        iterator(Node* const node) : pointingAt(node) {}

        iterator& operator--()
        {
            pointingAt = pointingAt->last;
            return *this;
        }

        iterator& operator++()
        {
            pointingAt = pointingAt->next;
            return *this;
        }

        type& operator*()
        {
            return pointingAt->data;
        }
    private:
        Node* pointingAt;
    };

    iterator begin() const
    {
        return iterator(head);
    }

    iterator end() const
    {
        return iterator(nullptr);
    }

    //iterator can't be a reference?
    void insert(iterator insertBeforeMe, const type& newNodeData)
    {
        if(insertBeforeMe.pointingAt == head)
        {
            push_front(newNodeData);
        }
        else if(insertBeforeMe.pointingAt)
        {
            insertBeforeMe.pointingAt->last = new Node(newNodeData, insertBeforeMe.pointingAt, insertBeforeMe.pointingAt->last);
            if(insertBeforeMe.pointingAt->last->last)
                insertBeforeMe.pointingAt->last->last->next = insertBeforeMe.pointingAt->last;
            ++sizeOfList;
        }
        else
            push_back(newNodeData);
//        return --insertBeforeMe;
    }

    type erase(const iterator& eraseMe)
    {
        if(eraseMe==head)
            head=head->next;
        if(eraseMe==tail)
            tail=tail->last;

        //Set new after node
        if(eraseMe.pointingAt->last)
            eraseMe.pointingAt->last->next = eraseMe.pointingAt->next;
        if(eraseMe.pointingAt->next)
            eraseMe.pointingAt->next->last = eraseMe.pointingAt->last;

        //Remove oldAfterNode
        type oldData = eraseMe.pointingAt->data;
        delete eraseMe.pointingAt;
        --sizeOfList;
        return oldData;
    }
};
