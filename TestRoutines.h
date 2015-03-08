#ifndef ____TestRoutines__
#define ____TestRoutines__

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>

#include "SequenceMap.h"

using namespace std;

template <typename TreeType>
void get_tree_characteristics(TreeType &tree) {
    
    
    // Calculate and print number of nodes in tree
    int n = tree.num_of_nodes();
    cout << "Number of Nodes: " << n << endl;
    
    // Compute and print average depth of tree
    float avg_depth = tree.internal_path_length() / n;
    cout << "Average Depth: " << setprecision(2) << avg_depth << endl;
    
    // Computes and prints ratio of avg depth to log n
    float ratio;
    
    
    
}

template <typename TreeType>
void search_from_file (istream &readf, TreeType &tree) {
    
}

template <typename TreeType>
void remove_from_file(istream &readf, TreeType &tree) {
    
}


#endif
