//
//  KeyHit.hpp
//  SuperBBmap
//
//  Created by Josip Maric on 07/01/2017.
//  Copyright © 2017 Josip Maric. All rights reserved.
//

#ifndef KeyHit_hpp
#define KeyHit_hpp

#include <stdio.h>

#endif /* KeyHit_hpp */

class KeyHit {
public:
    int keyOrderNumber;
    long locationIndex;
    long location;
    long offset;

    KeyHit() {
        keyOrderNumber = -1;
        locationIndex = -1;
        location = -1;
        offset = -1;
    }
    KeyHit(int _keyOrderNumber, long _locationIndex, long _location, long _offset) {
        keyOrderNumber = _keyOrderNumber;
        locationIndex = _locationIndex;
        location = _location;
        offset = _offset;
    }
    ~KeyHit() {
    }

    long keyHitSite();
};
