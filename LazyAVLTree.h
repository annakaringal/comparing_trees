/*****************************************************************************
 Title:             LazyAVLTree.h
 Author:            Anna Cristina Karingal
 Created on:        February 21, 2015
 Description:       Template class for AVL Tree that supports lazy deletion
 
 Last Modified:     March 5, 2015
 
 *****************************************************************************/

#ifndef ____LazyAVLTree__
#define ____LazyAVLTree__

#include <iostream>
#include "AvlTree.h"
using namespace std;


template <typename Comparable>
class LazyAvlTree: public AvlTree<Comparable>{
    
public:
    
    // Constructor
    LazyAvlTree();
    
    // Copy Constructor
    LazyAvlTree(const LazyAvlTree &tree_to_copy);
    
    // Destructor
    ~LazyAvlTree();
    
private:
    
    
};

#endif