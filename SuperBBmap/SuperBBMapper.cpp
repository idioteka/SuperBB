//
//  SuperBBMapper.cpp
//  SuperBBmap
//
//  Created by Josip Maric on 07/02/16.
//  Copyright © 2016 Josip Maric. All rights reserved.
//

#include "SuperBBMapper.hpp"

void mapRead(Read* read, GenomeIndex* index, string* wholeGenome) {
    
    vector<long> keyIndexes = read->makeKeyIndexes();
    vector<int> keys = read->createReadKeys();
    
    string reverseRead = read->reverseComplement();
    vector<long> reverseKeyIndexes = read->reverseComplementKeyIndexes();
    vector<int> reverseKeys = read->reverseComplementKeys();
    
    mapReadOneStrand(read, read->content, keyIndexes, keys, 0, index, wholeGenome);
    mapReadOneStrand(read, reverseRead, reverseKeyIndexes, reverseKeys, 1, index, wholeGenome);
}

void mapReadOneStrand(Read* read, string readContent, vector<long> keyIndexes, vector<int> keys, bool strand, GenomeIndex* index, string* wholeGenome) {
    vector<KeyHits*>* readKeysHits = getKeyHitsForKeys(keys, index);
//    print(to_string(readKeysHits->size()));
//    for (int i = 0; i < readKeysHits->size(); i++) {
//        KeyHits* keyHits = (*readKeysHits)[i];
//        print(to_string(keyHits->start) + " " + to_string(keyHits->number));
//    }
//    print("");
}

long countHitsForKey(int key, GenomeIndex* index) {
    long lengthOfSizes = keyspace();
    long numberOfKeyHits;
    
    if ((key + 1) == lengthOfSizes) {
        numberOfKeyHits = lengthOfSizes - index->sizes[key];
    }
    else {
        numberOfKeyHits = index->sizes[key+1] - index->sizes[key];
    }
    // TODO not sure if i will use reversed count hits
//    return numberOfKeyHits;
    int reversedKey = reverseComplementBinary(key, Config::instance()->keylen);
    if (key == reversedKey) {
        return numberOfKeyHits;
    }
    else {
        long numberOfReversedKeyHits;
        if ((reversedKey + 1) == lengthOfSizes) {
            numberOfReversedKeyHits = lengthOfSizes - index->sizes[reversedKey];
        }
        else {
            numberOfReversedKeyHits = index->sizes[reversedKey+1] - index->sizes[reversedKey];
        }
        return numberOfKeyHits + numberOfReversedKeyHits;
    }
}

vector<KeyHits*>* getKeyHitsForKeys(vector<int> keys, GenomeIndex* index) {
    // TODO comments left because of previous version reminder
//    int numberOfKeyHits = 0;
    vector<KeyHits*>* readKeysHits = new vector<KeyHits*>();
    for(unsigned int i = 0; i < keys.size(); i++) {
        int key = keys[i];
//        starts.push_back(-1);
//        stops.push_back(-1);
        if(key >= 0){
            long start = index->sizes[key];
            long number = countHitsForKey(key, index);
            if (number <= 0) {
                continue;
            }
            KeyHits* keyHits = new KeyHits(start, number);
            readKeysHits->push_back(keyHits);
//            if(len > 0 && len < max_len){
//                starts[i] = sizes[key];
//                stops[i] = starts[i] + len;
//                num_hits++;
//            }
        }
    }
    return readKeysHits;
}