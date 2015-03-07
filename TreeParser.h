/*****************************************************************************
 Title:             TreeParser.h
 Author:            Anna Cristina Karingal
 Created on:        February 21, 2015
 Description:       
 
 Last Modified:     March 7, 2015
 
 *****************************************************************************/

#ifndef ____TreeParser__
#define ____TreeParser__

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "SequenceMap.h"

using namespace std;

/* 
 Parses file and returns a tree of type TreeType containing data in file
    Pre-conditions: readf is an open, initialized file stream for a valid data 
                    file. 
 */
template <typename TreeType>
class TreeParser{
    
public:
    
    /**
     * Constructs a new tree parsed from file stream
     */
    TreeParser(ifstream &readfile){
        tree = parse_tree(readfile);
    }
    
    /**
     * Constructs a new tree parsed from file stream
     * Prints out number of
     */
    TreeParser(ifstream &readfile, int &count){
        tree = parse_tree(readfile, count);
    }
    
    /**
     * Copy constructor
     */
    TreeParser( const TreeParser &tp ){
        tree = tp.tree;
    }
    
    /**
     * Gets recognition sequence query from user
     * If query is a sequence in the tree, prints all enzyme acronyms for sequence
     */
    void print_seqmap(){
        
        string query;
        bool cont = true;
        
        while (cont){
            cout << "Enter Recognition Sequence [or enter 'q' to quit]: " ;
            cin >> query;
            
            if (query == "q") {
                cont = false;
            }
            else {
                SequenceMap seqmap_query(query, "");
                tree.print_node(seqmap_query);
            }
        }

    }
    
    void search_tree(istream &readf);
    
private:
    
    TreeType tree;
    
    int calls_to_insert;
    
    TreeType parse_tree(istream &readf, int count = 0);
    
};


#endif
