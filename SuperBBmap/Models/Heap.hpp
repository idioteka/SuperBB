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

#endif /* Heap_hpp */


struct Triplet {
    int column;
    int row;
    int site;
    Triplet() {
        column = -1;
        row = -1;
        site = -1;
    }
    Triplet(int column_, int row_, int site_) {
        column = column_;
        row = row_;
        site = site_;
    }
};

class Heap {
    int size_;
    int CAPACITY;
public:
    vector<Triplet> array;
    Heap();
    bool isNull(Triplet &t);
    void initHeap(int max_size);
    void add(Triplet &t);
    Triplet peek();
    Triplet poll();
    bool isEmpty();
    void clear();
    int size();
private:
    int compare(Triplet &t1, Triplet &t2);
    void percDown(int loc);
    void percUp(int loc);
};
