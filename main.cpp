

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>

#include "AvlTree.h"
#include "LazyAVLTree.h"
#include "BinarySearchTree.h"
#include "TreeParser.h"

using namespace std;

int main(int argc, const char * argv[]) {
    
    vector<int> myints = {1,9,10,3,5,4,6,8,7,2};
    
    LazyAvlTree<int> lazy;
    
    for (auto x: myints){
        lazy.insert(x);
    }
    
    AvlTree<int> avl;
    cout << "====" << endl;
    
    for (auto x: myints) {
        avl.insert(x);
    }
    
    vector<int> removeints = {3,4,3};
    
    for (auto x: removeints) {
        cout << "===" << endl;
        cout << "Lazy removing " << x << "..." << endl;
        lazy.remove(x);
        
    }
    
    for (auto x: removeints) {
        cout << "===" << endl;
        cout << "AVL Removing " << x << "..." << endl;
       avl.remove(x);
        
    }
   /* for (auto x : myints){
        cout << "Inserting " << x << "..." << endl;
        tree.insert(x);
    }
    
    cout << tree.contains(7) << endl;
    
    vector<int> removeints = {4,6,8};
    
    for (auto x: removeints) {
        cout << "Removing " << x << "..." << endl;
        tree.remove(x);
        
    }
    
    cout << tree.contains(7);*/
    
    /*
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
        
    }*/
    
    
    return 0;
}
