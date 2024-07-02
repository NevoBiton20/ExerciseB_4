#include <iostream>
#include <string>
#include "node.hpp"
#include "Tree.hpp"
#include "Complex.hpp"

using namespace std;
int main()
{
    Node<Complex>* root_node = new Node<Complex>(Complex(1,1));

    tree<Complex> tree1; // Binary tree that contains doubles.

    tree1.add_root(root_node);

    Node<Complex>* n1 = new Node<Complex>(Complex(2,2));
    Node<Complex>* n2 = new Node<Complex>(Complex(3,1));
    Node<Complex>* n3 = new Node<Complex>(Complex(4,1));
    Node<Complex>* n4 = new Node<Complex>(Complex(5,1));
    Node<Complex>* n5 = new Node<Complex>(Complex(6,1));
    tree1.add_sub_node(root_node, n1);
    tree1.add_sub_node(root_node, n2);
    tree1.add_sub_node(n1, n3);
    tree1.add_sub_node(n1, n4);
    tree1.add_sub_node(n2, n5);
/*
    // The tree should look like:
     *        root = 1 + i
     *        /            \
     *      2 + 2i         3 + i
     *     /      \         /
     *  4 + i    5 + i    6 + i
*/
    cout<<"Pre Order:"<<endl;

    for (auto node = tree1.begin_pre_order(); node != tree1.end_pre_order(); ++node)
    {
        cout << node.get_value() << endl;
    } // prints: 1. + i, 1 + 2i, 1 + 4i, 1 + 5i, 1 + 3i, 1 + 6i
    cout<<endl;

    cout<<"Post Order:"<<endl;
    for (auto node = tree1.begin_post_order(); node != tree1.end_post_order(); ++node)
    {
        cout << node.get_value() << endl;
    } 
    cout << tree1.end_post_order().get_value() << endl;

    cout<<endl;

    cout<<"In Order:"<<endl;
    for (auto node = tree1.begin_in_order(); node != tree1.end_in_order(); ++node)
    {
        cout << node.get_value() << endl;
    }
    cout << tree1.end_in_order().get_value() << endl;

    cout<<endl;

    cout<<"BFS Order:"<<endl;
    for (auto node = tree1.begin_bfs_scan(); node != tree1.end_bfs_scan(); ++node)
    {
        cout << node.get_value() << endl;
    } 
    cout << tree1.end_bfs_scan().get_value() << endl;
    cout<<endl;

    cout<<"DFS Order:"<<endl;
    for (auto node = tree1.begin_dfs_scan(); node != tree1.end_dfs_scan(); ++node)
    {
        cout << node.get_value() << endl;
    }
    cout << tree1.end_dfs_scan().get_value() << endl;
    cout<<endl;

    cout<<"Heap Order:"<<endl;
    for (auto node = tree1.begin_myHeap(); node != tree1.end_myHeap(); ++node)
    {
        cout << node.get_value() << endl;
    }
    cout<<endl;
    cout<<"Regular in range loop Order:"<<endl;

    for (auto node : tree1)
    {
        cout << node << endl;
    }
    cout << tree1.end_bfs_scan().get_value() << endl;

    cout << tree1; // Should print the graph using GUI.

    tree<Complex,3> three_ary_tree;

    Node<Complex>* root_node2 = new Node<Complex>(Complex(1,1));
    Node<Complex>* n6 = new Node<Complex>(Complex(3,1));
    Node<Complex>* n7 = new Node<Complex>(Complex(2,1));
    Node<Complex>* n8 = new Node<Complex>(Complex(7,1));
    Node<Complex>* n9 = new Node<Complex>(Complex(1,8));
    Node<Complex>* n10 = new Node<Complex>(Complex(12,1));

    three_ary_tree.add_root(root_node2);
    three_ary_tree.add_sub_node(root_node2, n6);
    three_ary_tree.add_sub_node(root_node2, n7);
    three_ary_tree.add_sub_node(root_node2, n8);
    three_ary_tree.add_sub_node(n6, n9);
    three_ary_tree.add_sub_node(n7, n10);

    cout<<"Three-Ary_tree:"<<endl;
    cout<<"Pre Order:"<<endl;

    for (auto node = three_ary_tree.begin_pre_order(); node != three_ary_tree.end_pre_order(); ++node)
    {
        cout << node.get_value() << endl;
    } // prints: 1 + i, 1+3i, 8+i, 1+2i, 1+12i, 1+7i
    cout << three_ary_tree.end_pre_order().get_value() << endl;


    cout<<"Post Order:"<<endl;
    for (auto node = three_ary_tree.begin_post_order(); node != three_ary_tree.end_post_order(); ++node)
    {
        cout << node.get_value() << endl;
    }  // prints: 1 + i, 1+3i, 8+i, 1+2i, 1+12i, 1+7i
    cout << three_ary_tree.end_post_order().get_value() << endl;


    cout<<"In Order:"<<endl;
    for (auto node = three_ary_tree.begin_in_order(); node != three_ary_tree.end_in_order(); ++node)
    {
        cout << node.get_value() << endl;
    }
    cout << three_ary_tree.end_in_order().get_value() << endl;
    // prints: 1 + i, 1+3i, 8+i, 1+2i, 1+12i, 1+7i
    cout<<endl;


    cout<<"BFS Order:"<<endl;
    for (auto node = three_ary_tree.begin_bfs_scan(); node != three_ary_tree.end_bfs_scan(); ++node)
    {
        cout << node.get_value() << endl;
    } // prints: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6
    cout << three_ary_tree.end_bfs_scan().get_value() << endl;
    cout<<endl;


    cout<<"DFS Order:"<<endl;
    for (auto node = three_ary_tree.begin_dfs_scan(); node != three_ary_tree.end_dfs_scan(); ++node)
    {
        cout << node.get_value() << endl;
    } // prints: 1 + i, 1+3i, 8+i, 1+2i, 1+12i, 1+7i
    cout << three_ary_tree.end_dfs_scan().get_value() << endl;



    cout<<"Regular in range loop Order:"<<endl;

    for (auto node : three_ary_tree)
    {
        cout << node << endl;
    } // same as BFS: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6
    cout << three_ary_tree.end_bfs_scan().get_value() << endl;
/*     // The tree should look like:
    **
     *       root = 1+i
     *     /      |     \
     *    3+i    2+i    7+i
     *   /        |
     *  1+8i      12+i
     *
*/
    return 0;
}