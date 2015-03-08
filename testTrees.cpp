

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
                    BinarySearchTree<SequenceMap> bst_tree = parse_tree<BinarySearchTree<SequenceMap>>(parsef, insert_count);
                    cout << "\nBinary Search Tree Created..." << endl;
                    
                    cout << "===============================" << endl;
                    cout << "BINARY SEARCH TREE TEST RESULTS" << endl;
                    cout << "===============================" << endl;
                    
                    cout << "Total number of recursive calls to insert: " << insert_count << endl;
                    
                    run_test_routine(bst_tree, seq_query_file);
                    
                }
                else if (tree_type == "avl"){
                    AvlTree<SequenceMap> avl_tree = parse_tree<AvlTree<SequenceMap>>(parsef, insert_count);
                    cout << "\nAVL Tree Created..." << endl;
                    
                    cout << "===============================" << endl;
                    cout << "AVL TREE TEST RESULTS" << endl;
                    cout << "===============================" << endl;
                    
                    cout << "Total number of recursive calls to insert: " << insert_count << endl;

                    run_test_routine(avl_tree, seq_query_file);

                }
                else if (tree_type == "lazyavl") {
                    LazyAvlTree<SequenceMap> lazy_tree = parse_tree<LazyAvlTree<SequenceMap>>(parsef, insert_count);
                    cout << "\nAVL Tree with Lazy Deletion Created..." << endl;
                    
                    cout << "===============================" << endl;
                    cout << "LAZY AVL TREE TEST RESULTS" << endl;
                    cout << "===============================" << endl;
                    
                    cout << "Total number of recursive calls to insert: " << insert_count << endl;

                    run_test_routine(lazy_tree, seq_query_file);

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
        
        parsef.close();
        
    }
    
    return 0;
}