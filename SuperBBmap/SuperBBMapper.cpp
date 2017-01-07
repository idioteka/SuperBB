//
//  SuperBBMapper.cpp
//  SuperBBmap
//
//  Created by Josip Maric on 07/02/16.
//  Copyright © 2016 Josip Maric. All rights reserved.
//

#include "SuperBBMapper.hpp"

void mapRead(Read* read, GenomeIndex* index, string* wholeGenome) {
    
    vector<long> keyOffsites = read->makeKeyOffsites();
    vector<int> keys = read->createReadKeys();
    
    string reverseRead = read->reverseComplement();
    vector<long> reverseKeyOffsites = read->reverseComplementKeyOffsites();
    vector<int> reverseKeys = read->reverseComplementKeys();
    
    mapReadOneStrand(read, read->content, keyOffsites, keys, 0, index, wholeGenome);
    mapReadOneStrand(read, reverseRead, reverseKeyOffsites, reverseKeys, 1, index, wholeGenome);
}

void mapReadOneStrand(Read* read, string readContent, vector<long> keyOffsites, vector<int> keys, bool strand, GenomeIndex* index, string* wholeGenome) {
    
    print(readContent);
    
    vector<KeyHitsCollection*>* readKeysHits = getKeyHitsForKeys(keys, keyOffsites, index);
    print(to_string(readKeysHits->size()));
    for (int i = 0; i < readKeysHits->size(); i++) {
        KeyHitsCollection* keyHits = (*readKeysHits)[i];
        print(to_string(keyHits->indexesStart) + " " + to_string(keyHits->numberOfKeyHits));
    }
    print("");
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
    return numberOfKeyHits;
//    int reversedKey = reverseComplementBinary(key, Config::instance()->keylen);
//    if (key == reversedKey) {
//        return numberOfKeyHits;
//    }
//    else {
//        long numberOfReversedKeyHits;
//        if ((reversedKey + 1) == lengthOfSizes) {
//            numberOfReversedKeyHits = lengthOfSizes - index->sizes[reversedKey];
//        }
//        else {
//            numberOfReversedKeyHits = index->sizes[reversedKey+1] - index->sizes[reversedKey];
//        }
//        return numberOfKeyHits + numberOfReversedKeyHits;
//    }
}

vector<KeyHitsCollection*>* getKeyHitsForKeys(vector<int> keys, vector<long> keyOffsites, GenomeIndex* index) {
    // TODO comments left because of previous version reminder
//    int numberOfKeyHits = 0;
    vector<KeyHitsCollection*>* readKeysHits = new vector<KeyHitsCollection*>();
    print("Number of keys "+to_string(keys.size()));
    int numHits = 0;
    for(unsigned int i = 0; i < keys.size(); i++) {
        int key = keys[i];
//        starts.push_back(-1);
//        stops.push_back(-1);
        if(key >= 0){
            long indexesStart = index->sizes[key];
            long number = countHitsForKey(key, index);
//            print("Number of key hits: " + to_string(number));
            if (number <= 0) {
                continue;
            }
            numHits += 1;
            KeyHitsCollection* keyHits = new KeyHitsCollection(i, indexesStart, number, keyOffsites[i]);
            readKeysHits->push_back(keyHits);
//            if(len > 0 && len < max_len){
//                starts[i] = sizes[key];
//                stops[i] = starts[i] + len;
//                num_hits++;
//            }
        }
    }
    print("Number of hitting keys: " + to_string(numHits));
    return readKeysHits;
}
