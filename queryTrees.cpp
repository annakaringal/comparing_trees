
/*****************************************************************************
 Title:             queryTrees.cpp
 Author:            Anna Cristina Karingal
 Created on:        February 21, 2015
 Description:       Parses a given file of enzymes and the recognition
                    sequences they act on. Creates a tree of a given type
                    that contains the recognition sequences and the enzymes
                    that act on them.
                    Prompts the user for input. User inputs a recognition 
                    sequence and the program will output a list of the enzymes
                    that act on the query sequnce.
 
 Last Modified:     March 8, 2015
 
*****************************************************************************/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <ctype.h>

#include "AvlTree.h"
#include "LazyAVLTree.h"
#include "BinarySearchTree.h"
#include "TreeParser.h"

using namespace std;
int main(int argc, const char * argv[]) {
    
    if (argc !=3){
        // Incorrect number of arguments given in command line
        cerr << "ERROR: Invalid number of arguments." << endl;
        exit(-1);
    }
    else {
        
        string file_name = argv[1];
        string tree_type = argv[2];
       
        // For case insensitive argument comparison
        transform(tree_type.begin(), tree_type.end(), tree_type.begin(), ::tolower);
        
        // Open file
        ifstream readf;
        readf.open(file_name.c_str());
        
        if (readf.fail()) {
            cerr << "ERROR: Invalid file. Please check your file name and try again." << endl;
            exit(-1);
        }
        
        if (readf.is_open()) {
            
            try {
                
                // Generate trees based on command line argument
                // Prompts user for recognition sequence queries and prints
                // enzyme acronyms for valid sequences
                if (tree_type == "bst") {
                    BinarySearchTree<SequenceMap> bst_tree = parseTree<BinarySearchTree<SequenceMap>>(readf);
                    printSequenceMap(bst_tree);
                }
                else if (tree_type == "avl"){
                    AvlTree<SequenceMap> avl_tree = parseTree<AvlTree<SequenceMap>>(readf);
                    printSequenceMap(avl_tree);
                }
                else if (tree_type == "lazyavl") {
                    LazyAvlTree<SequenceMap> lazy_tree = parseTree<LazyAvlTree<SequenceMap>>(readf);
                    printSequenceMap(lazy_tree);
                }
                else {
                    throw invalid_argument(tree_type);
                }
                
            }
            catch (invalid_argument invalid_tree_type) {
                cerr << "ERROR: Invalid tree type specified - " << invalid_tree_type.what() << endl;
                exit(-1);
            }
        }
        
        readf.close();
        
    }
    
    return 0;
}