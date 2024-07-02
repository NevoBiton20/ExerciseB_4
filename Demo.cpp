/**
 * Demo app for Ex4
 */
#include <iostream>
#include <string>
#include "node.hpp"
#include "Tree.hpp"

using namespace std;

int main()
{

    Node<double>* root_node = new Node<double>(1.1);

    tree<double> tree1; // Binary tree that contains doubles.

    tree1.add_root(root_node);

    Node<double>* n1 = new Node<double>(1.2);
    Node<double>* n2 = new Node<double>(1.3);
    Node<double>* n3 = new Node<double>(1.4);
    Node<double>* n4 = new Node<double>(1.5);
    Node<double>* n5 = new Node<double>(1.6);
    tree1.add_sub_node(root_node, n1);
    tree1.add_sub_node(root_node, n2);
    tree1.add_sub_node(n1, n3);
    tree1.add_sub_node(n1, n4);
    tree1.add_sub_node(n2, n5);
/*
    // The tree should look like:
     *       root = 1.1
     *     /       \
     *    1.2      1.3
     *   /  \      /
     *  1.4  1.5  1.6
     */
    cout<<"Pre Order:"<<endl;

    for (auto node = tree1.begin_pre_order(); node != tree1.end_pre_order(); ++node)
    {
        cout << node.get_value() << endl;
    } // prints: 1.1, 1.2, 1.4, 1.5, 1.3, 1.6
    cout << tree1.end_pre_order().get_value() << endl;

    cout<<"Post Order:"<<endl;
    for (auto node = tree1.begin_post_order(); node != tree1.end_post_order(); ++node)
    {
        cout << node.get_value() << endl;
    } // prints: 1.4, 1.5, 1.2, 1.6, 1.3, 1.1
    cout << tree1.end_post_order().get_value() << endl;


    cout<<"In Order:"<<endl;
    for (auto node = tree1.begin_in_order(); node != tree1.end_in_order(); ++node)
    {
        cout << node.get_value() << endl;
    }
    cout << tree1.end_in_order().get_value() << endl;
    // prints: 1.4, 1.2, 1.5, 1.1, 1.6, 1.3

    cout<<"BFS Order:"<<endl;
    for (auto node = tree1.begin_bfs_scan(); node != tree1.end_bfs_scan(); ++node)
    {
        cout << node.get_value() << endl;
    } // prints: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6
    cout << tree1.end_bfs_scan().get_value() << endl;

    tree<double,3> three_ary_tree;

    Node<double>* root_node2 = new Node<double>(1.1);
    Node<double>* n6 = new Node<double>(1.2);
    Node<double>* n7 = new Node<double>(1.3);
    Node<double>* n8 = new Node<double>(1.4);
    Node<double>* n9 = new Node<double>(1.5);
    Node<double>* n10 = new Node<double>(1.6);

    three_ary_tree.add_root(root_node2);
    three_ary_tree.add_sub_node(root_node2, n6);
    three_ary_tree.add_sub_node(root_node2, n7);
    three_ary_tree.add_sub_node(root_node2, n8);
    three_ary_tree.add_sub_node(n6, n9);
    three_ary_tree.add_sub_node(n7, n10);
    cout<<"Three-Ary_tree:"<<endl;
    cout<<three_ary_tree<<endl;
/*     // The tree should look like:
    **
     *       root = 1.1
     *     /      |     \
     *    1.2    1.3    1.4
     *   /        |
     *  1.5      1.6
     *
*/
    return 0;
}