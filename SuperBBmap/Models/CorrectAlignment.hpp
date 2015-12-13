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

class CorrectAlignment {
public:
    long start;
    long stop;
    string cigarString;
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
