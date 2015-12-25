//
//  Alignment.hpp
//  SuperBBmap
//
//  Created by Josip Maric on 13/12/15.
//  Copyright © 2015 Josip Maric. All rights reserved.
//

#ifndef Alignment_hpp
#define Alignment_hpp

#include "Utils.hpp"
#include "Read.hpp"

// one possible alignment of one read
class Alignment {
public:
    Read* read;
    long start;
    long stop;
    bool strand;
    // score of possible alignment
    int score;
    // match string representation of possible alignment
    string matchString;
    vector<long> gapArray;
    Alignment(Read* _read, long _start, long _stop, bool _strand, int _score, string _matchString, vector<long> _gapArray) {
        read = _read;
        start = _start;
        stop = _stop;
        strand = _strand;
        score = _score;
        matchString = _matchString;
        gapArray = _gapArray;
    }
    ~Alignment() {
    }
};
#endif /* Alignment_hpp */
