
#include "SequenceMap.h"

SequenceMap::SequenceMap(string seq, string acronym):sequence(seq) {
    enzyme_acronyms.insert(acronym);
}

void SequenceMap::clearAcronyms(){
    enzyme_acronyms.clear();
}

void SequenceMap::merge(SequenceMap &other){
    
    // Check if sequences of both sequences are the same
    if (other.sequence != sequence) {
        throw logic_error(other.sequence);
    }
    
    // Merge: Add other's acronyms to sequence map
    for (auto s: other.enzyme_acronyms) {
        enzyme_acronyms.insert(s);
    }
    
}

void SequenceMap::merge(const SequenceMap &other){
    
    // Check if sequences of both sequences are the same
    if (other.sequence != sequence) {
        throw logic_error(other.sequence);
    }
    
    // Merge: Add other's acronyms to sequence map
    for (auto s: other.enzyme_acronyms) {
        enzyme_acronyms.insert(s);
    }
    
}

bool SequenceMap::operator< (const SequenceMap &right){
    
    if (this->sequence < right.sequence) {
        return true; 
    }
    return false;
}


bool SequenceMap::operator> (const SequenceMap &right){
    
    if (this->sequence > right.sequence) {
        return true;
    }
    return false;
}


ostream &operator << (ostream &os, const SequenceMap &sm){
    
    os << "ACRONYMS: " << endl;
    for (auto x: sm.enzyme_acronyms) {
        os << x << endl;
    }
    
    return os;
    
}