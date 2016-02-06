//
//  SuperBBMapper.cpp
//  SuperBBmap
//
//  Created by Josip Maric on 07/02/16.
//  Copyright © 2016 Josip Maric. All rights reserved.
//

#include "SuperBBMapper.hpp"

void mapRead(Read* read, GenomeIndex* index) {
    
    vector<long> keyIndexes = read->makeKeyIndexes();
    vector<int> keys = read->createReadKeys();
    
    string reverseRead = read->reverseComplement();
    vector<long> reverseKeyIndexes = read->reverseComplementKeyIndexes();
    vector<int> reverseKeys = read->reverseComplementKeys();
    
    mapReadOneStrand(read, read->content, keyIndexes, keys, 0);
    mapReadOneStrand(read, reverseRead, reverseKeyIndexes, reverseKeys, 1);
}

void mapReadOneStrand(Read* read, string readContent, vector<long> keyIndexes, vector<int> keys, bool strand) {
    
}