#include "doctest.h"
#include "Tree.hpp"
#include "node.hpp"
#include "Complex.hpp"

using namespace std;
TEST_CASE("binary tree orders")
{
    tree<int> t;
    Node<int>* n1 = new Node<int>(1);
    Node<int>* n2 = new Node<int>(2);
    Node<int>* n3 = new Node<int>(3);
    Node<int>* n4 = new Node<int>(4);
    Node<int>* n5 = new Node<int>(5);
    Node<int>* n6 = new Node<int>(6);
    t.add_root(n1);
    t.add_sub_node(n1,n2);
    t.add_sub_node(n1,n3);
    t.add_sub_node(n2,n4);
    t.add_sub_node(n2,n5);
    t.add_sub_node(n3,n6);
    string output="";
    for (auto node = t.begin_pre_order(); node != t.end_pre_order(); ++node)
    {
        output += to_string(node.get_value()) + " ";
    } 
    output += to_string(t.end_pre_order().get_value());
    CHECK(output == "1 2 4 5 3 6"); // pre order

    output = "";
    for (auto node = t.begin_in_order(); node != t.end_in_order(); ++node)
    {
        output += to_string(node.get_value()) + " ";
    } 
    output += to_string(t.end_in_order().get_value());

    CHECK(output == "4 2 5 1 6 3"); // in order

    output = "";
    for (auto node = t.begin_post_order(); node != t.end_post_order(); ++node)
    {
        output += to_string(node.get_value()) + " ";
    } 
    output += to_string(t.end_post_order().get_value());

    CHECK(output == "4 5 2 6 3 1"); // post order

    output = "";
    for (auto node = t.begin_bfs_scan(); node != t.end_bfs_scan(); ++node)
    {
        output += to_string(node.get_value()) + " ";
    } 
    output += to_string(t.end_bfs_scan().get_value());
    CHECK(output == "1 2 3 4 5 6"); // bfs

    output = "";
    for (auto node = t.begin_dfs_scan(); node != t.end_dfs_scan(); ++node)
    {
        output += to_string(node.get_value()) + " ";
    } 
    output += to_string(t.end_dfs_scan().get_value());
    CHECK(output == "1 2 4 5 3 6"); //dfs

    tree<int> t2;
    Node<int>* n7 = new Node<int>(1);
    Node<int>* n8 = new Node<int>(2);
    Node<int>* n9 = new Node<int>(3);
    Node<int>* n11 = new Node<int>(4);
    Node<int>* n12 = new Node<int>(5);
    t2.add_root(n7);
    t2.add_sub_node(n7,n8);
    t2.add_sub_node(n7,n9);
    t2.add_sub_node(n8,n11);
    t2.add_sub_node(n11,n12);
    output="";
    for (auto node = t2.begin_pre_order(); node != t2.end_pre_order(); ++node)
    {
        output += to_string(node.get_value()) + " ";
    } 
    output += to_string(t2.end_pre_order().get_value());
    CHECK(output == "1 2 4 5 3"); // pre order

    output = "";
    for (auto node = t2.begin_in_order(); node != t2.end_in_order(); ++node)
    {
        output += to_string(node.get_value()) + " ";
    } 
    output += to_string(t2.end_in_order().get_value());

    CHECK(output == "5 4 2 1 3"); // in order

    output = "";
    for (auto node = t2.begin_post_order(); node != t2.end_post_order(); ++node)
    {
        output += to_string(node.get_value()) + " ";
    } 
    output += to_string(t2.end_post_order().get_value());

    CHECK(output == "5 4 2 3 1"); // post order

    output = "";
    for (auto node = t2.begin_bfs_scan(); node != t2.end_bfs_scan(); ++node)
    {
        output += to_string(node.get_value()) + " ";
    } 
    output += to_string(t2.end_bfs_scan().get_value());
    CHECK(output == "1 2 3 4 5"); // bfs

    output = "";
    for (auto node = t2.begin_dfs_scan(); node != t2.end_dfs_scan(); ++node)
    {
        output += to_string(node.get_value()) + " ";
    } 
    output += to_string(t2.end_dfs_scan().get_value());
    CHECK(output == "1 2 4 5 3"); //dsf

    output = "";
    for (auto node = t2.begin_myHeap(); node != t2.end_myHeap(); ++node)
    {
        output += to_string(node.get_value()) + " ";
    }
    CHECK(output == "1 2 3 4 5 "); // Min Heap
}


TEST_CASE("exception throwing and edge cases")
{
    tree<int,8> t;
    Node<int>* n1 = new Node<int>(1);
    Node<int>* n2 = new Node<int>(2);
    Node<int>* n3 = new Node<int>(3);
    Node<int>* n4 = new Node<int>(4);
    Node<int>* n5 = new Node<int>(5);
    Node<int>* n6 = new Node<int>(6);
    Node<int>* n7 = new Node<int>(7);
    Node<int>* n8 = new Node<int>(8);
    Node<int>* n9 = new Node<int>(9);
    Node<int>* n10 = new Node<int>(10);
    t.add_root(n1);
    t.add_sub_node(n1,n2);
    t.add_sub_node(n1,n3);
    t.add_sub_node(n1,n4);
    t.add_sub_node(n1,n5);
    t.add_sub_node(n1,n6);
    t.add_sub_node(n1,n7);
    t.add_sub_node(n1,n8);
    t.add_sub_node(n1,n9);
    CHECK_THROWS(t.add_sub_node(n1,n10));
    CHECK_THROWS(t.add_root(n2));

    std::string output="";
    for(auto node = t.begin_post_order(); node != t.end_post_order(); ++node)
    {
        output += to_string(node.get_value()) + " ";
    } 
    output += to_string(t.end_post_order().get_value());
    CHECK(output == "1 2 3 4 5 6 7 8 9"); // post order (dfs)

    output="";
    for(auto node = t.begin_in_order(); node != t.end_in_order(); ++node)
    {
        output += to_string(node.get_value()) + " ";
    } 
    output += to_string(t.end_in_order().get_value());
    CHECK(output == "1 2 3 4 5 6 7 8 9"); // in order (DFS)
    
    output="";
    for(auto node = t.begin_pre_order(); node != t.end_pre_order(); ++node)
    {
        output += to_string(node.get_value()) + " ";
    } 
    output += to_string(t.end_pre_order().get_value()); //pre order (DFS)
    CHECK(output == "1 2 3 4 5 6 7 8 9");
}
