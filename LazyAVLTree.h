#ifndef LAZYAVL_TREE_H
#define LAZYAVL_TREE_H

#include "dsexceptions.h"
#include <algorithm>
#include <iostream>
using namespace std;

/*****************************************************************************
 Title:             LazyAVLTree.h
 Author:            Anna Cristina Karingal
 Created on:        February 21, 2015
 Description:       Template class for an AVL Tree that supports lazy deletion
 
 Last Modified:     March 7, 2015
 
 *****************************************************************************/

//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x (unimplemented)
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class LazyAvlTree
{
public:
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
    
    ~LazyAvlTree( )
    {
        makeEmpty( );
    }
    
    /**
     * Deep copy.
     */
    LazyAvlTree & operator=( const LazyAvlTree & rhs )
    {
        LazyAvlTree copy = rhs;
        std::swap( *this, copy );
        return *this;
    }
    
    /**
     * Move.
     */
    LazyAvlTree & operator=( LazyAvlTree && rhs )
    {
        std::swap( root, rhs.root );
        
        return *this;
    }
    
    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMin( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMin( root )->element;
    }
    
    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMax( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMax( root )->element;
    }
    
    /**
     * Returns true if x is found in the tree.
     */
    bool contains( const Comparable & x ) const
    {
        int count = 0;
        bool c = contains( x, root, count );
        return c;
    }
    
    
    /**
     * Prints contents of the node containing element x
     */
    void print_node (const Comparable & x ) const{
        LazyAvlNode* found = find (x, root);
        if (found == nullptr) {
            cout << "Element not found in tree." << endl;
        }
        else {
            cout << found->element << endl;
        }
    }

    
    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty( ) const
    {
        return root == nullptr;
    }
    
    /**
     * Print the tree contents in sorted order.
     */
    void printTree( ) const
    {
        if( isEmpty( ) )
            cout << "Empty tree" << endl;
        else
            printTree( root );
    }
    
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
    void insert( const Comparable & x, int &count )
    {
        insert( x, root, count );
    }
    
    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( Comparable && x, int &count )
    {
        insert( std::move( x ), root, count );
        
    }
    
    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove( const Comparable & x )
    {
        int count = 0;
        remove( x, root, count );
        
    }
    
private:
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
    
    
    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( const Comparable & x, LazyAvlNode * & t, int &count )
    {
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
            t->element.merge(x);
        }
        
        balance( t );
    }
    
    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( Comparable && x, LazyAvlNode * & t, int &count)
    {
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
            t->element.merge(x);
        }
        
        balance( t );
    }
    
    /**
     * Internal method to remove find a node containing the Comparable element in the subtree
     * x is the item to find.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     * Returns a pointer to the node containing the element
     * If tree does not contain element or element is marked as deleted, returns nullptr
     */
    LazyAvlNode* find ( const Comparable & x, LazyAvlNode * t, int &count) const{
        
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

    
    LazyAvlNode* find ( const Comparable & x, LazyAvlNode * t ) const{
        
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
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void remove( const Comparable & x, LazyAvlNode * & t, int &count)
    {
        // Find element containing x
        LazyAvlNode* found = find(x, t, count);
        if (found == nullptr){
            cout << "Item not found. Nothing to delete." << endl;
            return;
            // Do nothing. No node to remove
        }
        else { // Mark node as deleted
            found->isDeleted = true;
        }
    }
    
    static const int ALLOWED_IMBALANCE = 1;
    
    // Assume t is balanced or within one of being balanced
    void balance( LazyAvlNode * & t )
    {
        if( t == nullptr )
            return;
        
        if( height( t->left ) - height( t->right ) > ALLOWED_IMBALANCE )
            if( height( t->left->left ) >= height( t->left->right ) )
                rotateWithLeftChild( t );
            else
                doubleWithLeftChild( t );
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
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    LazyAvlNode * findMin( LazyAvlNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        
        // Find min in left subtree while at node t
        LazyAvlNode * Lmin = findMin( t->left);
        
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
        return findMin( t->right );
    }
    
    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    LazyAvlNode * findMax( LazyAvlNode *t ) const
    {
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
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the tree.
     */
    bool contains( const Comparable & x, LazyAvlNode *t, int &count ) const
    {
        LazyAvlNode* found = find(x, t, count);
        if (found != nullptr){
            return true;
        }
        else { // Node not found or is marked as deleted
            return false;
        }
    }
    
    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty( LazyAvlNode * & t )
    {
        if( t != nullptr )
        {
            makeEmpty( t->left );
            makeEmpty( t->right );
            delete t;
        }
        t = nullptr;
    }
    
    /**
     * Internal method to print a subtree rooted at t in sorted order.
     */
    void printTree( LazyAvlNode *t ) const
    {
        // Print to console if tree node is not null and is not marked as deleted
        if( t != nullptr && !t->isDeleted)
        {
            printTree( t->left );
            cout << t->element << endl;
            printTree( t->right );
        }
    }
    
    /**
     * Internal method to clone subtree.
     */
    LazyAvlNode * clone( LazyAvlNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        else
            return new LazyAvlNode{ t->element, clone( t->left ), clone( t->right ), t->height };
    }
    // Avl manipulations
    /**
     * Return the height of node t or -1 if nullptr.
     */
    int height( LazyAvlNode *t ) const
    {
        return t == nullptr ? -1 : t->height;
    }
    
    int max( int lhs, int rhs ) const
    {
        return lhs > rhs ? lhs : rhs;
    }
    
    /**
     * Rotate binary tree node with left child.
     * For AVL trees, this is a single rotation for case 1.
     * Update heights, then set new root.
     */
    void rotateWithLeftChild( LazyAvlNode * & k2 )
    {
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
    void rotateWithRightChild( LazyAvlNode * & k1 )
    {
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
    void doubleWithLeftChild( LazyAvlNode * & k3 )
    {
        rotateWithRightChild( k3->left );
        rotateWithLeftChild( k3 );
    }
    
    /**
     * Double rotate binary tree node: first right child.
     * with its left child; then node k1 with new right child.
     * For AVL trees, this is a double rotation for case 3.
     * Update heights, then set new root.
     */
    void doubleWithRightChild( LazyAvlNode * & k1 )
    {
        rotateWithLeftChild( k1->right );
        rotateWithRightChild( k1 );
    }
};

#endif