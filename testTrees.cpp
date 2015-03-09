/*****************************************************************************
 Title:             testTrees.cpp
 Author:            Anna Cristina Karingal
 Created on:        February 21, 2015
 Description:       1. Parses a given file of enzymes and the recognition
                    sequences they act on. Creates a tree of a given type
                    that contains the recognition sequences and the enzymes
                    that act on them.
                    2. Runs a series of tests on the tree: 
                        - Displays the number of calls to insert() made when
                            parsing the tree
                        - Displays the number of nodes (n) in the tree
                        - Displays the average depth of all nodes in the tree
                        - Displays ratio of average depth to log base 2 of n
                    3. Searches the tree for sequences listed in a given query
                    file and prints the number of sequences found and the 
                    number of recursive calls to contains() made by searching
                    the tree.
                    4. Removes every other sequence in in the query file from
                    the tree and prints the number of sequences removed and
                    the number of recursive calls made to remove.
                    5. Runs tests in 2. and 3. again on the diminished tree.
 
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
#include "TestRoutines.h"

using namespace std;
int main(int argc, const char * argv[]) {
    
    if (argc !=4){
        // Incorrect number of arguments given in command line
        cerr << "ERROR: Invalid number of arguments." << endl;
        exit(-1);
    }
    else {
        
        string file_to_parse = argv[1];
        string tree_type = argv[3];
        string seq_query_file = argv[2];
        
        // For case insensitive argument comparison
        transform(tree_type.begin(), tree_type.end(), tree_type.begin(), ::tolower);
        
        // Open file
        ifstream parsef;
        parsef.open(file_to_parse.c_str());
        
        if (parsef.fail()) {
            cerr << "ERROR: Invalid file. Please check your file name and try again." << endl;
            exit(-1);
        }
        
        if (parsef.is_open()) {
            
            try {
                
                int insert_count = 0;
                
                // Create tree from file and run test routine
                
                if (tree_type == "bst") {
                    BinarySearchTree<SequenceMap> bst_tree = parseTree<BinarySearchTree<SequenceMap>>(parsef, insert_count);
                    cout << "\nBinary Search Tree Created..." << endl;
                    
                    cout << "===============================" << endl;
                    cout << "BINARY SEARCH TREE TEST RESULTS" << endl;
                    cout << "===============================" << endl;
                    
                    cout << "Total number of recursive calls to insert: " << insert_count << endl;
                    
                    runTestRoutine(bst_tree, seq_query_file);
                    
                }
                else if (tree_type == "avl"){
                    AvlTree<SequenceMap> avl_tree = parseTree<AvlTree<SequenceMap>>(parsef, insert_count);
                    cout << "\nAVL Tree Created..." << endl;
                    
                    cout << "===============================" << endl;
                    cout << "AVL TREE TEST RESULTS" << endl;
                    cout << "===============================" << endl;
                    
                    cout << "Total number of recursive calls to insert: " << insert_count << endl;

                    runTestRoutine(avl_tree, seq_query_file);

                }
                else if (tree_type == "lazyavl") {
                    LazyAvlTree<SequenceMap> lazy_tree = parseTree<LazyAvlTree<SequenceMap>>(parsef, insert_count);
                    cout << "\nAVL Tree with Lazy Deletion Created..." << endl;
                    
                    cout << "===============================" << endl;
                    cout << "LAZY AVL TREE TEST RESULTS" << endl;
                    cout << "===============================" << endl;
                    
                    cout << "Total number of recursive calls to insert: " << insert_count << endl;

                    runTestRoutine(lazy_tree, seq_query_file);

                }

                else {
                    throw invalid_argument(tree_type);
                }
                
            }
            catch (invalid_argument invalid_tree_type) {
                cerr << "ERROR: Invalid tree type specified - " << invalid_tree_type.what() << endl;
                exit(-1);
            }
            catch (underflow_error) {
                cerr << "ERROR: Empty tree. Could not run test routines."<< endl;
                exit(-1);
            }
            catch (logic_error le) {
                cerr << "ERROR: Trying to merge SequenceMaps containing different sequences. (" << le.what() << ")" << endl;
                exit(-1);
            }
            catch (...) {
                cerr << "Unknown Error. Now exiting. Goodbye." << endl;
                exit(-1);
            }
        }
        
        // Close file
        parsef.close();
        
    }
    
    return 0;
}