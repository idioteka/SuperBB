//
//  main.cpp
//  SuperBBmap
//
//  Created by Josip Maric on 30/11/15.
//  Copyright © 2015 Josip Maric. All rights reserved.
//

#include "IOManager.hpp"
#include "GenomeIndexer.hpp"
#include "SuperBBMapper.hpp"

void testIndex(int argc, const char * argv[]) {
    
    string genomeFilename = Config::instance()->inRootDir + "genome.fa";
    string* wholeGenome = IOManager::extractGenomeFromFile(genomeFilename);
    //    print(*wholeGenome);
    
        GenomeIndex* index = GenomeIndexer::createIndex(wholeGenome);
    
//    GenomeIndex* index = IOManager::readIndexFromFile();
    
    delete wholeGenome;
    
//    print(to_string(index->sitesLength));
    
        IOManager::writeIndexToFile(index);
    
    delete index;
}

void testKeysCreation(int argc, const char * argv[]) {
    
    string indexesFilename = Config::instance()->inRootDir + "inputIndexes.txt";
    ifstream ifsIndexes(indexesFilename.c_str());
    vector<vector<long>> indexesCorrectMap;
    if(!ifsIndexes) {
        print("File " + indexesFilename + " does not exist");
        exit(-1);
    }
    string lineIndexes;
    while(getline(ifsIndexes, lineIndexes)) {
        vector<long> indexes;
        vector<string> lines = split(lineIndexes, ' ');
        for (int i = 0; i < lines.size(); i++) {
            indexes.push_back(atol(lines[i].c_str()));
        }
        indexesCorrectMap.push_back(indexes);
    }
    
    string keysFilename = Config::instance()->inRootDir + "inputKeys.txt";
    ifstream ifsKeys(keysFilename.c_str());
    vector<vector<int>> keysCorrectMap;
    if(!ifsKeys) {
        print("File" + keysFilename + " does not exist");
        exit(-1);
    }
    string lineKeys;
    while(getline(ifsKeys, lineKeys)) {
        vector<int> keys;
        vector<string> lines = split(lineKeys, ' ');
        for (int i = 0; i < lines.size(); i++) {
            keys.push_back(atoi(lines[i].c_str()));
        }
        keysCorrectMap.push_back(keys);
    }
    
    string readsFilename = Config::instance()->inRootDir + "test_reads.bb";
    vector<Read*>* reads = IOManager::readReadsFromBBFormat(readsFilename);
    for (int i = 0; i < reads->size(); i++) {
        vector<long> indexes = (*reads)[i]->makeKeyOffsites();
        vector<int> keys = (*reads)[i]->createReadKeys();
        vector<int> keysCorrect = keysCorrectMap[i];
        vector<long> indexesCorrect = indexesCorrectMap[i];
        int readId = (*reads)[i]->id;
        for (int j = 0; j < keys.size(); j++) {
            if (keys[j] != keysCorrect[j] || indexes[j] != indexesCorrect[j]) {
                print(to_string(j) + ". id:" + to_string(readId) + ", keys: " + to_string(keys[j]) + "-" + to_string(keysCorrect[j]) + ", indexes: " + to_string(indexes[j]) + "-" + to_string(indexesCorrect[j]));
            }
        }
    }
}

void testAlgorithm(int argc, const char * argv[]) {
    string readsFilename = Config::instance()->inRootDir + "in2.bb";
    vector<Read*>* reads = IOManager::readReadsFromBBFormat(readsFilename);
    
    string genomeFilename = Config::instance()->inRootDir + "genome.fa";
    string* wholeGenome = IOManager::extractGenomeFromFile(genomeFilename);
    
//    GenomeIndex* index = GenomeIndexer::createIndex(wholeGenome);
    GenomeIndex* index = IOManager::readIndexFromFile();
//    IOManager::writeIndexToFile(index);
    
    print("Number of reads: " + to_string(reads->size()));
    for (int i = 0; i < 1; i++) {
        Read* read = (*reads)[i];
//        print(read->content);
        mapRead(read, index, wholeGenome);
    }
}

int main(int argc, const char * argv[]) {
    
//    testIndex(argc, argv);
//    testKeysCreation(argc, argv);
    testAlgorithm(argc, argv);

    return 0;
}
