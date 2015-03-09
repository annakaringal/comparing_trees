/*****************************************************************************
 Title:             TreeParser.h
 Author:            Anna Cristina Karingal
 Created on:        February 21, 2015
 Description:       Contains template functions to create a tree of type 
                    TreeType from file and query it.

                    parseTree(filename): 
                    Parses filename, a file containing a list of enzymes and
                    the recognition sequences they act on. Creates a tree of
                    type TreeType that contains the recognition sequences and
                    the enzymes that act on them.

                    printSequenceMap(tree):
                    Prompts the user for a recognition sequence and searches
                    the tree for that sequence. Prints enzymes that act on
                    the sequence to the console.
 
 Last Modified:     March 8, 2015
 
 *****************************************************************************/

#ifndef TREEPARSER_H
#define TREEPARSER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "SequenceMap.h"

using namespace std;

/**
 * Parses file and returns a tree of type TreeType containing data in file
 * Counts number of times insert() function is recursively called on the tree
 */
template <typename TreeType>
TreeType parseTree(istream &readf, int &count) {
    
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

                    // Insert into tree
                    tree.insert(smap, count);
                }
            }
        }
        else {
            //  Header: Line doesn't end in double slash. Do nothing.
        }
    }
    
    return tree;
}

/**
 * Parses file and returns a tree of type TreeType containing data in file
 */
template <typename TreeType>
TreeType parseTree(istream &readf) {
    
    TreeType tree;
    string line;
    
    int count = 0;
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
                    // Insert into tree
                    tree.insert(smap, count);
                }
            }
        }
        else {
            //  Header: Line doesn't end in double slash. Do nothing.
        }
    }
    
    return tree;
}

/**
 * Prompts user for recognition sequence, searches tree for given sequence
 * If sequence is found in tree, prints out a list of enzyme acronyms for that
 * sequence
 */
template <typename TreeType>
void printSequenceMap(TreeType &tree){
    
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
            tree.printNode(seqmap_query);
        }
    }
    
}
#endif
