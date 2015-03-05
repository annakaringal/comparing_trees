
#include "SequenceMap.h"

string SequenceMap::get_sequence() const { return sequence; }

void SequenceMap::merge(SequenceMap other){
    
    // If other's sequence is the same as the object's sequence
    if (other.sequence == sequence) {
        
        // Newly created other sequence map should only have 1 enzyme acronym
        // Add this acronym to the list of acronyms
        enzyme_acronyms.push_back(other.enzyme_acronyms[0]);
    }
    
}

bool SequenceMap::operator< (const SequenceMap &right){
    
    if (this->get_sequence() < right.get_sequence()) {
        return true; 
    }
    return false;
}