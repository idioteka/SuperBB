//
//  CorrectAlignment.hpp
//  SuperBBmap
//
//  Created by Josip Maric on 13/12/15.
//  Copyright © 2015 Josip Maric. All rights reserved.
//

#ifndef CorrectAlignment_hpp
#define CorrectAlignment_hpp

#include "Utils.hpp"

// correct alignment for one read
class CorrectAlignment {
public:
    // start of correct alignment of read
    long start;
    // stop of correct alignment of read
    long stop;
    // cigar string representation of correct alignment
    string cigarString;
    // contains positions of introns
    vector<long> gapArray;
    CorrectAlignment(long _start, long _stop, string _cigarString, vector<long> _gapArray) {
        start = _start;
        stop = _stop;
        cigarString = _cigarString;
        gapArray = _gapArray;
    }
    ~CorrectAlignment() {
    }
};

#endif /* CorrectAlignment_hpp */
