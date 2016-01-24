//
//  main.cpp
//  SuperBBmap
//
//  Created by Josip Maric on 30/11/15.
//  Copyright © 2015 Josip Maric. All rights reserved.
//

#include "IOManager.hpp"
#include "GenomeIndexer.hpp"

void testIndex(int argc, const char * argv[]) {
    
    string genomeFilename = Config::instance()->inRootDir + "test_genome.fa";
    string* wholeGenome = IOManager::extractGenomeFromFile(genomeFilename);
    //    print(*wholeGenome);
    
    //    GenomeIndex* index = GenomeIndexer::createIndex(wholeGenome);
    
    GenomeIndex* index = IOManager::readIndexFromFile();
    
    delete wholeGenome;
    
    print(to_string(index->sitesLength));
    
    //    IOManager::writeIndexToFile(index);
    
    delete index;
}

void testAlgorithm(int argc, const char * argv[]) {
    
    string readsFilename = Config::instance()->inRootDir + "test_reads.bb";
    vector<Read*>* reads = IOManager::readReadsFromBBFormat(readsFilename);
    unsigned long length = reads->size();
    print(to_string(length));
}

int main(int argc, const char * argv[]) {
    
//    testIndex(argc, argv);
    testAlgorithm(argc, argv);
    
    return 0;
}
