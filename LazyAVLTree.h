/*****************************************************************************
 Title:             LazyAVLTree.h
 Author:            Anna Cristina Karingal
 Created on:        February 21, 2015
 Description:       Template class for AVL Tree that supports lazy deletion
 
 Last Modified:     March 6, 2015
 
 *****************************************************************************/

#ifndef ____LazyAVLTree__
#define ____LazyAVLTree__

#include <iostream>
#include "AvlTree.h"
using namespace std;


template <typename Comparable>
class LazyAvlTree {
public:
    // Constructor & copy constructors
    LazyAvlTree( ) : root{ nullptr }
    { }
    
    LazyAvlTree( const LazyAvlTree & rhs ) : root{ nullptr }
    {
        root = clone( rhs.root );
    }
    
    LazyAvlTree( LazyAvlTree && rhs ) : root{ rhs.root }
    {
        rhs.root = nullptr;
    }
    
    // Destructor
    ~LazyAvlTree() {
        //AvlTree<Comparable>::makeEmpty(  );
    }
    
    void remove (const Comparable &x) {
        
        int count = 0;
        remove( x, root, count );
        cout << "Recursive calls to remove: " << count << endl;
    }

private:
    struct LazyAvlNode {
        
        Comparable element;
        LazyAvlNode *left;
        LazyAvlNode *right;
        int height;
        bool deleted;
        
        LazyAvlNode ( const Comparable &ele, LazyAvlNode *lt, LazyAvlNode *rt, int h = 0, bool del = false) : element { ele }, left{ lt }, right{ rt }, height{ h }, deleted { del } { }
        
        
        LazyAvlNode ( Comparable &ele, LazyAvlNode *lt, LazyAvlNode *rt, int h = 0, bool del = false) : element { std::move( ele ) }, left{ lt }, right{ rt }, height{ h }, deleted { del } { }
        
    };
    
    LazyAvlNode *root;
    
    static const int ALLOWED_IMBALANCE = 1;
    
    //void insert(const Comparable & x, AvlNode * & t, int &count);
    
    //void insert (Comparable && x, AvlNode * & t, int &count);
    
    LazyAvlNode * find ( const Comparable & x, LazyAvlNode *t, int &count );
    
    bool contains ( const Comparable & x, LazyAvlNode *t, int &count ) const;
    
    void remove (const Comparable &x, LazyAvlNode *&t, int &count);
    
    void balance (LazyAvlNode *&t);
    
    void printTree (LazyAvlNode *t) const;    
    
    
    

};

#endif