//
//  KeyHits.hpp
//  SuperBBmap
//
//  Created by Josip Maric on 05/03/16.
//  Copyright © 2016 Josip Maric. All rights reserved.
//

#ifndef KeyHits_hpp
#define KeyHits_hpp

#include "Utils.hpp"

class KeyHits {
public:
    long start;
    long number;
    KeyHits(long _start, long _number) {
        start = _start;
        number = _number;
    }
    ~KeyHits() {
    }
};

#endif /* KeyHits_hpp */
