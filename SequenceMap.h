/*****************************************************************************
 Title:             SequenceMap.h
 Author:            Anna Cristina Karingal
 Created on:        February 21, 2015
 Description:       Class for containing a recognition sequence and the set of
                    enzymes that act on it.
                    Functions to: 
                        - compare two SequenceMaps by their sequence strings
                        - merge two SequenceMaps that possess identical
                          sequence strings
                        - print the list of enzyme acronyms for a sequence to
                          the console
 
 Last Modified:     March 8, 2015
 
 *****************************************************************************/

#ifndef SEQUENCEMAP_H
#define SEQUENCEMAP_H

#include <iostream>
#include <set>
#include <stdexcept>
using namespace std;

class SequenceMap {
private:
    
    string sequence;
    set <string> enzyme_acronyms;
    
public:
    
    // Constructor that initializes with an empty set of enzyme acronyms by default
    SequenceMap(string seq, string acronym="");
    
    // In case of duplicates: adds other SequenceMap's enzyme acronym to enzyme acronyms
    void merge(SequenceMap &other);
    void merge(const SequenceMap &other);
    
    // Removes all acronyms existing from enyme_acronyms and creates an empty set
    void clearAcronyms ();
    
    // Compares SequenceMaps using sequence string as a key
    bool operator< (const SequenceMap &right);
    bool operator> (const SequenceMap &right);
    
    // Overloaded << operator to print contents of sequence map to console.
    friend ostream &operator << (ostream &os, const SequenceMap &sm);
    
    
};

#endif