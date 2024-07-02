### Exercise 4 - STL

## **Introduction**
This project is made in order to create an easy way to make use of trees in c++.
In this guide I will explain all the components in this project, how they work,
and why they are built like that.
_________________________________________________________________________________
## **Main Components**

### Node Class
This is the Node class used to represent a simple generic Node in a tree.
This class is a template class in c++ and looks like this:

**Class:**
```
template<typename T>
class Node<T>
```

**Main fields:**
```
T key
Node<T>** children
Node<T>* parent
int current_children
int MaxChildren
```
key holds the actual value of the node,
children is an array of pointers to other nodes who are it's children
parent is the father of this node, for root this field will hold nullptr
current_children is a variable that holds how many children this node currently, basically 
the amount of non null pointers in this array
maxChildren is the max amount of children this node can hold in children

Node class has several class methids he uses:
This class owns a constructor that receives a T data and initializes a node with that data, the rest of the fields are set using initializer list.
This class owns a destructor which iterates through the children array using key word ```delete``` to free the memory of each children and at the end frees the array itself.

**Main functions:**
```
Node<T>** getChildren() // Returns the children pointers array
T getKey() // Returns the value this node holds
bool addChild(Node<T>* newChild) // Receives a child and adds it (adds only if there is available place for it, if the child adding succeed, returns true
```

### Tree Class
This it the tree used to represent a generic tree.
This class is a template class in c++ that looks like this:
This class owns a default constructor that initializes the basic fields for itself.
This class owns a destructor which uses the key word ```delete``` on the root, the rest of tree is being deleted recursively by Node's destructor definition.

**Class:**
```
template<typename T, int n=2>
class tree<T,n>
```

As you can see, this class is built by a type that represents it and its contains, and an integer number that represents how many children each node in the tree holds at max. (The default of this class is binary tree)
The tree class holds a single field in order to represent its structure:

**Main fields:**
```
Node<T>* root
```
the tree holds a pointer to its root node, as shown earlier, each node holds its children so the whole tree is represented recursively only from single node - root.

**Main Functions:**
```
void add_root(Node<T>* newRoot); // Adds root to tree ( Prints error if another root is tried to be added )
void add_sub_node(Node<T>* node, Node<T>* newChild); // Adds new child to node ( Prints error if max children limit been surpassed )
```

### Complex class:
A simple complex class representaion created due to exercise requirements:

**Fields**
```
double im
double re
```
Every complex number is defined as structure of *a + bi* where *a* and *b* are real numbers.

This class contains getters for both fields, and is initiallized by a simple constructor receives two real numbers
This class owns a copy constructor used for algorithms needs.

In addition, this class overloads several comparison operators used for algorithms' needs and maybe a future usage:
The ```<<``` operator is overloaded for couting a coomplex number if used as data. 
```
friend bool operator==(const Complex &first,const Complex &second); 
friend bool operator!=(const Complex &first,const Complex &second);
friend bool operator<(const Complex &first,const Complex &second);
friend bool operator>(const Complex &first,const Complex &second);
friend bool operator<=(const Complex &first,const Complex &second);
friend bool operator>=(const Complex &first,const Complex &second);
friend ostream& operator<<(ostream& os, const Complex& cmp);
```
_________________________________________________________________________________________________________________________

## **Iterators**

One of the main instructions in this exercise was creating iterators of several kinds to the tree class.
Every Iterator implemented in this project is an inner class of tree<T,n> class, the reason for that is so
every iterator could access to the tree's data structure.

### Basic Iterator structure
Every iterator implemented in this project is of the following structure (every iterator adds things by his needs):

```
Node<T>* begin;
Node<T>* current;
Node<T>* end;
```
The tree class has, for every iterator, a begin() and end() function which returns iterators standing on the begin and the end of the traversal.
In addition, every iterator overloads an operator++ which increase the current value index by one so the next element in the traversal will be holded by current.
In start current always equals to begin, and when ++ is used current is moves on, until it reaches to end in the for each loop.

### The tree iterators kinds in this project
```
class IteratorInOrder
class IteratorPostOrder
class IteratorPreOrder
class BFSIterator
class DFSIterator
class IteratorHeap
```

## **GUI implementation**

This project has a feature of representing a tree<T,n> in a graphical interface.
For GUI purposes, this project uses SFML library to create graphical design representations.
tree<T,n> class holds a function called ```draw```, this function receives a ```Node<T>* root``` and creates a new graphical window, iterates recursively through the root, and draws every node.

## **Testing and Edge cases**

This projects holds a doctest tests, these tests runs check on the following cases:

*Binary tree Iterators correctness*
*General tree Iterators correctness*
*Limits surpassing*
*Wrong usage*
The tests check correct outputs, errors throws and correct edge cases respons.

## ** Main and Demo**

This project contains Main program and demo program, Main program creates trees containing complex numbers, make iterators prints and GUI tree representation,
Demo program creates binary and trinary trees, output several iterators and makes GUI tree representation.
