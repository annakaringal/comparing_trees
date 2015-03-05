

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

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
        
        ifstream readf;
        readf.open(file_name.c_str());
        
        if (readf.fail()) {
            cerr << "ERROR: Invalid file. Please check your file name and try again." << endl;
            exit(-1);
        }
        
        if (readf.is_open()) {
            
            try {
                // Parse tree
                BinarySearchTree<SequenceMap> bst = parse_tree<BinarySearchTree<SequenceMap>>(readf);
                
                // Get user query
                cout << "Recognition sequence: ";
                string query_seq;
                cin >> query_seq;
                
                
                // If sequence is in tree, print all corresponding enzymes
                
            }
            catch (...) {
                cerr << "UNKNOWN ERROR." << endl;
                exit(-1);
            }
        }
        
        readf.close();
        
    }
    
    
    return 0;
}
