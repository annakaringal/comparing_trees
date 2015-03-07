
#include "LazyAVLTree.h"

template <typename Comparable>
void LazyAvlTree<Comparable>::insert (const Comparable &x, LazyAvlNode *&t, int &count) {
    
    if( t == nullptr )
        t = new LazyAvlNode{ x, nullptr, nullptr };
    else if( x < t->element ){
        count ++;
        insert( x, t->left, count);
    }
    else if( t->element < x ){
        count ++;
        insert( x, t->right, count);
    }
    else {
        ; // Duplicate
    }
    
    balance( t );

}


template <typename Comparable>
void LazyAvlTree<Comparable>::insert (Comparable &&x, LazyAvlNode *&t, int &count) {
    if( t == nullptr )
        t = new LazyAvlNode{ std::move( x ), nullptr, nullptr };
    else if( x < t->element ){
        count ++;
        insert( std::move( x ), t->left, count );
    }
    else if( t->element < x ){
        count ++;
        insert( std::move( x ), t->right, count);
    }
    
    balance( t );
    
}

template <typename Comparable>
typename LazyAvlTree<Comparable>::LazyAvlNode* LazyAvlTree<Comparable>::find( const Comparable & x, LazyAvlNode *t, int &count ){
        if (t == nullptr){
            return nullptr;
        }
        else if( x < t->element ){
            count ++;
            return find( x, t->left, count );
        }
        else if( t->element < x ){
            count++;
            return find( x, t->right, count );
        }
        else{ // Found a match, return pointer to node
            if (!t->deleted) {
                return *t;
            }
            else {
                return nullptr;
            }
        }
}

template <typename Comparable>
bool LazyAvlTree<Comparable>::contains ( const Comparable & x, LazyAvlNode *t, int &count ) const{
    
    LazyAvlNode* found = find(x, t, count);
    if (found != nullptr){
        return true;
    }
    else { // Node not found or is marked as deleted
        return false;
    }
}

template <typename Comparable>
void LazyAvlTree<Comparable>::remove (const Comparable &x, LazyAvlNode *&t, int &count){
    
    LazyAvlNode* found = find(x, t, count);
    if (found == nullptr){
        // Do nothing. No node to remove
    }
    else { // Mark node as deleted
        found->deleted = true;
    }
}

template <typename Comparable>
void LazyAvlTree<Comparable>::balance( LazyAvlNode * & t )
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
                if( height( t->right->right ) >= height( t->right->left ) )
                    rotateWithRightChild( t );
                else
                    doubleWithRightChild( t );
    
    t->height = max( height( t->left ), height( t->right ) ) + 1;
}

/**
 * Rotate binary tree node with left child.
 * For AVL trees, this is a single rotation for case 1.
 * Update heights, then set new root.
 */
template <typename Comparable>
void LazyAvlTree<Comparable>::rotateWithLeftChild( LazyAvlNode * & k2 )
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
template <typename Comparable>
void LazyAvlTree<Comparable>::rotateWithRightChild( LazyAvlNode * & k1 )
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
template <typename Comparable>
void LazyAvlTree<Comparable>::doubleWithLeftChild( LazyAvlNode * & k3 )
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
template <typename Comparable>
void LazyAvlTree<Comparable>::doubleWithRightChild( LazyAvlNode * & k1 )
{
    rotateWithLeftChild( k1->right );
    rotateWithRightChild( k1 );
}


template <typename Comparable>
void LazyAvlTree<Comparable>::printTree (LazyAvlNode *t) const{
    if( t != nullptr && !t->deleted )
    {
        printTree( t->left );
        cout << t->element << endl;
        printTree( t->right );
    }
}
