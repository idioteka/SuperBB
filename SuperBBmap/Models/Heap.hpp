//
//  Heap.hpp
//  SuperBBmap
//
//  Created by Josip Maric on 25/12/15.
//  Copyright © 2015 Josip Maric. All rights reserved.
//

#ifndef Heap_hpp
#define Heap_hpp

#include "Utils.hpp"
#include "KeyHit.hpp"

#endif /* Heap_hpp */

class Heap {
    int size_;
    int CAPACITY;
public:
    vector<KeyHit> array;
    Heap();
    bool isNull(KeyHit &t);
    void initHeap(int max_size);
    void add(KeyHit &t);
    KeyHit peek();
    KeyHit poll();
    bool isEmpty();
    void clear();
    int size();
private:
    int compare(KeyHit &t1, KeyHit &t2);
    void percDown(int loc);
    void percUp(int loc);
};
