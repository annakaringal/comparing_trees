/*****************************************************************************
 Title:             SequenceMap.h
 Author:            Anna Cristina Karingal
 Created on:        February 21, 2015
 Description:
 
 Last Modified:     February 21, 2015
 
 *****************************************************************************/

#ifndef ____SequenceMap__
#define ____SequenceMap__

#include <iostream>
#include <set>
using namespace std;

class SequenceMap {
private:
    
    string sequence;
    set <string> enzyme_acronyms;
    
public:
    
    SequenceMap(string seq, string acronym);
    
    string get_sequence() const;
    
    // In case of duplicates: adds other SequenceMap's enzyme acronym to enzyme acronyms
    void merge(SequenceMap other);
    
    bool operator< (const SequenceMap &right);
    
    
};

#endif