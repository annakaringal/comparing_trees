#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "dsexceptions.h"
#include <algorithm>
using namespace std;

// BinarySearchTree class
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
class BinarySearchTree
{
public:
    
/******************************************************************************
     PUBLIC CONSTRUCTORS, DESTRUCTORS, MOVERS
******************************************************************************/
    BinarySearchTree( ) : root{ nullptr } { }
    
    /**
     * Copy constructor
     */
    BinarySearchTree( const BinarySearchTree & rhs ) : root{ nullptr } {
        root = clone( rhs.root );
    }
    
    /**
     * Move constructor
     */
    BinarySearchTree( BinarySearchTree && rhs ) : root{ rhs.root } {
        rhs.root = nullptr;
    }
    
    /**
     * Destructor for the tree
     */
    ~BinarySearchTree( ) {
        makeEmpty( );
    }
    
    /**
     * Copy assignment
     */
    BinarySearchTree & operator=( const BinarySearchTree & rhs ) {
        BinarySearchTree copy = rhs;
        std::swap( *this, copy );
        return *this;
    }
    
    /**
     * Move assignment
     */
    BinarySearchTree & operator=( BinarySearchTree && rhs ) {
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
        BinaryNode* found = find (x, root);
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
    void printTree( ostream & out = cout ) const {
        if( isEmpty( ) )
            out << "Empty tree" << endl;
        else
            printTree( root, out );
    }
    
/******************************************************************************
     PUBLIC INSERT/REMOVE FUNCTIONS
******************************************************************************/
   
    /**
     * Make the tree logically empty.
     */
    void makeEmpty( ) {
        makeEmpty( root );
    }
    
    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( const Comparable & x, int &count ) {
        insert(x, root, count);
    }
    
    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert ( Comparable &x, int &count ) {
        insert( std::move( x ), root, count);
    }
    
    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    bool remove( const Comparable & x, int& count ) {
        return remove( x, root, count );
    }

    
/******************************************************************************
     PUBLIC FUNCTIONS TO GET TREE CHARACTERISTICS
******************************************************************************/
    
    /**
     * Returns number of nodes in the tree
     */
    int nodes ( ) {
        return countNodes(root);
    }
    
    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty( ) const {
        return root == nullptr;
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
    struct BinaryNode
    {
        Comparable element;
        BinaryNode *left;
        BinaryNode *right;
        
        BinaryNode( const Comparable & theElement, BinaryNode *lt, BinaryNode *rt )
        : element{ theElement }, left{ lt }, right{ rt } { }
        
        BinaryNode( Comparable && theElement, BinaryNode *lt, BinaryNode *rt )
        : element{ std::move( theElement ) }, left{ lt }, right{ rt } { }
    };
    
    BinaryNode *root;
    
    
/******************************************************************************
     Insert Functions
******************************************************************************/
    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( const Comparable & x, BinaryNode * & t, int &count) {
        if( t == nullptr ){
            t = new BinaryNode{ x, nullptr, nullptr };
        }
        else if( t->element > x ){
            count ++;
            insert( x, t->left, count);
        }
        else if( t->element < x ){
            count ++;
            insert( x, t->right, count );
        }
        else {
            t->element.merge(x);
        }
    }
    
    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( Comparable && x, BinaryNode * & t, int &count) {
        if( t == nullptr ){
            t = new BinaryNode{ std::move( x ), nullptr, nullptr };
        }
        else if( t->element > x ){
            count ++;
            insert( std::move( x ), t->left, count);
        }
        else if( t->element < x ){
            count ++;
            insert( std::move( x ), t->right, count);
        }
        else{
            t->element.merge(x);
        }
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
     bool remove( const Comparable & x, BinaryNode * & t, int & count) {
        if( t == nullptr )
            return false; // Item not found; return false
        if( t->element > x ){
            count ++;
            return remove( x, t->left, count);
        }
        else if( t->element < x )
        {
            count ++;
            return remove( x, t->right, count);
        }
        else if( t->left != nullptr && t->right != nullptr ) // Two children
        {
            count ++;
            t->element = findMin( t->right, count )->element;
            count ++;
            return remove( t->element, t->right, count);
        }
        else
        {
            BinaryNode *oldNode = t;
            t = ( t->left != nullptr ) ? t->left : t->right;
            delete oldNode;
            return true;
        }
    }
    
/******************************************************************************
     Find Functions
******************************************************************************/
    
    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    BinaryNode * findMin( BinaryNode *t) const {
        if( t == nullptr )
            return nullptr;
        if( t->left == nullptr )
            return t;
        return findMin( t->left);
    }
    
    
    BinaryNode * findMin( BinaryNode *t, int &count ) const {
        if( t == nullptr )
            return nullptr;
        if( t->left == nullptr )
            return t;
        count ++;
        return findMin( t->left, count);
    }
    
    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    BinaryNode * findMax( BinaryNode *t ) const {
        if( t != nullptr )
            while( t->right != nullptr )
                t = t->right;
        return t;
    }
    
    BinaryNode* find( const Comparable & x, BinaryNode *t ) const {
        
        if( t == nullptr ) // Item not found
            return nullptr;
        else if( t->element > x ){
            return find( x, t->left );
        }
        else if( t->element < x ){
            return find( x, t->right );
        }
        else
            return t;    // Match
    }
    
    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the subtree.
     */
    bool contains( const Comparable & x, BinaryNode *t, int &count ) const {
        if( t == nullptr )
            return false;
        else if( t->element > x ){
            count++;
            return contains( x, t->left, count );
        }
        else if( t->element < x ){
            count ++;
            return contains( x, t->right, count );
        }
        else
            return true;    // Match
    }
    /****** NONRECURSIVE VERSION*************************
     bool contains( const Comparable & x, BinaryNode *t ) const
     {
     while( t != nullptr )
     if( x < t->element )
     t = t->left;
     else if( t->element < x )
     t = t->right;
     else
     return true;    // Match
     
     return false;   // No match
     }
     *****************************************************/

    
/******************************************************************************
     Functions to calculate characteristics of tree
******************************************************************************/
    
    
    /**
     * Recursively counts number of nodes in tree
     */
    int countNodes ( BinaryNode *t ) const {
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
    
    int totalDepth( BinaryNode *t, int& totald) {
        
        if (t == nullptr) {
            return totald-1;
        }
        else {
            totald++;
            return totalDepth(t->left, totald) + totalDepth(t->right, totald);
        }
        
    }
    

/******************************************************************************
     Print to console functions
******************************************************************************/
    
    /**
     * Internal method to print a subtree rooted at t in sorted order.
     */
    void printTree( BinaryNode *t, ostream & out ) const {
        if( t != nullptr )
        {
            printTree( t->left, out );
            out << t->element << endl;
            printTree( t->right, out );
        }
    }
    
    
/******************************************************************************
     Internal Constructor/Destructor Helper Functions
******************************************************************************/
    
    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty( BinaryNode * & t ) {
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
    BinaryNode * clone( BinaryNode *t ) const {
        if( t == nullptr )
            return nullptr;
        else
            return new BinaryNode{ t->element, clone( t->left ), clone( t->right ) };
    }
};

#endif