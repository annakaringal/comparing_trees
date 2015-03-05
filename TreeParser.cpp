
#include "TreeParser.h"

template <typename TreeType>
TreeParser<TreeType>::TreeParser(ifstream &is){
    
    // Create new empty tree of type tree_type and insert values into tree
    sequence_tree = new TreeType;
    PopulateTree(is);
}

/* COPY CONSTRUCTOR */
template <typename TreeType>
TreeParser<TreeType>::TreeParser(const TreeParser &copy){
    sequence_tree = new TreeType (copy);
}

/* DESTRUCTOR */
template <typename TreeType>
TreeParser<TreeType>::~TreeParser(){
    delete sequence_tree;
}


// Returns number of nodes in tree
template <typename TreeType>
int TreeParser<TreeType>::get_num_nodes() { return num_of_nodes; }


/* PRIVATE METHODS */

template <typename TreeType>
void TreeParser<TreeType>::PopulateTree(ifstream &is, int count) {
    
    string enzyme;
    while (getline(is, enzyme)) {
        sequence_tree.insert();
    }
}

