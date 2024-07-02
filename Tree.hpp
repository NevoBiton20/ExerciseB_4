#ifndef TREE_HPP
#define TREE_HPP

#include <iostream>
#include "node.hpp"
#include <stack>
#include <queue>
#include <vector>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <type_traits>
#include "Complex.hpp"
#include <sstream>


// Tree template class , T is the type used in the tree
template <typename T,int n=2>
class tree{
    private:
        Node<T>* root; // pointer to root
    
    public:

        tree() : root(nullptr){} // constructor

        ~tree() //destructor
        {
            delete root;
        }

        void add_root(Node<T>* newRoot); //add root to tree
        void add_sub_node(Node<T>* node, Node<T>* newChild); // add new child to node

        template<typename U, int m>
        friend std::ostream& operator<<(std::ostream& os, const tree<U,m>& tr); // << operator (GUI representation)

        void draw(sf::RenderWindow& window, Node<T>* node, float x, float y, float xSpacing) const; // GUI tree drawing
        
        class IteratorInOrder {  // Iterator for tree<T,n=2> In-Order traversal
            private:
                Node<T>* begin;
                Node<T>* current;
                Node<T>* end;
                std::stack<Node<T>*> s;
                void pushLeft(Node<T>* node) {
                    while (node) {
                        s.push(node);
                        node = node->getChildren()[0];
                    }
                }

            public:
                IteratorInOrder(tree<T,n>& tree)
                {
                    if(n<=2 && n>0) // only if each tree node can hold more than 2 children
                    {
                        Node<T>* temp;
                        temp = tree.root;
                        while(temp->getChildren()[1])
                        {
                            temp = temp->getChildren()[1];
                        }
                        end = temp;
                        temp = tree.root;
                        while(temp->getChildren()[0])
                        {
                            s.push(temp);
                            temp = temp->getChildren()[0];
                        }
                        begin = temp;
                        current = begin;
                    }
                    else
                    {
                        s.push(tree.root);
                        current = tree.root;
                        for (int i=current->getCurrentChildren()-1; i>=0 ;i--) {
                            s.push(current->getChildren()[i]);
                        }
                        begin = current;
                        end = DFS(tree.root);
                    }
                }

                Node<T>* getCurrent() const
                {
                    return current;
                }

                IteratorInOrder& operator++()
                {
                    if(n<=2 && n>0)
                    {
                        Node<T>* node = s.top();
                        s.pop();
                        current = node;
                        if (node->getChildren()[1]) {
                            pushLeft(node->getChildren()[1]);
                        }
                    }
                    else
                    {
                        current = s.top();
                        s.pop();
                        for (int i=current->getCurrentChildren()-1; i>=0 ;i--) {
                            s.push(current->getChildren()[i]);
                        }
                    }
                    return *this;
                }

                Node<T>* DFS(Node<T>* root) { // DFS if tree is more then binary
                    std::stack<Node<T>*> nodeStack;
                    nodeStack.push(root);
                    Node<T>* cur;
                    while (!nodeStack.empty()) {
                        cur = nodeStack.top();
                        nodeStack.pop();
                        for (int i=cur->getCurrentChildren()-1; i>=0 ;i--) {
                            nodeStack.push(cur->getChildren()[i]);
                        }
                    }
                    return cur;
                }

                void set_to_end()
                {
                    current = end;
                }

                T get_value()
                {
                    return current->getKey();
                }

                bool operator==(const IteratorInOrder& other) const {
                    return current == other.getCurrent();
                }

                bool operator!=(const IteratorInOrder& other) const {
                    return !(current==other.getCurrent());
                }
        };

        class IteratorPostOrder {  // Iterator for tree<T,n=2> Post-Order traversal
            private:
                Node<T>* begin;
                Node<T>* current;
                Node<T>* end;
                std::stack<Node<T>*> nodeStack;
                std::stack<Node<T>*> visitStack;

            public:
                IteratorPostOrder(tree<T,n>& tree){
                    if(n<=2 && n>0)
                    {
                        end = tree.root;
                        Node<T>* temp = tree.root;
                        while(temp->getChildren()[0])
                        {
                            temp = temp->getChildren()[0];
                        }
                        begin = temp;
                        nodeStack.push(tree.root);
                        while(!nodeStack.empty())
                        {
                            Node<T>* node = nodeStack.top();
                            nodeStack.pop();
                            visitStack.push(node);
                            if(node->getChildren()[0]) nodeStack.push(node->getChildren()[0]);
                            if(node->getChildren()[1]) nodeStack.push(node->getChildren()[1]);
                        }
                        if(!visitStack.empty())
                        {
                            current = visitStack.top();
                            visitStack.pop();
                        }
                    }
                    else
                    {
                        nodeStack.push(tree.root);
                        current = tree.root;
                        for (int i=current->getCurrentChildren()-1; i>=0 ;i--) {
                            nodeStack.push(current->getChildren()[i]);
                        }
                        begin = current;
                        end = DFS(tree.root);
                    }
                }

                Node<T>* DFS(Node<T>* root) {
                    std::stack<Node<T>*> s;
                    s.push(root);
                    Node<T>* cur;
                    while (!s.empty()) {
                        cur = s.top();
                        s.pop();
                        for (int i=cur->getCurrentChildren()-1; i>=0 ;i--) {
                            s.push(cur->getChildren()[i]);
                        }
                    }
                    return cur;
                }

                IteratorPostOrder& operator++() {
                    if(n<=2 && n>0)
                    {
                        if(!visitStack.empty())
                        {
                            current = visitStack.top();
                            visitStack.pop();
                        }
                    }
                    else
                    {
                        current = nodeStack.top();
                        nodeStack.pop();
                        for (int i=current->getCurrentChildren()-1; i>=0 ;i--) {
                            nodeStack.push(current->getChildren()[i]);
                        }
                    }
                    return *this;
                }

                T get_value()
                {
                    return current->getKey();
                }

                void set_to_end()
                {
                    current = end;
                }

                bool operator!=(const IteratorPostOrder& other) const {
                    return current != other.current;
                }
        };

        class IteratorPreOrder {  // Iterator for tree<T,n=2> Pre-Order traversal
            private:
                Node<T>* begin;
                Node<T>* current;
                Node<T>* end;
                std::stack<Node<T>*> nodeStack;
                std::stack<Node<T>*> helper;
            public:
                IteratorPreOrder(tree<T,n>& tree) {
                    if(n<=2 && n>0)
                    {
                        preorderTraversal(tree.root);
                        begin = tree.root;
                        Node<T>* temp = tree.root;
                        current = begin;
                        if(current->getChildren()[1]) nodeStack.push(current->getChildren()[1]);
                        if(current->getChildren()[0]) nodeStack.push(current->getChildren()[0]); 
                        end = helper.top();
                    }
                    else
                    {
                        nodeStack.push(tree.root);
                        current = tree.root;
                        for (int i=current->getCurrentChildren()-1; i>=0 ;i--) {
                            nodeStack.push(current->getChildren()[i]);
                        }
                        begin = current;
                        end = DFS(tree.root);
                    }
                }

                void preorderTraversal(Node<T>* root) {
                    if (root == nullptr) return;
                    helper.push(root);
                    preorderTraversal(root->getChildren()[0]);

                    preorderTraversal(root->getChildren()[1]);

                }

                Node<T>* DFS(Node<T>* root) {
                    std::stack<Node<T>*> s;
                    s.push(root);
                    Node<T>* cur;
                    while (!s.empty()) {
                        cur = s.top();
                        s.pop();
                        for (int i=cur->getCurrentChildren()-1; i>=0 ;i--) {
                            s.push(cur->getChildren()[i]);
                        }
                    }
                    return cur;
                }

                IteratorPreOrder& operator++() {
                    if(n<=2 && n>0)
                    {
                        if(!nodeStack.empty())    
                        {
                            current = nodeStack.top();
                            nodeStack.pop();
                            if(current->getChildren()[1]) nodeStack.push(current->getChildren()[1]);
                            if(current->getChildren()[0]) nodeStack.push(current->getChildren()[0]);
                        }
                    }
                    else
                    {
                        current = nodeStack.top();
                        nodeStack.pop();
                        for (int i=current->getCurrentChildren()-1; i>=0 ;i--) {
                            nodeStack.push(current->getChildren()[i]);
                        }
                    }
                    return *this;
                }

                T get_value()
                {
                    return current->getKey();
                }

                void set_to_end()
                {
                    current = end;
                }

                bool operator!=(const IteratorPreOrder& other) const {
                    return current != other.current;
                }
        };

        class BFSIterator // Iterator for tree<T,n=2> BFS traversal
        {
            private:
                Node<T>* current;
                Node<T>* begin;
                Node<T>* end;
                std::queue<Node<T>*> nodeQueue;
            public:
                BFSIterator(tree<T,n>& tree) {
                    if (tree.root)
                    {
                        nodeQueue.push(tree.root);
                        current = tree.root;
                        for (int i=0;i<current->getCurrentChildren();i++) {
                            nodeQueue.push(current->getChildren()[i]);
                        }
                        begin = current;
                        nodeQueue.pop();
                        end = BFS(tree.root);
                    }
                }

                Node<T>* BFS(Node<T>* root) {
                    std::queue<Node<T>*> q;
                    q.push(root);
                    Node<T>* cur;
                    while (!q.empty()) {
                        cur = q.front();
                        q.pop();
                        for (int i=0;i<cur->getCurrentChildren();i++) {
                            q.push(cur->getChildren()[i]);
                        }
                    }
                    return cur;
                }
                BFSIterator& operator++() {
                    current = nodeQueue.front();
                    nodeQueue.pop();
                    for (int i=0;i<current->getCurrentChildren();i++) {
                        nodeQueue.push(current->getChildren()[i]);
                    }
                    return *this;
                }

                T operator*() const {
                    return current->getKey();
                }
                
                T get_value()
                {
                    return current->getKey();
                }

                void set_to_end()
                {
                    current = end;
                }

                bool operator!=(const BFSIterator& other) const {
                    return current != other.current;
                }
        };

        class DFSIterator {
            private:
                Node<T>* current;
                Node<T>* begin;
                Node<T>* end;
                std::stack<Node<T>*> nodeStack;
            public:
                DFSIterator(tree<T,n>& tree) {
                    if (tree.root)
                    {
                        nodeStack.push(tree.root);
                        current = tree.root;
                        for (int i=current->getCurrentChildren()-1; i>=0 ;i--) {
                            nodeStack.push(current->getChildren()[i]);
                        }
                        begin = current;
                        end = DFS(tree.root);
                    }
                }

                Node<T>* DFS(Node<T>* root) {
                    std::stack<Node<T>*> s;
                    s.push(root);
                    Node<T>* cur;
                    while (!s.empty()) {
                        cur = s.top();
                        s.pop();
                        for (int i=cur->getCurrentChildren()-1; i>=0 ;i--) {
                            s.push(cur->getChildren()[i]);
                        }
                    }
                    return cur;
                }
                DFSIterator& operator++() {
                    current = nodeStack.top();
                    nodeStack.pop();
                    for (int i=current->getCurrentChildren()-1; i>=0 ;i--) {
                        nodeStack.push(current->getChildren()[i]);
                    }
                    return *this;
                }

                T get_value()
                {
                    return current->getKey();
                }

                void set_to_end()
                {
                    current = end;
                }

                bool operator!=(const DFSIterator& other) const {
                    return current != other.current;
                }
        };

        class IteratorHeap  // Iterator for tree<T,n=2> MinHeap traversal
        {
            private:
                size_t current;
                size_t begin;
                size_t end;
                std::vector<T> heap;
                size_t size;
            public:
                IteratorHeap(tree<T,n>& tree)
                {
                    if(n<=2 && n>0)
                    {
                        size = count_elements(tree.root);

                        begin = 0;
                        current = 0;
                        end=size;
                        levelOrderToArray(tree.root);
                        buildMinHeap();
                    }
                    else
                    {
                        std::cout<<"The tree isn't binary!"<<std::endl;
                    }
                }

                // Function to convert binary tree to array
                void levelOrderToArray(Node<T>* root) {
                    if (root == nullptr) return;

                    std::queue<Node<T>*> q;
                    q.push(root);

                    while (!q.empty()) {
                        Node<T>* node = q.front();
                        q.pop();
                        heap.push_back(node->getKey());

                        if (node->getChildren()[0]) q.push(node->getChildren()[0]);
                        if (node->getChildren()[1]) q.push(node->getChildren()[1]);
                    }
                }

                // Function to build a min heap
                void buildMinHeap() {
                    std::make_heap(heap.begin(), heap.end(), std::greater<T>());
                }

                size_t count_elements(Node<T>* root)
                {
                    if(root)
                    {
                        return 1+count_elements(root->getChildren()[0]) + count_elements(root->getChildren()[1]);
                    }
                    return 0;
                }
                IteratorHeap& operator++() {
                    current++;
                    return *this;
                }

                T get_value()
                {
                    return heap[current];
                }

                void set_to_end()
                {
                    current = end;
                }

                bool operator!=(const IteratorHeap& other) const {
                    return current != other.current;
                }
        };

        IteratorPostOrder begin_post_order() {
            IteratorPostOrder it = IteratorPostOrder(*this);
            return it;      
        }

        IteratorPostOrder end_post_order() {
            IteratorPostOrder it = IteratorPostOrder(*this);
            it.set_to_end();
            return it;
        }

        BFSIterator begin_bfs_scan()
        {
            BFSIterator it = BFSIterator(*this);
            return it;
        }

        BFSIterator end_bfs_scan()
        {
            BFSIterator it = BFSIterator(*this);
            it.set_to_end();
            return it;
        }

        BFSIterator begin()
        {
            BFSIterator it = BFSIterator(*this);
            return it;
        }

        BFSIterator end()
        {
            BFSIterator it = BFSIterator(*this);
            it.set_to_end();
            return it;
        }

        DFSIterator begin_dfs_scan()
        {
            DFSIterator it = DFSIterator(*this);
            return it;
        }

        DFSIterator end_dfs_scan()
        {
            DFSIterator it = DFSIterator(*this);
            it.set_to_end();
            return it;
        }

        IteratorInOrder begin_in_order()
        {
            IteratorInOrder it = IteratorInOrder(*this);
            return it;
        }

        IteratorInOrder end_in_order()
        {
            IteratorInOrder it = IteratorInOrder(*this);
            it.set_to_end();
            return it;
        }

        IteratorPreOrder begin_pre_order()
        {
            IteratorPreOrder it = IteratorPreOrder(*this);
            return it;
        }

        IteratorPreOrder end_pre_order()
        {
            IteratorPreOrder it = IteratorPreOrder(*this);
            it.set_to_end();
            return it;
        }

        IteratorHeap begin_myHeap()
        {
            IteratorHeap it = IteratorHeap(*this);
            return it;
        }

        IteratorHeap end_myHeap()
        {
            IteratorHeap it = IteratorHeap(*this);
            it.set_to_end();
            return it;
        }
};

template<typename T, int n>
void tree<T,n>::add_root(Node<T>* newRoot)
{
    if(!root)
    {
        newRoot->setMaxChildren(n);
        root = newRoot;
    }
    else
    {
        throw std::runtime_error("This tree already has a root!");
    }
}

template<typename T, int n>
void tree<T,n>::add_sub_node(Node<T>* node, Node<T>* newChild)
{
    if(!node->addChild(newChild))
    {
        std::string error= "This tree is " + std::to_string(n) + "-ary, this node already has " + std::to_string(n) + " children";
        throw std::runtime_error(error);
    }
    else
    {
        newChild->setParent(node);
    }
}

template<typename T, int n>
std::ostream& operator<<(std::ostream& os, const tree<T,n>& tr)
{
    // Draw the node
    Node<T>* node = tr.root;
    float x = 100.f;
    float y = 50.f;
    float xSpacing = 150.f;
    sf::RenderWindow window(sf::VideoMode(800, 800), "Tree GUI!");
    window.clear(sf::Color::White);
    tr.draw(window,tr.root, x, y, xSpacing);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.display();
    }
    os<<"Tree representation display:"<<std::endl;
    return os;
}

template<typename T, int n>
void tree<T,n>::draw(sf::RenderWindow& window, Node<T>* node, float x, float y, float xSpacing) const {
    if (!node)
        return;

    // Draw the node
    sf::CircleShape shape(20.f); // Circle shape for nodes
    shape.setOutlineThickness(5.f);
    shape.setOutlineColor(sf::Color::Black);
    shape.setFillColor(sf::Color::White);
    shape.setPosition(x, y);
    window.draw(shape);

    // Draw the key (Uses ostringstream to hold key in string)
    sf::Font font;
    unsigned int size = 12;
    if (!font.loadFromFile("ARIAL.TTF")) {
        // Error loading font
        std::cout << "Error loading font!" << std::endl;
        return;
    }
    T data = node->getKey();
    std::string str;
    std::ostringstream oss;
    oss << data;
    str = oss.str();
    sf::Text text(str, font, size);
    text.setFillColor(sf::Color::Black);
    text.setPosition(x + 5.f, y + 10.f);
    window.draw(text);

    // Draw connections to children
    float startX = x + 20.f;
    float startY = y + 40.f;
    float offsetY = 80.f; // Vertical spacing between levels
    float offsetX = xSpacing; // Horizontal spacing between nodes

    for (int i = 0; i < n; ++i) {
        if (node->getChildren()[i]) {
            float childX = x + i * offsetX;
            float childY = y + offsetY;

            if(i==0) // Horizontal spacing between brother nodes
            {
                if(node->getParent() && node->getParent()->getChildren()[0] != node && node->getParent()->getChildren()[node->getParent()->getChildByNum(node)-1]->getCurrentChildren() >1)
                {
                    childX += offsetX*node->getParent()->getChildByNum(node);
                }
            }
            // Draw line between current node and child
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(startX, startY),sf::Color::Black),
                sf::Vertex(sf::Vector2f(childX + 20.f, childY),sf::Color::Black)
            };
            window.draw(line, 2, sf::Lines);

            // Recursive call to draw child
            draw(window, node->getChildren()[i], childX, childY, xSpacing);
        }
    }
}
#endif