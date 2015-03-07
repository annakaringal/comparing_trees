

#include "TreeParser.h"

template <typename TreeType>
TreeType TreeParser<TreeType>::parse_tree(istream &readf, int count){
    
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