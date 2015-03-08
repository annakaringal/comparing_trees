

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
                
                if (tree_type == "bst") {
                    BinarySearchTree<SequenceMap> bst_tree = parse_tree<BinarySearchTree<SequenceMap>>(parsef, insert_count);
                    cout << "Binary Search Tree Created." << endl;
                    cout << "Total number of recursive calls to insert: " << insert_count << endl;
                    get_tree_characteristics(bst_tree);
                    search_from_file(seq_query_file, bst_tree);
                    string alt_query_file = get_alternate_sequences(seq_query_file );
                    remove_from_file(alt_query_file, bst_tree);
                    get_tree_characteristics(bst_tree);
                    
                    
                }
                else if (tree_type == "avl"){
                    AvlTree<SequenceMap> avl_tree = parse_tree<AvlTree<SequenceMap>>(parsef, insert_count);
                    cout << "AVL Tree Created." << endl;
                    cout << "Total number of recursive calls to insert: " << insert_count << endl;
                    get_tree_characteristics(avl_tree);
                    search_from_file(seq_query_file, avl_tree);

                }
                else if (tree_type == "lazyavl") {
                    LazyAvlTree<SequenceMap> lazy_tree = parse_tree<LazyAvlTree<SequenceMap>>(parsef, insert_count);
                    cout << "AVL Tree with Lazy Deletion Created." << endl;
                    cout << "Total number of recursive calls to insert: " << insert_count << endl;
                    get_tree_characteristics(lazy_tree);
                    search_from_file(seq_query_file, lazy_tree);

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
        
        parsef.close();
        
    }
    
    return 0;
}