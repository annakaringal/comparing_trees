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
     * Prints out number of recursive calls to insert after processing
     * entire database
     */
    TreeParser(ifstream &readfile, int &count){
        tree = parse_tree(readfile, count);
        cout << "Total recursive calls to insert: " << count << endl;
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
    
    int get_num_of_nodes(){
        return num_of_nodes;
    }
    
    int get_avg_depth(){
        return calculate_avg_depth();
    }
    
    float get_avg_depth_ratio(){
        return calculate_avg_depth_ratio();
    }
    
    void search(istream &readf);
    
    void remove(istream &readf);
    
private:
    
    TreeType tree;
    
    int num_of_nodes;
    
    TreeType parse_tree(istream &readf, int count = 0);
    
    int calculate_avg_depth();
    
    float calculate_avg_depth_ratio();
    
    void search_tree(istream &readf);
    
    void remove_from_tree(istream &readf);
    
};


#endif
