//
//  SuperBBMapper.hpp
//  SuperBBmap
//
//  Created by Josip Maric on 07/02/16.
//  Copyright © 2016 Josip Maric. All rights reserved.
//

#ifndef SuperBBMapper_hpp
#define SuperBBMapper_hpp

#include "Utils.hpp"
#include "GenomeIndex.hpp"
#include "Read.hpp"
#include "Alignment.hpp"
#include "KeyHitsCollection.hpp"

using namespace std;

void mapRead(Read* read, GenomeIndex* index, string* wholeGenome);
void mapReadOneStrand(Read* read, string readContent, vector<long> keyIndexes, vector<int> keys, bool strand, GenomeIndex* index, string* wholeGenome);
long countHitsForKey(int key, GenomeIndex* index);
vector<KeyHitsCollection*>* getKeyHitsForKeys(vector<int> keys, vector<long> keyIndexes, GenomeIndex* index);
#endif /* SuperBBMapper_hpp */
