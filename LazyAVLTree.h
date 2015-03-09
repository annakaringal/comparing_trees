#ifndef LAZYAVL_TREE_H
#define LAZYAVL_TREE_H

/*****************************************************************************
 Title:             LazyAVLTree.h
 Author:            Anna Cristina Karingal
 Created on:        February 21, 2015
 Description:       Template class for an AVL Tree data structure that
                    supports lazy deletion
 
 Last Modified:     March 8, 2015
 
*****************************************************************************/


#include "dsexceptions.h"
#include <algorithm>
#include <iostream>
using namespace std;

// AVL Tree with Lazy Deletion class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x, count )     --> Insert x. Adds to count the number of
//                                 recursive calls made.
// void remove( x, count )     --> Removes x. Adds to count the number of
//                                 recursive calls made.
// bool contains( x, count )   --> Return true if x is present; else false.
//                                 Adds to count the number of recursive calls
//                                 made.
// Comparable findMin( )       --> Return smallest item
// Comparable findMax( )       --> Return largest item
// boolean isEmpty( )          --> Return true if empty; else false
// void makeEmpty( )           --> Remove all items
// void printTree( )           --> Print tree in sorted order
// void printNode(x)           --> Prints element in node containing x
// int nodes( )                --> Returns the number of nodes in the tree
// int internalPathLength( )   --> Returns the sum of the depth of all nodes
//                                 in the tree.
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class LazyAvlTree
{
public:
    
/******************************************************************************
     PUBLIC CONSTRUCTORS, DESTRUCTORS, MOVERS
******************************************************************************/
    LazyAvlTree( ) : root{ nullptr } { }
    
    LazyAvlTree( const LazyAvlTree & rhs ) : root{ nullptr } {
        root = clone( rhs.root );
    }
    
    LazyAvlTree( LazyAvlTree && rhs ) : root{ rhs.root } {
        rhs.root = nullptr;
    }
    
    ~LazyAvlTree( ) {
        makeEmpty( );
    }
    
    /**
     * Deep copy.
     */
    LazyAvlTree & operator=( const LazyAvlTree & rhs ) {
        LazyAvlTree copy = rhs;
        std::swap( *this, copy );
        return *this;
    }
    
    /**
     * Move.
     */
    LazyAvlTree & operator=( LazyAvlTree && rhs ) {
        std::swap( root, rhs.root );
        
        return *this;
    }
    
/******************************************************************************
     PUBLIC FIND FUNCTIONS
******************************************************************************/
    
    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMin( ) const {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMin( root )->element;
    }
    
    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMax( ) const {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMax( root )->element;
    }
    
    /**
     * Returns true if x is found in the tree.
     */
    bool contains( const Comparable & x, int& count) const {
        return contains( x, root, count );
    }
    

    
    
/******************************************************************************
     PUBLIC PRINT FUNCTIONS
******************************************************************************/
    /**
     * Prints contents of the node containing element x
     */
    void printNode (const Comparable & x ) const {
        LazyAvlNode* found = find (x, root);
        if (found == nullptr) {
            cout << "Element not found in tree." << endl;
        }
        else {
            cout << found->element << endl;
        }
    }
    
    /**
     * Print the tree contents in sorted order.
     */
    void printTree( ) const {
        if( isEmpty( ) )
            cout << "Empty tree" << endl;
        else
            printTree( root );
    }
    
/******************************************************************************
     PUBLIC INSERT/REMOVE FUNCTIONS
******************************************************************************/
    
    /**
     * Make the tree logically empty.
     */
    void makeEmpty( )
    {
        makeEmpty( root );
    }
    
    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( const Comparable & x, int &count ) {
        insert( x, root, count );
    }
    
    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( Comparable && x, int &count ) {
        insert( std::move( x ), root, count );
        
    }
    
    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    bool remove( const Comparable & x, int &count) {
        return remove( x, root, count );
        
    }
    
/******************************************************************************
     PUBLIC FUNCTIONS TO GET TREE CHARACTERISTICS
******************************************************************************/
    
    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty( ) const {
        return root == nullptr;
    }

    /**
     * Returns number of nodes in the tree
     */
    int nodes ( ) {
        return countNodes(root);
    }
    
    
    /**
     * Returns internal path length, i.e. sum of depth of all nodes in
     * tree
     */
    int internalPathLength() {
        int start = 0;
        return totalDepth(root, start);
    }

    
private:
    
/******************************************************************************
     Member Data
******************************************************************************/
    struct LazyAvlNode
    {
        Comparable element;
        LazyAvlNode *left;
        LazyAvlNode *right;
        int height;
        bool isDeleted;
        
        LazyAvlNode( const Comparable & ele, LazyAvlNode *lt, LazyAvlNode *rt, int h = 0, bool del = false)
        : element{ ele }, left{ lt }, right{ rt }, height{ h }, isDeleted{ del } { }
        
        LazyAvlNode( Comparable && ele, LazyAvlNode *lt, LazyAvlNode *rt, int h = 0, bool del = false )
        : element{ std::move( ele ) }, left{ lt }, right{ rt }, height{ h }, isDeleted{ del } { }
    };
    
    LazyAvlNode *root;

/******************************************************************************
     Insert Functions
******************************************************************************/

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( const Comparable & x, LazyAvlNode * & t, int &count ) {
        if( t == nullptr )
            t = new LazyAvlNode{ x, nullptr, nullptr };
        else if( t->element > x ){
            count ++;
            insert( x, t->left, count);
        }
        else if( t->element < x ){
            count ++;
            insert( x, t->right, count);
        }
        else {
            if (!t->isDeleted) {
                // Non deleted node exists, merge two nodes
                t->element.merge(x);
            }
            else {
                // Deleted node. Mark as not deleted
                // Clear acronyms and merge
                t->isDeleted = false;
                t->element.clearAcronyms();
                t->element.merge(x);
            }
        }
        
        balance( t );
    }
    
    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( Comparable && x, LazyAvlNode * & t, int &count) {
        if( t == nullptr )
            t = new LazyAvlNode{ std::move( x ), nullptr, nullptr };
        else if( t->element > x ){
            count ++;
            insert( std::move( x ), t->left, count );
        }
        else if( t->element < x ){
            count ++;
            insert( std::move( x ), t->right, count);
        }
        else {
            if (!t->isDeleted) {
                // Non deleted node exists, merge two nodes
                t->element.merge(x);
            }
            else {
                // Deleted node. Mark as not deleted
                // Clear acronyms and merge 
                t->isDeleted = false;
                t->element.clearAcronyms();
                t->element.merge(x);
            }
        }
        
        balance( t );
    }

    
/******************************************************************************
     Remove Functions
******************************************************************************/
    
    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    bool remove( const Comparable & x, LazyAvlNode * & t, int &count) {
        if( t == nullptr ){
            return false;   // Item not found; do nothing
        }
        if( t->element > x  ){
            count++;
            return remove( x, t->left, count );
        }
        else if( t->element < x ){
            count++;
            return remove( x, t->right, count );
        }
        else
        {
            if (!t->isDeleted) {
                t->isDeleted = true; // Mark as deleted
                return true;
            }
            else { // already marked as deleted
                return false;
            }
        }
        
    }

/******************************************************************************
     Find Functions
******************************************************************************/
    
    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    LazyAvlNode * findMin( LazyAvlNode *t, int &count ) const {
        if( t == nullptr )
            return nullptr;
        
        // Find min in left subtree while at node t
        count ++;
        LazyAvlNode * Lmin = findMin( t->left, count );
        
        // Min found in left subtree
        if (Lmin != nullptr) {
            return Lmin;
        }
        
        // Current node is the minimum and not marked as deleted
        if (!t->isDeleted) {
            return t;
        }
        
        // Current node is the minimum but is marked as deleted
        // Look in right subtree
        count ++;
        return findMin( t->right, count );
    }
    
    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    LazyAvlNode * findMax( LazyAvlNode *t ) const {
        if( t == nullptr )
            return nullptr;
        
        // Find min in  right subtree while at node t
        LazyAvlNode * Rmax = findMax( t->right);
        
        // Min found in left subtree
        if (Rmax != nullptr) {
            return Rmax;
        }
        
        // Current node is the max and not marked as deleted
        if (!t->isDeleted) {
            return t;
        }
        
        // Current node is the maximum but is marked as deleted
        // Look in left subtree
        return findMax( t->left );

    }
    
    
    /**
     * Internal method to remove find a node containing the Comparable element in the subtree
     * x is the item to find.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     * Returns a pointer to the node containing the element
     * If tree does not contain element or element is marked as deleted, returns nullptr
     */
    LazyAvlNode* find ( const Comparable & x, LazyAvlNode * t, int &count) const {
        
        if (t == nullptr){
            return nullptr;
        }
        else if( t->element > x ){
            count ++;
            return find( x, t->left, count );
        }
        else if( t->element < x ){
            count++;
            return find( x, t->right, count );
        }
        else{ // Found a match, return pointer to node
            if (!t->isDeleted) {
                return t;
            }
            else {
                return nullptr;
            }
        }
        
    }
    
    LazyAvlNode* find ( const Comparable & x, LazyAvlNode * t ) const {
        
        if (t == nullptr){
            return nullptr;
        }
        else if( t->element > x ){
            return find( x, t->left );
        }
        else if( t->element < x ){
            return find( x, t->right );
        }
        else{ // Found a match, return pointer to node
            if (!t->isDeleted) {
                return t;
            }
            else {
                return nullptr;
            }
        }
        
    }
    
    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the tree.
     */
    bool contains( const Comparable & x, LazyAvlNode *t, int &count ) const {
        if( t == nullptr )
            return false;
        else if( t->element > x ){
            count ++;
            return contains( x, t->left, count );
        }
        else if( t->element < x ){
            count++;
            return contains( x, t->right, count );
        }
        else{
            if (!t->isDeleted) { // Non-deleted Match
                return true;
            }
            else {
                return false;
            }
        }
    }
    
/******************************************************************************
     Functions to calculate characteristics of tree
******************************************************************************/
    
    /**
     * Return the height of node t or -1 if nullptr.
     */
    int height( LazyAvlNode *t ) const {
        return t == nullptr ? -1 : t->height;
    }
    
    /**
     * Recursively counts number of nodes in tree
     */
    int countNodes ( LazyAvlNode *t ) const {
        if (t == nullptr) {
            return 0;
        }
        if (t->left == nullptr && t->right == nullptr) {
            return 1;
        }
        else {
            return 1 + countNodes(t->left) + countNodes(t->right);
        }
    }

    /**
     * Returns sum of the depth of all nodes in tree rooted at t
     */
    int totalDepth( LazyAvlNode *t, int& totald) {
        
        if (t == nullptr) {
            return totald-1;
        }
        else {
            totald++;
            return totalDepth(t->left, totald) + totalDepth(t->right, totald);
        }
        
    }
    
    int max( int lhs, int rhs ) const {
        return lhs > rhs ? lhs : rhs;
    }
    
    
/******************************************************************************
     Print to console functions
******************************************************************************/
    
    /**
     * Internal method to print a subtree rooted at t in sorted order.
     */
    void printTree( LazyAvlNode *t ) const {
        // Print to console if tree node is not null and is not marked as deleted
        if( t != nullptr && !t->isDeleted)
        {
            printTree( t->left );
            cout << t->element << endl;
            printTree( t->right );
        }
    }

    
/******************************************************************************
     Internal Constructor/Destructor Helper Functions
******************************************************************************/
    
    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty( LazyAvlNode * & t ) {
        if( t != nullptr )
        {
            makeEmpty( t->left );
            makeEmpty( t->right );
            delete t;
        }
        t = nullptr;
    }
    
    /**
     * Internal method to clone subtree.
     */
    LazyAvlNode * clone( LazyAvlNode *t ) const {
        if( t == nullptr )
            return nullptr;
        else
            return new LazyAvlNode{ t->element, clone( t->left ), clone( t->right ), t->height };
    }
    // Avl manipulations

    
/******************************************************************************
     Balance Functions
******************************************************************************/
    
    
    static const int ALLOWED_IMBALANCE = 1;
    
    // Assume t is balanced or within one of being balanced
    void balance( LazyAvlNode * & t ) {
        if( t == nullptr )
            return;
        
        if( height( t->left ) - height( t->right ) > ALLOWED_IMBALANCE )
            if( height( t->left->left ) >= height( t->left->right ) ){
                rotateWithLeftChild( t );
            }
            else{
                doubleWithLeftChild( t );
            }
            else
                if( height( t->right ) - height( t->left ) > ALLOWED_IMBALANCE )
                    if ( height( t->right->right ) >= height( t->right->left ) ){
                        rotateWithRightChild( t );
                    }
                    else {
                        doubleWithRightChild( t );
                    }
        
        t->height = max( height( t->left ), height( t->right ) ) + 1;
    }
    
    /**
     * Rotate binary tree node with left child.
     * For AVL trees, this is a single rotation for case 1.
     * Update heights, then set new root.
     */
    void rotateWithLeftChild( LazyAvlNode * & k2 ) {
        LazyAvlNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
        k1->height = max( height( k1->left ), k2->height ) + 1;
        k2 = k1;
    }
    
    /**
     * Rotate binary tree node with right child.
     * For AVL trees, this is a single rotation for case 4.
     * Update heights, then set new root.
     */
    void rotateWithRightChild( LazyAvlNode * & k1 ) {
        LazyAvlNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
        k2->height = max( height( k2->right ), k1->height ) + 1;
        k1 = k2;
    }
    
    /**
     * Double rotate binary tree node: first left child.
     * with its right child; then node k3 with new left child.
     * For AVL trees, this is a double rotation for case 2.
     * Update heights, then set new root.
     */
    void doubleWithLeftChild( LazyAvlNode * & k3 ) {
        rotateWithRightChild( k3->left );
        rotateWithLeftChild( k3 );
    }
    
    /**
     * Double rotate binary tree node: first right child.
     * with its left child; then node k1 with new right child.
     * For AVL trees, this is a double rotation for case 3.
     * Update heights, then set new root.
     */
    void doubleWithRightChild( LazyAvlNode * & k1 ) {
        rotateWithLeftChild( k1->right );
        rotateWithRightChild( k1 );
    }
};

#endif