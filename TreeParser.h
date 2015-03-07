/*****************************************************************************
 Title:             TreeParser.h
 Author:            Anna Cristina Karingal
 Created on:        February 21, 2015
 Description:       
 
 Last Modified:     March 5, 2015
 
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
TreeType parse_tree(istream &readf) {
    
    TreeType tree;
    string line;

    // For each line in file
    while (getline(readf, line)) {
        
        istringstream seqmapss(line);
        size_t last_letter = line.length() - 1;
        
        if (line[last_letter] == '/' && line[last_letter-1] == '/') {
        
            // Split line into acronym and recognition sequences
            string enzyme_acronym;
            string all_seqs;
            getline(seqmapss, enzyme_acronym, '/');
            getline(seqmapss, all_seqs, '\n');
            
            // Get the next recognition sequence
            istringstream seqss(all_seqs);
            string s;
            while (getline(seqss, s, '/')){
                if (!s.empty()){
                    SequenceMap smap(s, enzyme_acronym);
                    tree.insert(smap);
                }
            }
        }
        else {
            //  Header: Line doesn't end in double slash. Do nothing.
        }
    }
    
    return tree;
}

template <typename TreeType>
void print_seqmap(TreeType &tree){
    
    string query;
    bool cont = true;
    
    while (cont){
        cout << "Recognition Sequence [or enter 'q' to quit]: " ;
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

#endif
