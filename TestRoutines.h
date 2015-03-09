/*****************************************************************************
 Title:             testTrees.cpp
 Author:            Anna Cristina Karingal
 Created on:        February 21, 2015
 Description:       A set of templated functions that run a series of tests on
                    a tree of a given type TreeType

                    getTreeCharacteristics(tree): 
                        - Displays the number of nodes (n) in tree
                        - Displays the average depth of all nodes in tree
                        - Displays ratio of average depth to log base 2 of n

                    searchFromFile (filename, tree) : 
                    Searches the tree for sequences listed in filename and
                    prints the number of sequences found and the number of
                    recursive calls made to contains().

                    removeAlternateSequences (filename, tree):
                    Removes every other sequence in in filename from tree and
                    prints the number of sequences removed and the number of
                    recursive calls made to remove().

                    runTestRoutines(tree, filename: 
                    Runs all the above tests.

 
 Last Modified:     March 8, 2015
 
*****************************************************************************/


#ifndef TESTROUTINES_H
#define TESTROUTINES_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <cmath>

#include "SequenceMap.h"

using namespace std;

/**
* Runs the series of tests on the tree in order. Shows tree
* characteristics before and after removing roughly half
* the sequences in the search file.
*/
template <typename TreeType>
void runTestRoutine(TreeType &tree, string filename){
    
    // Print number of nodes, avg depth & avg depth ratio
    getTreeCharacteristics(tree);
    
    cout << "--------------------" << endl;
    cout << "..Searching tree for sequences in file...\n" << endl;
    // Search tree for sequences in a given query file
    searchFromFile(filename, tree);
    
    cout << "--------------------" << endl;
    cout << "...Removing every other sequence from tree...\n" << endl;

    // Remove every other sequence in query file from tree
    removeAlternateSequences(filename, tree);
    
    
    cout << "--------------------" << endl;
    // Print number of nodes, avg depth & avg depth ratio for new tree
    getTreeCharacteristics(tree);
    
    cout << "--------------------" << endl;
    cout << "...Searching tree for sequences in file...\n" << endl;
    // Search new tree for sequences in file
    searchFromFile(filename, tree);
    
}

/**
* Calculates and prints: 
*     number of nodes in the tree, n
*     average depth of all nodes
*     ratio of average depth to log(base 2) of n
*/
template <typename TreeType>
void getTreeCharacteristics(TreeType &tree) {
    
    // Check if tree is empty to avoid divide by zero error
    if (!tree.isEmpty()) {
        
        // Calculate and print number of nodes in tree
        int n = tree.nodes();
        cout << "Number of Nodes: " << n << endl;
        
        // Compute and print average depth of tree
        float avg_depth = tree.internalPathLength() / n;
        cout << "Average Depth: " << avg_depth << endl;
        
        if (n > 1) {
            // Computes and prints ratio of avg depth to log n
            cout << "Ratio of Avg Depth: " << avg_depth/log2(n) << endl;
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

/**
* Searches tree for sequences in the given file. 
* Counts and prints the number of sequences found in the tree
* and the number of recursive calls made to contains()
*/
template <typename TreeType>
void searchFromFile (string filename, TreeType &tree) {
    
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
    cout << "Recursive calls to contains(): " << recursive_calls << endl;
    
}

/**
* Removes every other sequence in a given file from the tree
* Counts and prints the number of sequences removed
* and the number of recursive calls made to remove()
*/
template <typename TreeType>
void removeAlternateSequences(string filename, TreeType &tree) {
    
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
    cout << "Recursive calls to remove(): " << recursive_calls << endl;

}
#endif
