
#include "SequenceMap.h"

SequenceMap::SequenceMap(string seq, string acronym):sequence(seq) {
    enzyme_acronyms.insert(acronym);
}

string SequenceMap::get_sequence() const { return sequence; }

set<string> SequenceMap::get_acronyms() const { return enzyme_acronyms; }

void SequenceMap::merge(SequenceMap &other){
    
    // Check if sequences of both sequences are the same
    if (other.get_sequence() != sequence) {
        throw logic_error(other.get_sequence());
    }
    
    // Merge: Add other's acronyms to sequence map
    for (auto s: other.get_acronyms()){
        enzyme_acronyms.insert(s);
    }
    
}

bool SequenceMap::operator< (const SequenceMap &right){
    
    if (this->get_sequence() < right.get_sequence()) {
        return true; 
    }
    return false;
}


bool SequenceMap::operator== (string query){
    
    if (this->get_sequence() == query) {
        return true;
    }
    return false;
}


bool SequenceMap::operator== (const SequenceMap &right){
    
    if (this->get_sequence() == right.get_sequence()) {
        return true;
    }
    return false;
}



bool SequenceMap::operator> (const SequenceMap &right){
    
    if (this->get_sequence() > right.get_sequence()) {
        return true;
    }
    return false;
}


ostream &operator << (ostream &os, const SequenceMap &sm){
    
    os << "SEQUENCE: " << sm.get_sequence() << endl;
    os << "ACRONYMS: " << endl;
    for (auto x: sm.get_acronyms()) {
        os << x << endl;
    }
    
    return os;
    
}