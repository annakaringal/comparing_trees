

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
        
        ifstream readf;
        readf.open(file_name.c_str());
        
        if (readf.fail()) {
            cerr << "ERROR: Invalid file. Please check your file name and try again." << endl;
            exit(-1);
        }
        
        if (readf.is_open()) {
            
            try {
                
                // Generate trees based on command line argument
                // Prompt user for recognition sequence queries and print
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
            catch (exception e) {
                cerr << "ERROR:" << e.what() << endl;
                exit(-1);
            }
        }
        
        readf.close();
        
    }
    
    return 0;
}