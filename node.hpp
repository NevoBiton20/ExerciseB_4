#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>
// Node class template <T> where T is the accepted value for key in the class
template <typename T>
class Node{
    private:
        T key; // Node's key
        Node<T>* parent; // Pointer to parent
        Node<T>** children; // Array of pointer to children
        size_t maxChildren; // Max children possible
        int currentChildren; // Current amount of children (For tracking limits)

    public:

        Node(T data) : key(data), parent(nullptr), currentChildren(0), maxChildren(0) {} // Constructor using initializer list

        ~Node() // Destructor
        {
            if(children)
            {
                for(size_t i=0; i<currentChildren;i++)
                {
                    delete children[i];
                }
                delete[] children;
            }
        }

        T getKey() const // Return key of type T
        {
            return key;
        }

        int getCurrentChildren() // Get current amount of children
        {
            return currentChildren;
        }

        void setMaxChildren(size_t n) // Set children limit
        {
            maxChildren=n;
            children = new Node<T>*[maxChildren];
        }

        Node<T>** getChildren() // Returns an array of pointers to this Node's children
        {
            return children;
        }

        void setParent(Node<T>* parentNode) // Sets a parent to the node
        {
            parent = parentNode;
        }

        Node<T>* getParent()
        {
            return parent;
        }

        bool addChild(Node<T>* child); // Adds a child to the node

        void printNode(); // Prints to std::cout this nodes data

        int getChildByNum(Node<T>* node); // Returns the index of nodes in this class' children pointers array

};

template<typename T>
bool Node<T>::addChild(Node<T>* child)
{
    if(currentChildren < maxChildren)
    {
        child->setMaxChildren(maxChildren);
        children[currentChildren] = child;
        currentChildren++;
        return true;
    }
    else
    {
        return false;
    }
}

template<typename T>
void Node<T>::printNode()
{
    std::cout<<key<<"\n";
    if(currentChildren>0)
    {
        for(size_t i=0;i<maxChildren;i++)
        {
            if(children[i])
            {
                children[i]->printNode();
            }
        }
    }
}

template<typename T>
int Node<T>::getChildByNum(Node<T>* node)
{
    for(int i=0;i<currentChildren;i++)
    {
        if(children[i]==node)
        {
            return i;
        }
    }
    return -1;
}
#endif