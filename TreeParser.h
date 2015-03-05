/*****************************************************************************
 Title:             TreeParser.h
 Author:            Anna Cristina Karingal
 Created on:        February 21, 2015
 Description:       
 
 Last Modified:     March 5, 2015
 
 *****************************************************************************/

#ifndef ____TreeParser__
#define ____TreeParser__

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "SequenceMap.h"
#include "BinarySearchTree.h"
#include "AvlTree.h"
#include "LazyAVLTree.h"

using namespace std;


template <typename TreeType>
class TreeParser {
    
public:
    
    TreeParser(ifstream &is);
    
    TreeParser(const TreeParser &copy);
    
    ~TreeParser();

    // Returns number of nodes in tree
    int get_num_nodes();
    
    void query (string query_sequence, ostream &os = cout );
    
    
private:
    
    /* MEMBER DATA VARIABLES */
    TreeType sequence_tree;
    int num_of_nodes;
    
    
    void PopulateTree(ifstream &is, int count = 0);

    
    
};

#endif
