#ifndef ____TestRoutines__
#define ____TestRoutines__

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <cmath>

#include "SequenceMap.h"

using namespace std;

template <typename TreeType>
void run_test_routine(TreeType &tree, string filename){
    
    // Print number of nodes, avg depth & avg depth ratio
    get_tree_characteristics(tree);
    
    // Search tree for sequences in a given query file
    search_from_file(filename, tree);
    
    // Remove every other sequence in query file from tree
    remove_alternate_sequences(filename, tree);
    
    // Print number of nodes, avg depth & avg depth ratio for new tree
    get_tree_characteristics(tree);
    
    // Search new tree for sequences in file
    search_from_file(filename, tree);
    
}

template <typename TreeType>
void get_tree_characteristics(TreeType &tree) {
    
    if (!tree.isEmpty()) {
        
        // Calculate and print number of nodes in tree
        int n = tree.num_of_nodes();
        cout << "Number of Nodes: " << n << endl;
        
        // Compute and print average depth of tree
        float avg_depth = tree.internal_path_length() / n;
        cout << "Average Depth: " << setprecision(2) << avg_depth << endl;
        
        if (n > 1) {
            // Computes and prints ratio of avg depth to log n
            cout << "Ratio of Avg Depth: " << setprecision(3) << avg_depth/log2(n) << endl;
        }
        else {
            // Only 1 node
            cout << "Ratio of Avg Depth: 0" << endl;
        }

    }
    else {
        cout << "Empty tree. No information to calculate." << endl;
    }
    
}

template <typename TreeType>
void search_from_file (string filename, TreeType &tree) {
    
    ifstream readf;
    readf.open(filename.c_str());
    
    if (readf.fail()){
        cerr << "ERROR: Invalid file. Please check your file name and try again." << endl;
        exit(-1);
    }
    
    int success = 0;
    int recursive_calls = 0;
    string query;
    
    if (readf.is_open()) {
        while (getline(readf,query)){
            SequenceMap q(query);
            if (tree.contains(q, recursive_calls)){
                success ++;
            }
        }
    }
    
    cout << "Successful queries: " << success << endl;
    cout << "Recursive calls to contains():  << " << recursive_calls << endl;
    
}

template <typename TreeType>
void remove_alternate_sequences(string filename, TreeType &tree) {
    
    ifstream readf;
    readf.open(filename.c_str());
    
    if (readf.fail()){
        cerr << "ERROR: Invalid file. Please check your file name and try again." << endl;
        exit(-1);
    }
    
    int success = 0;
    int recursive_calls = 0;
    int query_count = 0;
    string query;
    
    if (readf.is_open()) {
        
        // Get each sequence in the file
        while (getline(readf,query)){
            query_count ++;
            
            // Only remove every other query sequence
            if (query_count % 2 == 0 ) {
                SequenceMap q(query);
                if (tree.remove(q,recursive_calls)){
                    success ++;
                }
            }
        }
    }
    
    cout << "Successful removes: " << success << endl;
    cout << "Recursive calls to remove():  << " << recursive_calls << endl;

}
#endif
