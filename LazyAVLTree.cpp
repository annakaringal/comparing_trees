
#include "LazyAVLTree.h"

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
void LazyAvlTree<Comparable>::printTree (LazyAvlNode *t) const{
    if( t != nullptr && !t->deleted )
    {
        printTree( t->left );
        cout << t->element << endl;
        printTree( t->right );
    }
}
