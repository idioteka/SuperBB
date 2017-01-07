//
//  KeyHitsCollection.hpp
//  SuperBBmap
//
//  Created by Josip Maric on 05/03/16.
//  Copyright © 2016 Josip Maric. All rights reserved.
//

#ifndef KeyHitsCollection_hpp
#define KeyHitsCollection_hpp

#include "Utils.hpp"

class KeyHitsCollection {
public:
    int keyOrderNumber;
    long indexesStart;
    long numberOfKeyHits;
    long offset;
    KeyHitsCollection(int _keyOrderNumber, long _indexesStart, long _numberOfKeyHits, long _offset) {
        keyOrderNumber = _keyOrderNumber;
        indexesStart = _indexesStart;
        numberOfKeyHits = _numberOfKeyHits;
        offset = _offset;
    }
    ~KeyHitsCollection() {
    }
};

#endif /* KeyHitsCollection_hpp */

