/*****************************************************************************
 Title:             SequenceMap.h
 Author:            Anna Cristina Karingal
 Created on:        February 21, 2015
 Description:
 
 Last Modified:     March 5, 2015
 
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
    
    SequenceMap(string seq, string acronym="");
    
    string get_sequence() const;
    set<string> get_acronyms() const;
    
    // In case of duplicates: adds other SequenceMap's enzyme acronym to enzyme acronyms
    void merge(SequenceMap &other);
    void merge(const SequenceMap &other);
    
    // Removes all acronyms existing from enyme_acronyms and creates an empty set
    void clear_acronyms ();
    
    // Comparison operators
    bool operator< (const SequenceMap &right);
    
    bool operator> (const SequenceMap &right);
    
    // Overloaded << operator to print contents of sequence map to console.
    friend ostream &operator << (ostream &os, const SequenceMap &sm);
    
    
};

#endif