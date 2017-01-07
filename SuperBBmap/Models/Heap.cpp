//
//  Heap.cpp
//  SuperBBmap
//
//  Created by Josip Maric on 25/12/15.
//  Copyright © 2015 Josip Maric. All rights reserved.
//

#include "Heap.hpp"

Heap::Heap() {
    size_ = 0;
}

int Heap::compare(KeyHit &t1, KeyHit &t2) {
    long siteDifference = t1.keyHitSite() - t2.keyHitSite();
    if(siteDifference != 0) return (int) siteDifference;
    return t1.keyOrderNumber - t2.keyOrderNumber;
}

void Heap::percDown(int loc){
    
    if(loc == 1) {
        return;
    }
    
    int next = loc/2;
    KeyHit a = array[loc];
    KeyHit b = array[next];
    
    while(loc > 1 && compare(a, b) < 0){
        array[loc] = b;
        loc = next;
        next = next/2;
        b = array[next];
    }
    
    array[loc]=a;
}

void Heap::percUp(int loc){
    int next1 = loc * 2;
    int next2 = next1 + 1;
    if(next1 > size_) {
        return;
    }
    KeyHit a = array[loc];
    KeyHit b = array[next1];
    if(next2 > size_) {
        if(compare(a, b) > 0){
            array[next1] = a;
            array[loc] = b;
            percUp(next1);
        }
    }
    else {
        KeyHit c = array[next2];
        if(compare(b, c) < 1) {
            if(compare(a, b) > 0){
                array[next1] = a;
                array[loc] = b;
                percUp(next1);
            }
        }
        else{
            if(compare(a, c)>0){
                array[next2] = a;
                array[loc] = c;
                percUp(next2);
            }
        }
    }
}

void Heap::initHeap(int max_size) {
    CAPACITY = max_size;
    KeyHit t;
    array.clear();
    array.push_back(t);
}

void Heap::add(KeyHit &t) {
    size_++;
    array.push_back(t);
    percDown(size_);
}

KeyHit Heap::peek() {
    if(size_ == 0) {
        return array[0];
    }
    return array[1];
}
KeyHit Heap::poll(){
    if(size_ == 0) {
        return array[0];
    }
    KeyHit t = array[1];
    array[1] = array[size_];
    array.erase(array.begin()+size_);
    size_--;
    if(size_ > 0) {
        percUp(1);
    }
    return t;
}

bool Heap::isEmpty() {
    return size_ == 0;
}

void Heap::clear() {
    size_ = 0;
}

int Heap::size() {
    return size_;
}

