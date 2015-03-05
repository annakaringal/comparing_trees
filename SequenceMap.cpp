
#include "SequenceMap.h"

string SequenceMap::get_sequence() const { return sequence; }

void SequenceMap::merge(SequenceMap other){
    
}

bool SequenceMap::operator< (const SequenceMap &right){
    
    if (this->get_sequence() < right.get_sequence()) {
        return true; 
    }
    return false;
}